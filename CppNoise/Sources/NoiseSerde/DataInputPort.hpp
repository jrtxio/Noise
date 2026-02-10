// DataInputPort.hpp - In-memory Input Port

#pragma once

#include "Port.hpp"
#include <cstring>

namespace Noise {

class DataInputPort : public InputPort {
    std::vector<uint8_t> data_;
    size_t pos_ = 0;
public:
    explicit DataInputPort(std::vector<uint8_t> data) : data_(std::move(data)) {}

    uint8_t readByte() override {
        if (pos_ >= data_.size()) throw std::runtime_error("End of data");
        return data_[pos_++];
    }

    size_t read(uint8_t* buffer, size_t count) override {
        size_t n = std::min(count, data_.size() - pos_);
        std::memcpy(buffer, data_.data() + pos_, n);
        pos_ += n;
        return n;
    }
};

} // namespace Noise
