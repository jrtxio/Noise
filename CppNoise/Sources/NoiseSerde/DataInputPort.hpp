// DataInputPort.hpp - In-memory Input Port

#pragma once

#include "Port.hpp"

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

    std::vector<uint8_t> read(size_t count) override {
        size_t n = std::min(count, data_.size() - pos_);
        std::vector<uint8_t> result(data_.begin() + pos_, data_.begin() + pos_ + n);
        pos_ += n;
        return result;
    }
};

} // namespace Noise
