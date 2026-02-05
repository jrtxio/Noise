// DataOutputPort.hpp - In-memory Output Port
// Mirrors SwiftNoise/Sources/NoiseSerde/DataOutputPort.swift

#pragma once

#include "Port.hpp"
#include <vector>

namespace Noise {

/// An output port backed by an in-memory buffer.
class DataOutputPort : public OutputPort {
public:
    DataOutputPort() = default;

    void writeByte(uint8_t byte) override {
        data_.push_back(byte);
    }

    void write(const uint8_t* data, size_t count) override {
        data_.insert(data_.end(), data, data + count);
    }

    void flush() override {
        // No-op for in-memory port
    }

    /// Returns the accumulated data.
    const std::vector<uint8_t>& data() const { return data_; }

    /// Clears the buffer.
    void clear() { data_.clear(); }

private:
    std::vector<uint8_t> data_;
};

} // namespace Noise
