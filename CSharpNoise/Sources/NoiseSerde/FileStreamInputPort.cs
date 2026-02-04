using System;
using System.IO;

namespace NoiseSerde;

public class FileStreamInputPort : IInputPort
{
    private readonly Stream _stream;

    public FileStreamInputPort(Stream stream)
    {
        _stream = stream;
    }

    public int Read(Span<byte> buffer)
    {
        return _stream.Read(buffer);
    }

    public byte ReadByte()
    {
        int b = _stream.ReadByte();
        if (b == -1) return 0; // EOF convention
        return (byte)b;
    }
}
