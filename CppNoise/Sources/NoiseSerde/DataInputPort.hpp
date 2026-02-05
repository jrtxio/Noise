// DataInputPort.hpp - In-memory Input Port
// Mirrors SwiftNoise/Sources/NoiseSerde/DataInputPort.swift

#pragma once

#include "Port.hpp"
#include <vector>
#include <cstddef>

namespace Noise {

/// An input port backed by an in-memory buffer.
class DataInputPort : public InputPort {
public:
    explicit DataInputPort(std::vector<uint8_t> data)
        : data_(std::move(data)), pos_(0) {}

    uint8_t readByte() override {
        if (pos_ >= data_.size()) {
            throw std::runtime_error("End of data");
        }
        return data_[pos_++];
    }

    std::vector<uint8_t> read(size_t count) override {
        size_t available = data_.size() - pos_;
        size_t toRead = std::min(count, available);
        std::vector<uint8_t> result(data_.begin() + pos_, data_.begin() + pos_ + toRead);
        pos_ += toRead;
        return result;
    }

private:
    std::vector<uint8_t> data_;
    size_t pos_;
};

} // namespace Noise
