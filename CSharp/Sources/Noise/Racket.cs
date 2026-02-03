using System.Runtime.InteropServices;
using System.Text;

namespace Noise;

/// <summary>
/// P/Invoke declarations for the Racket CS C API.
/// </summary>
internal static unsafe class RacketImports
{
    /// <summary>Boot arguments structure for Racket CS initialization.</summary>
    [StructLayout(LayoutKind.Sequential)]
    internal struct racket_boot_arguments_t
    {
        public byte* exec_file;
        public byte* boot1_path;
        public byte* boot2_path;
        public byte* boot3_path;
    }

    [DllImport("racketcs.dll", EntryPoint = "racket_boot", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    internal static extern void racket_boot(racket_boot_arguments_t* args);

    [DllImport("racketcs.dll", EntryPoint = "racket_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static extern void racket_destroy();

    [DllImport("racketcs.dll", EntryPoint = "racket_activate_thread", CallingConvention = CallingConvention.Cdecl)]
    internal static extern void racket_activate_thread();

    [DllImport("racketcs.dll", EntryPoint = "racket_deactivate_thread", CallingConvention = CallingConvention.Cdecl)]
    internal static extern void racket_deactivate_thread();

    [DllImport("racketcs.dll", EntryPoint = "racket_embedded_load_file", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    internal static extern void racket_embedded_load_file([MarshalAs(UnmanagedType.LPStr)] string path, int flags);

    [DllImport("racketcs.dll", EntryPoint = "racket_dynamic_require", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_dynamic_require(nint mod, nint what);

    [DllImport("racketcs.dll", EntryPoint = "racket_nil", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_nil();

    [DllImport("racketcs.dll", EntryPoint = "racket_true", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_true();

    [DllImport("racketcs.dll", EntryPoint = "racket_false", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_false();

    [DllImport("racketcs.dll", EntryPoint = "racket_fixnum", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_fixnum(nint value);

    [DllImport("racketcs.dll", EntryPoint = "racket_symbol", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    internal static extern nint racket_symbol([MarshalAs(UnmanagedType.LPStr)] string s);

    [DllImport("racketcs.dll", EntryPoint = "racket_string", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    internal static extern nint racket_string([MarshalAs(UnmanagedType.LPStr)] string s, nuint len);

    [DllImport("racketcs.dll", EntryPoint = "racket_cons", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_cons(nint a, nint b);

    [DllImport("racketcs.dll", EntryPoint = "racket_apply", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_apply(nint proc, nint args);

    [DllImport("racketcs.dll", EntryPoint = "racket_procedurep", CallingConvention = CallingConvention.Cdecl)]
    internal static extern int racket_procedurep(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_pairp", CallingConvention = CallingConvention.Cdecl)]
    internal static extern int racket_pairp(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_fixnump", CallingConvention = CallingConvention.Cdecl)]
    internal static extern int racket_fixnump(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_bytevectorp", CallingConvention = CallingConvention.Cdecl)]
    internal static extern int racket_bytevectorp(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_car", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_car(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_cdr", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_cdr(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_fixnum_value", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_fixnum_value(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_bytevector_length", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nuint racket_bytevector_length(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_bytevector_data", CallingConvention = CallingConvention.Cdecl)]
    internal static extern nint racket_bytevector_data(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_lock_object", CallingConvention = CallingConvention.Cdecl)]
    internal static extern void racket_lock_object(nint ptr);

    [DllImport("racketcs.dll", EntryPoint = "racket_unlock_object", CallingConvention = CallingConvention.Cdecl)]
    internal static extern void racket_unlock_object(nint ptr);
}

/// <summary>
/// The Racket runtime.
/// </summary>
/// <remarks>
/// Threading: The thread on which the runtime is instantiated is considered the
/// main Racket place. All Racket operations must be run on that thread.
/// You may work with Chez Scheme values and call Chez Scheme primitives from
/// other threads (see Bracket and Activate).
///
/// Warning: Only one instance may be created per process.
/// </summary>
public sealed unsafe class Racket
{
    private readonly Thread _mainRacketPlace;
    private bool _initialized;

    /// <summary>
    /// Initializes a new instance of the Racket runtime.
    /// </summary>
    /// <param name="execPath">Path to the Racket executable (default: "racket")</param>
    public Racket(string execPath = "racket")
    {
        _mainRacketPlace = Thread.CurrentThread;

        var bootDir = BootFileExtractor.GetBootDirectory();

        var args = new RacketImports.racket_boot_arguments_t();
        args.exec_file = AllocateAndCopy(execPath);
        args.boot1_path = AllocateAndCopy(Path.Combine(bootDir, "petite.boot"));
        args.boot2_path = AllocateAndCopy(Path.Combine(bootDir, "scheme.boot"));
        args.boot3_path = AllocateAndCopy(Path.Combine(bootDir, "racket.boot"));

        try
        {
            RacketImports.racket_boot(&args);
            RacketImports.racket_deactivate_thread();
        }
        finally
        {
            Marshal.FreeHGlobal((nint)args.exec_file);
            Marshal.FreeHGlobal((nint)args.boot1_path);
            Marshal.FreeHGlobal((nint)args.boot2_path);
            Marshal.FreeHGlobal((nint)args.boot3_path);
        }

        _initialized = true;
    }

    /// <summary>
    /// Loads compiled Racket code (.zo file).
    /// </summary>
    /// <param name="zoPath">Path to the .zo file</param>
    /// <exception cref="InvalidOperationException">
    /// Thrown if called from a different thread than the main Racket place
    /// </exception>
    public void Load(string zoPath)
    {
        EnsureOnMainThread();
        RacketImports.racket_embedded_load_file(zoPath, flags: 1);
    }

    /// <summary>
    /// Requires a symbol from a module.
    /// </summary>
    /// <param name="what">The symbol to require</param>
    /// <param name="mod">The module specification</param>
    /// <returns>The required value</returns>
    /// <exception cref="InvalidOperationException">
    /// Thrown if called from a different thread than the main Racket place
    /// </exception>
    public Val Require(Val what, Val mod)
    {
        EnsureOnMainThread();
        var result = RacketImports.racket_dynamic_require(mod.Ptr, what.Ptr);
        return new Val(result);
    }

    /// <summary>
    /// Executes a procedure after activating the current thread,
    /// then deactivates before returning.
    /// </summary>
    public T Bracket<T>(Func<T> proc)
    {
        RacketImports.racket_activate_thread();
        try
        {
            return proc();
        }
        finally
        {
            RacketImports.racket_deactivate_thread();
        }
    }

    /// <summary>
    /// Makes the current thread known to Chez Scheme.
    /// </summary>
    /// <remarks>
    /// Warning: Accessing Chez Scheme data from inactive threads
    /// races against the garbage collector. Active threads that aren't
    /// running Scheme code block the garbage collector, so deactivate
    /// unused threads with Deactivate.
    /// </remarks>
    public void Activate()
    {
        RacketImports.racket_activate_thread();
    }

    /// <summary>
    /// Deactivates the current thread from Chez Scheme.
    /// </summary>
    public void Deactivate()
    {
        RacketImports.racket_deactivate_thread();
    }

    /// <summary>
    /// Tears down the Chez Scheme runtime.
    /// </summary>
    public void Destroy()
    {
        RacketImports.racket_destroy();
    }

    private void EnsureOnMainThread()
    {
        if (Thread.CurrentThread != _mainRacketPlace)
            throw new InvalidOperationException(
                "This operation must be called from the main Racket place thread");
    }

    private byte* AllocateAndCopy(string str)
    {
        var bytes = Encoding.UTF8.GetBytes(str + '\0');
        var ptr = (byte*)Marshal.AllocHGlobal(bytes.Length);
        fixed (byte* src = bytes)
        {
            Buffer.MemoryCopy(src, ptr, bytes.Length, bytes.Length);
        }
        return ptr;
    }
}

/// <summary>
/// An unsafe wrapper for Chez Scheme values.
/// </summary>
/// <remarks>
/// Warning: Values may be moved by the GC at any time, so these
/// helpers should mainly be used to create data to be passed into
/// Racket, and to copy data from Racket within activated threads.
/// </remarks>
public readonly struct Val
{
    public nint Ptr { get; }

    public Val(nint ptr)
    {
        Ptr = ptr;
    }

    /// <summary>The empty list.</summary>
    public static Val Null => new Val(RacketImports.racket_nil());

    /// <summary>The false value.</summary>
    public static Val False => new Val(RacketImports.racket_false());

    /// <summary>The true value.</summary>
    public static Val True => new Val(RacketImports.racket_true());

    /// <summary>Creates a Chez Scheme fixnum.</summary>
    public static Val Fixnum(nint value) => new Val(RacketImports.racket_fixnum(value));

    /// <summary>Creates a Chez Scheme symbol.</summary>
    public static Val Symbol(string name) => new Val(RacketImports.racket_symbol(name));

    /// <summary>Creates a Chez Scheme string.</summary>
    public static Val String(string value)
    {
        var bytes = Encoding.UTF8.GetBytes(value);
        var ptr = RacketImports.racket_string(value, (nuint)bytes.Length);
        return new Val(ptr);
    }

    /// <summary>Creates a pair of two values.</summary>
    public static Val Cons(Val car, Val cdr) => new Val(RacketImports.racket_cons(car.Ptr, cdr.Ptr));

    /// <summary>Locks the value to prevent GC from moving it.</summary>
    public void Lock() => RacketImports.racket_lock_object(Ptr);

    /// <summary>Unlocks the value to let GC move it.</summary>
    public void Unlock() => RacketImports.racket_unlock_object(Ptr);

    /// <summary>Locks and returns the value.</summary>
    public Val Locked() { Lock(); return this; }

    /// <summary>Unlocks and returns the value.</summary>
    public Val Unlocked() { Unlock(); return this; }

    /// <summary>Applies the value as a procedure.</summary>
    public Val? Apply(Val args)
    {
        if (!IsProcedure)
            return null;
        return new Val(RacketImports.racket_apply(Ptr, args.Ptr));
    }

    /// <summary>Applies the value as a procedure (unsafe).</summary>
    public Val UnsafeApply(Val args) => new Val(RacketImports.racket_apply(Ptr, args.Ptr));

    /// <summary>Returns true if this is a procedure.</summary>
    public bool IsProcedure => RacketImports.racket_procedurep(Ptr) == 1;

    /// <summary>Returns true if this is a pair.</summary>
    public bool IsPair => RacketImports.racket_pairp(Ptr) == 1;

    /// <summary>Returns true if this is a fixnum.</summary>
    public bool IsFixnum => RacketImports.racket_fixnump(Ptr) == 1;

    /// <summary>Returns true if this is a bytevector.</summary>
    public bool IsBytevector => RacketImports.racket_bytevectorp(Ptr) == 1;

    /// <summary>Returns the car of a pair.</summary>
    public Val? Car => IsPair ? new Val(RacketImports.racket_car(Ptr)) : null;

    /// <summary>Returns the cdr of a pair.</summary>
    public Val? Cdr => IsPair ? new Val(RacketImports.racket_cdr(Ptr)) : null;

    /// <summary>Returns the car of a pair (unsafe).</summary>
    public Val UnsafeCar => new Val(RacketImports.racket_car(Ptr));

    /// <summary>Returns the cdr of a pair (unsafe).</summary>
    public Val UnsafeCdr => new Val(RacketImports.racket_cdr(Ptr));

    /// <summary>Extracts the integer value of a fixnum.</summary>
    public nint? FixnumValue => IsFixnum ? RacketImports.racket_fixnum_value(Ptr) : null;

    /// <summary>Extracts the integer value of a fixnum (unsafe).</summary>
    public nint UnsafeFixnumValue => RacketImports.racket_fixnum_value(Ptr);

    /// <summary>Copies a Chez Scheme bytevector into a string (UTF-8).</summary>
    public string? Bytestring()
    {
        if (!IsBytevector)
            return null;

        return UnsafeBytevector(nulTerminated: true);
    }

    /// <summary>Copies a Chez Scheme bytevector into a string (unsafe).</summary>
    public string UnsafeBytestring()
    {
        return UnsafeBytevector(nulTerminated: true);
    }

    /// <summary>Copies a Chez Scheme bytevector into a byte array.</summary>
    public byte[]? Bytevector()
    {
        if (!IsBytevector)
            return null;

        return UnsafeBytevectorBytes();
    }

    /// <summary>Copies a Chez Scheme bytevector into a byte array (unsafe).</summary>
    public byte[] UnsafeBytevectorBytes()
    {
        var len = (int)RacketImports.racket_bytevector_length(Ptr);
        var data = RacketImports.racket_bytevector_data(Ptr);
        var result = new byte[len];
        Marshal.Copy(data, result, 0, len);
        return result;
    }

    private string UnsafeBytevector(bool nulTerminated)
    {
        var len = (int)RacketImports.racket_bytevector_length(Ptr);
        var data = RacketImports.racket_bytevector_data(Ptr);
        var bytes = new byte[len + (nulTerminated ? 1 : 0)];
        Marshal.Copy(data, bytes, 0, len);
        return Encoding.UTF8.GetString(bytes, 0, len);
    }

    public override bool Equals(object? obj)
    {
        return obj is Val other && Ptr == other.Ptr;
    }

    public override int GetHashCode()
    {
        return Ptr.GetHashCode();
    }

    public static bool operator ==(Val left, Val right)
    {
        return left.Equals(right);
    }

    public static bool operator !=(Val left, Val right)
    {
        return !(left == right);
    }
}

/// <summary>
/// Extracts boot files from embedded resources.
/// </summary>
internal static class BootFileExtractor
{
    private static string? _bootDirectory;
    private static readonly object _lock = new();

    public static string GetBootDirectory()
    {
        if (_bootDirectory != null)
            return _bootDirectory;

        lock (_lock)
        {
            if (_bootDirectory != null)
                return _bootDirectory;

            var architecture = RuntimeInformation.ProcessArchitecture;
            var tempPath = Path.Combine(Path.GetTempPath(), $"Noise_boot_{Guid.NewGuid()}");
            Directory.CreateDirectory(tempPath);

            var archFolder = architecture == Architecture.Arm64 ? "arm64" : "x64";
            var bootFiles = new[] { "petite.boot", "scheme.boot", "racket.boot" };

            var assembly = typeof(BootFileExtractor).Assembly;
            var resourceNames = assembly.GetManifestResourceNames();

            foreach (var bootFile in bootFiles)
            {
                var resourceName = resourceNames.FirstOrDefault(n =>
                    n.Contains($"NoiseBoot.Windows.boot.{archFolder}") &&
                    n.EndsWith(bootFile));

                if (resourceName == null)
                    throw new FileNotFoundException($"Boot file not found: {bootFile}");

                using var stream = assembly.GetManifestResourceStream(resourceName)!;
                var outputPath = Path.Combine(tempPath, bootFile);
                using var fileStream = File.Create(outputPath);
                stream.CopyTo(fileStream);
            }

            _bootDirectory = tempPath;

            AppDomain.CurrentDomain.ProcessExit += (_, _) => Cleanup();

            return _bootDirectory;
        }
    }

    private static void Cleanup()
    {
        if (_bootDirectory != null && Directory.Exists(_bootDirectory))
        {
            try
            {
                Directory.Delete(_bootDirectory, recursive: true);
            }
            catch
            {
                // Ignore cleanup errors
            }
        }
    }
}
