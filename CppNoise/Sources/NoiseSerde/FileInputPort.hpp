// FileInputPort.hpp - File Descriptor Input Port

#pragma once

#include "Port.hpp"

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace Noise {

class FileInputPort : public InputPort {
    int fd_;
public:
    explicit FileInputPort(int fd) : fd_(fd) {}

    uint8_t readByte() override {
        uint8_t byte;
        #ifdef _WIN32
        if (_read(fd_, &byte, 1) != 1) throw std::runtime_error("Failed to read byte");
        #else
        if (::read(fd_, &byte, 1) != 1) throw std::runtime_error("Failed to read byte");
        #endif
        return byte;
    }

    size_t read(uint8_t* buffer, size_t count) override {
        #ifdef _WIN32
        int n = _read(fd_, buffer, static_cast<unsigned>(count));
        #else
        ssize_t n = ::read(fd_, buffer, count);
        #endif
        if (n < 0) throw std::runtime_error("Failed to read");
        return static_cast<size_t>(n);
    }
};

} // namespace Noise
