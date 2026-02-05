// Serde.hpp - Serialization Types
// Mirrors SwiftNoise/Sources/NoiseSerde/Serde.swift

#pragma once

#include "Port.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace Noise {

// MARK: - Varint

/// Reads a signed variable-length integer.
inline int64_t readVarint(InputPort& port) {
    int64_t s = 0;
    int64_t n = 0;
    while (true) {
        uint8_t b = port.readByte();
        n |= static_cast<int64_t>(b & 0x7F) << s;
        if ((b & 0x80) == 0) break;
        s += 7;
    }
    return n;
}

/// Writes a signed variable-length integer.
inline void writeVarint(OutputPort& port, int64_t value) {
    uint64_t n = static_cast<uint64_t>(value);
    while (true) {
        uint64_t r = n & 0x7F;
        uint64_t q = n >> 7;
        if (q == 0) {
            port.writeByte(static_cast<uint8_t>(r));
            break;
        } else {
            port.writeByte(static_cast<uint8_t>(r | 0x80));
            n = q;
        }
    }
}

// MARK: - UVarint

/// Reads an unsigned variable-length integer.
inline uint64_t readUVarint(InputPort& port) {
    uint64_t s = 0;
    uint64_t n = 0;
    while (true) {
        uint8_t b = port.readByte();
        n |= static_cast<uint64_t>(b & 0x7F) << s;
        if ((b & 0x80) == 0) break;
        s += 7;
    }
    return n;
}

/// Writes an unsigned variable-length integer.
inline void writeUVarint(OutputPort& port, uint64_t value) {
    uint64_t n = value;
    while (true) {
        uint64_t r = n & 0x7F;
        uint64_t q = n >> 7;
        if (q == 0) {
            port.writeByte(static_cast<uint8_t>(r));
            break;
        } else {
            port.writeByte(static_cast<uint8_t>(r | 0x80));
            n = q;
        }
    }
}

// MARK: - Int32

inline int32_t readInt32(InputPort& port) {
    return (static_cast<int32_t>(port.readByte()) << 24) |
           (static_cast<int32_t>(port.readByte()) << 16) |
           (static_cast<int32_t>(port.readByte()) << 8) |
           (static_cast<int32_t>(port.readByte()));
}

inline void writeInt32(OutputPort& port, int32_t value) {
    port.writeByte(static_cast<uint8_t>((value >> 24) & 0xFF));
    port.writeByte(static_cast<uint8_t>((value >> 16) & 0xFF));
    port.writeByte(static_cast<uint8_t>((value >> 8) & 0xFF));
    port.writeByte(static_cast<uint8_t>(value & 0xFF));
}

// MARK: - UInt32

inline uint32_t readUInt32(InputPort& port) {
    return (static_cast<uint32_t>(port.readByte()) << 24) |
           (static_cast<uint32_t>(port.readByte()) << 16) |
           (static_cast<uint32_t>(port.readByte()) << 8) |
           (static_cast<uint32_t>(port.readByte()));
}

inline void writeUInt32(OutputPort& port, uint32_t value) {
    port.writeByte(static_cast<uint8_t>((value >> 24) & 0xFF));
    port.writeByte(static_cast<uint8_t>((value >> 16) & 0xFF));
    port.writeByte(static_cast<uint8_t>((value >> 8) & 0xFF));
    port.writeByte(static_cast<uint8_t>(value & 0xFF));
}

// MARK: - Float32

inline float readFloat32(InputPort& port) {
    uint32_t bits = readUInt32(port);
    float result;
    std::memcpy(&result, &bits, sizeof(result));
    return result;
}

inline void writeFloat32(OutputPort& port, float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    writeUInt32(port, bits);
}

// MARK: - Float64

inline double readFloat64(InputPort& port) {
    uint64_t bits = 0;
    for (int i = 0; i < 8; i++) {
        bits = (bits << 8) | port.readByte();
    }
    double result;
    std::memcpy(&result, &bits, sizeof(result));
    return result;
}

inline void writeFloat64(OutputPort& port, double value) {
    uint64_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    for (int i = 7; i >= 0; i--) {
        port.writeByte(static_cast<uint8_t>((bits >> (i * 8)) & 0xFF));
    }
}

// MARK: - String

inline std::string readString(InputPort& port) {
    int64_t len = readVarint(port);
    if (len <= 0) return "";
    std::vector<uint8_t> bytes = port.read(static_cast<size_t>(len));
    return std::string(bytes.begin(), bytes.end());
}

inline void writeString(OutputPort& port, const std::string& value) {
    writeVarint(port, static_cast<int64_t>(value.size()));
    port.write(reinterpret_cast<const uint8_t*>(value.data()), value.size());
}

// MARK: - Data (bytes)

inline std::vector<uint8_t> readData(InputPort& port) {
    int64_t len = readVarint(port);
    if (len <= 0) return {};
    return port.read(static_cast<size_t>(len));
}

inline void writeData(OutputPort& port, const std::vector<uint8_t>& data) {
    writeVarint(port, static_cast<int64_t>(data.size()));
    port.write(data);
}

} // namespace Noise
