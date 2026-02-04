using System;
using System.Collections.Concurrent;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Noise;
using NoiseSerde;

namespace NoiseBackend;

public struct BackendStats
{
    public ulong TotalRequests;
    public TimeSpan TotalWaitDuration;
    public TimeSpan TotalReadDuration;
    public TimeSpan TotalWriteDuration;
}

public class Backend : IDisposable
{
    private readonly AnonymousPipeServerStream _outStream; // We write to this (Racket input)
    private readonly AnonymousPipeServerStream _inStream;  // We read from this (Racket output)
    private readonly AnonymousPipeClientStream _racketIn;  // Racket reads from this
    private readonly AnonymousPipeClientStream _racketOut; // Racket writes to this
    
    // Using a lock for thread safety similar to Swift's dispatch semaphore
    private readonly object _lock = new();
    private readonly IOutputPort _outPort;
    private ulong _seq = 0;
    private readonly ConcurrentDictionary<ulong, IResponseHandler> _pending = new();
    
    private ulong _totalRequests = 0;
    private TimeSpan _totalWaitDuration = TimeSpan.Zero;
    private TimeSpan _totalReadDuration = TimeSpan.Zero;
    private TimeSpan _totalWriteDuration = TimeSpan.Zero;

    private readonly Thread _serverThread;
    private readonly Thread _readerThread;
    private volatile bool _disposed = false;

    public Backend(string zoPath, string modname, string proc)
    {
        // Pipes for communication
        // C# -> Racket
        _outStream = new AnonymousPipeServerStream(PipeDirection.Out, HandleInheritability.Inheritable);
        _racketIn = new AnonymousPipeClientStream(PipeDirection.In, _outStream.GetClientHandleAsString());

        // Racket -> C#
        _inStream = new AnonymousPipeServerStream(PipeDirection.In, HandleInheritability.Inheritable);
        _racketOut = new AnonymousPipeClientStream(PipeDirection.Out, _inStream.GetClientHandleAsString());

        _outPort = new FileStreamOutputPort(_outStream);

        _serverThread = new Thread(() => Serve(zoPath, modname, proc))
        {
            Name = "Noise Backend (Server)",
            IsBackground = true
        };
        _serverThread.Start();

        _readerThread = new Thread(Read)
        {
            Name = "Noise Backend (Reader)",
            IsBackground = true
        };
        _readerThread.Start();
    }

    private void Serve(string zoPath, string modname, string proc)
    {
        // Initialize Racket if needed (assuming Racket singleton handles this or checks)
        // Note: Racket.cs constructor initializes Racket. We might simply create an instance if not already.
        // Swift creates a new Racket instance.
        var r = new Racket(execPath: zoPath); // This boots Racket if not booted? Racket.cs seems to boot in constructor.
        
        r.Bracket<object>(() =>
        {
            r.Load(zoPath);
            
            // Construct arguments: '(quote modname)
            var mod = Val.Cons(Val.Symbol("quote"), Val.Cons(Val.Symbol(modname), Val.Null));
            
            // Get file descriptors/handles as integers
            // On Windows, these are Handles (IntPtr). On Unix, file descriptors (int).
            // Racket CS on Windows likely expects HANDLEs if using Windows API, or FDs if using C runtime.
            // But since 'racket_fixnum' is used in Swift, let's assume we pass the Handle value.
            // CSNoise usually runs on Windows, so IntPtr handle.
            
            nint inHandle = _racketIn.SafePipeHandle.DangerousGetHandle();
            nint outHandle = _racketOut.SafePipeHandle.DangerousGetHandle();

            var ifd = Val.Fixnum(inHandle);
            var ofd = Val.Fixnum(outHandle);
            
            var serveSymbol = r.Require(Val.Symbol(proc), mod).UnsafeCar;
            // Calls (serve in-handle out-handle)
            serveSymbol.UnsafeApply(Val.Cons(ifd, Val.Cons(ofd, Val.Null)));
            
            // Should not return until exit
            throw new InvalidOperationException("Racket server exited");
        });
    }

    private void Read()
    {
        var inp = new FileStreamInputPort(_inStream);
        while (!_disposed)
        {
            try
            {
                // Read Request ID
                ulong id = inp.ReadUVarint();
                
                IResponseHandler? handler;
                if (_pending.TryRemove(id, out handler))
                {
                    TimeSpan duration = handler.Handle(inp);
                    
                    lock (_lock)
                    {
                        _totalRequests++;
                        _totalReadDuration += duration;
                        _totalWaitDuration += (DateTime.UtcNow - handler.StartTime); // approx
                    }
                }
                else
                {
                    // Log error: future gone
                    // We might need to drain the response to prevent desync? 
                    // Protocol relies on handler to read data. If we don't have a handler, we depend on Serde knowing how to skip?
                    // Serde doesn't support skipping arbitrary objects without type info.
                    // This implies a critical failure if handler is missing.
                    Console.Error.WriteLine($"Error: Missing handler for request #{id}");
                    break; // Unrecoverable without schema
                }
            }
            catch (Exception ex)
            {
                if (!_disposed) Console.Error.WriteLine($"Reader error: {ex.Message}");
                break;
            }
        }
    }

    public Task<T> Send<T>(
        Action<IOutputPort> writeProc,
        Func<IInputPort, T> readProc,
        string commandName = "")
    {
        var tcs = new TaskCompletionSource<T>();
        ulong id;
        
        lock (_lock)
        {
            id = _seq++;
            // Log command
        }

        var start = DateTime.UtcNow; // precision might be low, good enough for stats
        
        lock (_lock) // Write lock
        {
             id.WriteUVarint(_outPort);
             writeProc(_outPort);
             _outPort.Flush();
             _totalWriteDuration += (DateTime.UtcNow - start);
        }

        var handler = new ResponseHandlerImpl<T>(id, tcs, readProc);
        if (!_pending.TryAdd(id, handler))
        {
            tcs.SetException(new InvalidOperationException("Duplicate request ID"));
            return tcs.Task;
        }

        return tcs.Task;
    }

    public BackendStats Stats()
    {
        lock (_lock)
        {
            return new BackendStats
            {
                TotalRequests = _totalRequests,
                TotalWaitDuration = _totalWaitDuration,
                TotalReadDuration = _totalReadDuration,
                TotalWriteDuration = _totalWriteDuration
            };
        }
    }

    public void Dispose()
    {
        _disposed = true;
        _outStream.Dispose();
        _inStream.Dispose();
        _racketIn.Dispose();
        _racketOut.Dispose();
        // Threads will die eventually or we can Join
    }

    // Helper interface
    private interface IResponseHandler
    {
        DateTime StartTime { get; }
        TimeSpan Handle(IInputPort inp);
    }

    private class ResponseHandlerImpl<T> : IResponseHandler
    {
        public ulong Id { get; }
        public DateTime StartTime { get; } = DateTime.UtcNow;
        private readonly TaskCompletionSource<T> _tcs;
        private readonly Func<IInputPort, T> _read;

        public ResponseHandlerImpl(ulong id, TaskCompletionSource<T> tcs, Func<IInputPort, T> read)
        {
            Id = id;
            _tcs = tcs;
            _read = read;
        }

        public TimeSpan Handle(IInputPort inp)
        {
            var sw = Stopwatch.StartNew();
            try
            {
                byte status = inp.ReadByte();
                if (status == 1)
                {
                    T result = _read(inp);
                    _tcs.TrySetResult(result);
                }
                else
                {
                    string error = inp.ReadString();
                    _tcs.TrySetException(new Exception(error));
                }
            }
            catch (Exception ex)
            {
                _tcs.TrySetException(ex);
            }
            sw.Stop();
            return sw.Elapsed;
        }
    }
}
