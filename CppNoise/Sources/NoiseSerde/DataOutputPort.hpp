// DataOutputPort.hpp - In-memory Output Port

#pragma once

#include "Port.hpp"

namespace Noise {

class DataOutputPort : public OutputPort {
    std::vector<uint8_t> data_;
public:
    void writeByte(uint8_t byte) override { data_.push_back(byte); }
    void write(const uint8_t* data, size_t count) override { data_.insert(data_.end(), data, data + count); }
    void flush() override {}
    const std::vector<uint8_t>& data() const { return data_; }
    void clear() { data_.clear(); }
};

} // namespace Noise
