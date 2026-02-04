using System;

namespace NoiseSerde;

public interface IInputPort
{
    /// <summary>
    /// Reads bytes from the handle into <paramref name="buffer"/>, returning
    /// the number of bytes read. Returns 0 at EOF.
    /// </summary>
    int Read(Span<byte> buffer);

    /// <summary>
    /// Reads a single byte. Returns 0 at EOF.
    /// </summary>
    byte ReadByte();
}

public interface IOutputPort
{
    /// <summary>
    /// Buffers <paramref name="data"/> into memory if there is sufficient capacity.
    /// Otherwise, flushes any previously-buffered data and writes the new data.
    /// </summary>
    void Write(ReadOnlySpan<byte> data);

    /// <summary>
    /// Buffers a single byte into memory if there is sufficient capacity.
    /// Otherwise, flushes any previously-buffered data and then buffers the byte.
    /// </summary>
    void WriteByte(byte b);

    /// <summary>
    /// Writes any buffered data to the handle.
    /// </summary>
    void Flush();
}
