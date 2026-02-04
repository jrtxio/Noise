using System;
using System.IO;

namespace NoiseSerde;

public class FileStreamOutputPort : IOutputPort
{
    private readonly Stream _stream;

    public FileStreamOutputPort(Stream stream)
    {
        _stream = stream;
    }

    public void Write(ReadOnlySpan<byte> data)
    {
        _stream.Write(data);
    }

    public void WriteByte(byte b)
    {
        _stream.WriteByte(b);
    }

    public void Flush()
    {
        _stream.Flush();
    }
}
