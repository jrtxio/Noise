// Port.hpp - Input/Output Port Interfaces
// Mirrors SwiftNoise/Sources/NoiseSerde/Port.swift

#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

namespace Noise {

/// Protocol for readable ports.
class InputPort {
public:
    virtual ~InputPort() = default;

    /// Reads a single byte from the port.
    virtual uint8_t readByte() = 0;

    /// Reads `count` bytes from the port.
    virtual std::vector<uint8_t> read(size_t count) = 0;
};

/// Protocol for writable ports.
class OutputPort {
public:
    virtual ~OutputPort() = default;

    /// Writes a single byte to the port.
    virtual void writeByte(uint8_t byte) = 0;

    /// Writes bytes to the port.
    virtual void write(const uint8_t* data, size_t count) = 0;

    /// Writes a vector of bytes to the port.
    void write(const std::vector<uint8_t>& data) {
        write(data.data(), data.size());
    }

    /// Flushes the port.
    virtual void flush() = 0;
};

} // namespace Noise
