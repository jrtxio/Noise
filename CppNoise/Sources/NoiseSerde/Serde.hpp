// Serde.hpp - Serialization Types

#pragma once

#include "Port.hpp"
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace Noise {

// Bool
inline bool readBool(InputPort& p) { return p.readByte() == 1; }
inline void writeBool(OutputPort& p, bool v) { p.writeByte(v ? 1 : 0); }

// Varint (zigzag encoded)
inline int64_t readVarint(InputPort& p) {
    uint64_t s = 0, n = 0;
    while (true) {
        uint8_t b = p.readByte();
        n |= uint64_t(b & 0x7F) << s;
        if ((b & 0x80) == 0) break;
        s += 7;
    }
    return (n & 1) ? ~int64_t(n >> 1) : int64_t(n >> 1);
}

inline void writeVarint(OutputPort& p, int64_t v) {
    uint64_t n = uint64_t((v << 1) ^ (v < 0 ? -1 : 0));
    while (true) {
        if (n < 0x80) { p.writeByte(uint8_t(n)); break; }
        p.writeByte(uint8_t((n & 0x7F) | 0x80));
        n >>= 7;
    }
}

// UVarint
inline uint64_t readUVarint(InputPort& p) {
    uint64_t s = 0, n = 0;
    while (true) {
        uint8_t b = p.readByte();
        n |= uint64_t(b & 0x7F) << s;
        if ((b & 0x80) == 0) break;
        s += 7;
    }
    return n;
}

inline void writeUVarint(OutputPort& p, uint64_t v) {
    while (true) {
        if (v < 0x80) { p.writeByte(uint8_t(v)); break; }
        p.writeByte(uint8_t((v & 0x7F) | 0x80));
        v >>= 7;
    }
}

// Int16 / UInt16
inline int16_t readInt16(InputPort& p) {
    return int16_t(p.readByte()) << 8 | int16_t(p.readByte());
}

inline void writeInt16(OutputPort& p, int16_t v) {
    p.writeByte(uint8_t(v >> 8));
    p.writeByte(uint8_t(v));
}

inline uint16_t readUInt16(InputPort& p) {
    return uint16_t(p.readByte()) << 8 | uint16_t(p.readByte());
}

inline void writeUInt16(OutputPort& p, uint16_t v) {
    p.writeByte(uint8_t(v >> 8));
    p.writeByte(uint8_t(v));
}

// Int32 / UInt32
inline int32_t readInt32(InputPort& p) {
    return int32_t(p.readByte()) << 24 | int32_t(p.readByte()) << 16 |
           int32_t(p.readByte()) << 8 | int32_t(p.readByte());
}
inline void writeInt32(OutputPort& p, int32_t v) {
    p.writeByte(uint8_t(v >> 24)); p.writeByte(uint8_t(v >> 16));
    p.writeByte(uint8_t(v >> 8)); p.writeByte(uint8_t(v));
}
inline uint32_t readUInt32(InputPort& p) { return uint32_t(readInt32(p)); }
inline void writeUInt32(OutputPort& p, uint32_t v) { writeInt32(p, int32_t(v)); }

// Float32 / Float64
inline float readFloat32(InputPort& p) {
    uint32_t bits = readUInt32(p);
    float r; std::memcpy(&r, &bits, 4); return r;
}
inline void writeFloat32(OutputPort& p, float v) {
    uint32_t bits; std::memcpy(&bits, &v, 4); writeUInt32(p, bits);
}
inline double readFloat64(InputPort& p) {
    uint64_t bits = 0;
    for (int i = 0; i < 8; i++) bits = (bits << 8) | p.readByte();
    double r; std::memcpy(&r, &bits, 8); return r;
}
inline void writeFloat64(OutputPort& p, double v) {
    uint64_t bits; std::memcpy(&bits, &v, 8);
    for (int i = 7; i >= 0; i--) p.writeByte(uint8_t(bits >> (i * 8)));
}

// String
inline std::string readString(InputPort& p) {
    int64_t len = readVarint(p);
    if (len <= 0) return "";
    auto bytes = p.read(size_t(len));
    return std::string(bytes.begin(), bytes.end());
}
inline void writeString(OutputPort& p, const std::string& s) {
    writeVarint(p, int64_t(s.size()));
    p.write(reinterpret_cast<const uint8_t*>(s.data()), s.size());
}

// Data (bytes)
inline std::vector<uint8_t> readData(InputPort& p) {
    int64_t len = readVarint(p);
    return (len <= 0) ? std::vector<uint8_t>{} : p.read(size_t(len));
}
inline void writeData(OutputPort& p, const std::vector<uint8_t>& d) {
    writeVarint(p, int64_t(d.size()));
    p.write(d);
}

// Generic vector/array serialization
template<typename T, typename ReadFunc>
std::vector<T> readVector(InputPort& p, ReadFunc readElement) {
    int64_t len = readVarint(p);
    if (len <= 0) return {};
    
    std::vector<T> result;
    result.reserve(size_t(len));
    for (int64_t i = 0; i < len; i++) {
        result.push_back(readElement(p));
    }
    return result;
}

template<typename T, typename WriteFunc>
void writeVector(OutputPort& p, const std::vector<T>& vec, WriteFunc writeElement) {
    writeVarint(p, int64_t(vec.size()));
    for (const auto& elem : vec) {
        writeElement(p, elem);
    }
}

// Generic map/dictionary serialization
template<typename K, typename V, typename ReadKeyFunc, typename ReadValueFunc>
std::unordered_map<K, V> readMap(InputPort& p, ReadKeyFunc readKey, ReadValueFunc readValue) {
    int64_t len = readVarint(p);
    if (len <= 0) return {};
    
    std::unordered_map<K, V> result;
    result.reserve(size_t(len));
    for (int64_t i = 0; i < len; i++) {
        K key = readKey(p);
        V value = readValue(p);
        result[std::move(key)] = std::move(value);
    }
    return result;
}

template<typename K, typename V, typename WriteKeyFunc, typename WriteValueFunc>
void writeMap(OutputPort& p, const std::unordered_map<K, V>& map, WriteKeyFunc writeKey, WriteValueFunc writeValue) {
    writeVarint(p, int64_t(map.size()));
    for (const auto& [key, value] : map) {
        writeKey(p, key);
        writeValue(p, value);
    }
}

// Optional serialization
template<typename T, typename ReadFunc>
std::optional<T> readOptional(InputPort& p, ReadFunc readValue) {
    uint8_t hasValue = p.readByte();
    if (hasValue == 0) return std::nullopt;
    return readValue(p);
}

template<typename T, typename WriteFunc>
void writeOptional(OutputPort& p, const std::optional<T>& opt, WriteFunc writeValue) {
    if (!opt.has_value()) {
        p.writeByte(0);
    } else {
        p.writeByte(1);
        writeValue(p, *opt);
    }
}

} // namespace Noise
