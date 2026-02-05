// Port.hpp - Input/Output Port Interfaces

#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace Noise {

class InputPort {
public:
    virtual ~InputPort() = default;
    virtual uint8_t readByte() = 0;
    virtual std::vector<uint8_t> read(size_t count) = 0;
};

class OutputPort {
public:
    virtual ~OutputPort() = default;
    virtual void writeByte(uint8_t byte) = 0;
    virtual void write(const uint8_t* data, size_t count) = 0;
    void write(const std::vector<uint8_t>& data) { write(data.data(), data.size()); }
    virtual void flush() = 0;
};

} // namespace Noise
