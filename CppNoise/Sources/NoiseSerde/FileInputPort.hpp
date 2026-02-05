// FileInputPort.hpp - File Handle Input Port
// Mirrors SwiftNoise/Sources/NoiseSerde/FileHandleInputPort.swift

#pragma once

#include "Port.hpp"
#include <fstream>
#include <cstdio>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#include <unistd.h>
#endif

namespace Noise {

/// An input port backed by a file descriptor.
class FileInputPort : public InputPort {
public:
    explicit FileInputPort(int fd) : fd_(fd) {}

    uint8_t readByte() override {
        uint8_t byte;
        #ifdef _WIN32
        int result = _read(fd_, &byte, 1);
        #else
        ssize_t result = ::read(fd_, &byte, 1);
        #endif
        if (result != 1) {
            throw std::runtime_error("Failed to read byte from file");
        }
        return byte;
    }

    std::vector<uint8_t> read(size_t count) override {
        std::vector<uint8_t> buffer(count);
        #ifdef _WIN32
        int result = _read(fd_, buffer.data(), static_cast<unsigned int>(count));
        #else
        ssize_t result = ::read(fd_, buffer.data(), count);
        #endif
        if (result < 0) {
            throw std::runtime_error("Failed to read from file");
        }
        buffer.resize(static_cast<size_t>(result));
        return buffer;
    }

private:
    int fd_;
};

} // namespace Noise
