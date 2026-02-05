// FileOutputPort.hpp - File Descriptor Output Port

#pragma once

#include "Port.hpp"

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace Noise {

class FileOutputPort : public OutputPort {
    int fd_;
public:
    explicit FileOutputPort(int fd) : fd_(fd) {}

    void writeByte(uint8_t byte) override {
        #ifdef _WIN32
        _write(fd_, &byte, 1);
        #else
        ::write(fd_, &byte, 1);
        #endif
    }

    void write(const uint8_t* data, size_t count) override {
        #ifdef _WIN32
        _write(fd_, data, static_cast<unsigned>(count));
        #else
        ::write(fd_, data, count);
        #endif
    }

    void flush() override {
        #ifdef _WIN32
        _commit(fd_);
        #else
        ::fsync(fd_);
        #endif
    }
};

} // namespace Noise
