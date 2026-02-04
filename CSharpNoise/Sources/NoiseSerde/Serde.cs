using System;
using System.Buffers.Binary;
using System.Collections.Generic;
using System.Text;

namespace NoiseSerde;

public static class Serde
{
    // MARK: - UVarint
    public static ulong ReadUVarint(this IInputPort inp)
    {
        ulong s = 0;
        ulong n = 0;
        while (true)
        {
            byte b = inp.ReadByte();
            ulong x = b;
            if ((x & 0x80) == 0)
            {
                n += x << (int)s;
                break;
            }
            n += (x & 0x7F) << (int)s;
            s += 7;
        }
        return n;
    }

    public static void WriteUVarint(this ulong value, IOutputPort outp)
    {
        ulong n = value;
        while (true)
        {
            ulong q = n / 0x80;
            byte r = (byte)(n % 0x80);
            if (q == 0)
            {
                outp.WriteByte(r);
                break;
            }
            else
            {
                outp.WriteByte((byte)(r | 0x80));
                n = q;
            }
        }
    }

    // MARK: - Varint
    public static long ReadVarint(this IInputPort inp)
    {
        ulong s = 0;
        long n = 0;
        while (true)
        {
            byte b = inp.ReadByte();
            long x = b;
            if ((x & 0x80) == 0)
            {
                n += x << (int)s;
                break;
            }
            n += (x & 0x7F) << (int)s;
            s += 7;
        }
        // zig-zag decoding
        return (n & 1) == 0 ? (n >> 1) : ~(n >> 1);
    }

    public static void WriteVarint(this long value, IOutputPort outp)
    {
        // zig-zag encoding
        long n = (value << 1) ^ (value < 0 ? -1 : 0);
        ulong un = (ulong)n;
        while (true)
        {
            ulong q = un / 0x80;
            byte r = (byte)(un % 0x80);
            if (q == 0)
            {
                outp.WriteByte(r);
                break;
            }
            else
            {
                outp.WriteByte((byte)(r | 0x80));
                un = q;
            }
        }
    }

    // MARK: - Bool
    public static bool ReadBool(this IInputPort inp) => inp.ReadByte() == 1;

    public static void Write(this bool value, IOutputPort outp) => outp.WriteByte((byte)(value ? 1 : 0));

    // MARK: - Data (byte[])
    public static byte[] ReadData(this IInputPort inp)
    {
        long vlen = inp.ReadVarint();
        if (vlen == 0) return Array.Empty<byte>();
        
        int len = (int)vlen;
        byte[] buffer = new byte[len];
        int offset = 0;
        int remaining = len;
        while (remaining > 0)
        {
            int read = inp.Read(buffer.AsSpan(offset, remaining));
            if (read == 0) throw new System.IO.EndOfStreamException($"Expected {len} bytes, got {offset}");
            offset += read;
            remaining -= read;
        }
        return buffer;
    }

    public static void Write(this byte[] data, IOutputPort outp)
    {
        ((long)data.Length).WriteVarint(outp);
        outp.Write(data);
    }

    // MARK: - String
    public static string ReadString(this IInputPort inp)
    {
        long vlen = inp.ReadVarint();
        if (vlen == 0) return "";
        
        int len = (int)vlen;
        byte[] buffer = new byte[len];
        int offset = 0;
        int remaining = len;
        while (remaining > 0)
        {
            int read = inp.Read(buffer.AsSpan(offset, remaining));
            if (read == 0) throw new System.IO.EndOfStreamException($"Expected {len} bytes, got {offset}");
            offset += read;
            remaining -= read;
        }
        return Encoding.UTF8.GetString(buffer);
    }

    public static void Write(this string value, IOutputPort outp)
    {
        byte[] bytes = Encoding.UTF8.GetBytes(value);
        ((long)bytes.Length).WriteVarint(outp);
        outp.Write(bytes);
    }

    // MARK: - Integers
    public static int ReadInt32(this IInputPort inp)
    {
        Span<byte> buf = stackalloc byte[4];
        ReadExact(inp, buf);
        // BigEndian handling manually to match Swift bit shifting
        return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    }

    public static void Write(this int value, IOutputPort outp)
    {
        outp.WriteByte((byte)(value >> 24));
        outp.WriteByte((byte)(value >> 16));
        outp.WriteByte((byte)(value >> 8));
        outp.WriteByte((byte)value);
    }

    public static uint ReadUInt32(this IInputPort inp)
    {
        Span<byte> buf = stackalloc byte[4];
        ReadExact(inp, buf);
        return ((uint)buf[0] << 24) | ((uint)buf[1] << 16) | ((uint)buf[2] << 8) | (uint)buf[3];
    }

    public static void Write(this uint value, IOutputPort outp)
    {
        outp.WriteByte((byte)(value >> 24));
        outp.WriteByte((byte)(value >> 16));
        outp.WriteByte((byte)(value >> 8));
        outp.WriteByte((byte)value);
    }
    
    // Helpers
    private static void ReadExact(IInputPort inp, Span<byte> buffer)
    {
        int offset = 0;
        while (offset < buffer.Length)
        {
            int read = inp.Read(buffer.Slice(offset));
            if (read == 0) throw new System.IO.EndOfStreamException();
            offset += read;
        }
    }
}
