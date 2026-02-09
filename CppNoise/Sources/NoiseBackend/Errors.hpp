// Errors.hpp - Enhanced error handling for CppNoise

#pragma once

#include <stdexcept>
#include <string>

namespace Noise {

// Base exception for all Noise errors
class NoiseError : public std::runtime_error {
public:
    explicit NoiseError(const std::string& message) 
        : std::runtime_error(message) {}
};

// Future-related errors
class FutureCanceled : public NoiseError {
public:
    FutureCanceled() : NoiseError("Future was canceled") {}
};

class FutureTimeout : public NoiseError {
public:
    FutureTimeout() : NoiseError("Future wait timed out") {}
};

class FutureRejected : public NoiseError {
public:
    explicit FutureRejected(const std::string& reason)
        : NoiseError("Future rejected: " + reason) {}
};

// Callback-related errors
class CallbackNotFound : public NoiseError {
public:
    explicit CallbackNotFound(uint64_t id)
        : NoiseError("Callback not found: " + std::to_string(id)) {}
};

class CallbackAlreadyRegistered : public NoiseError {
public:
    explicit CallbackAlreadyRegistered(uint64_t id)
        : NoiseError("Callback already registered: " + std::to_string(id)) {}
};

// Serialization errors
class SerializationError : public NoiseError {
public:
    explicit SerializationError(const std::string& message)
        : NoiseError("Serialization error: " + message) {}
};

class DeserializationError : public NoiseError {
public:
    explicit DeserializationError(const std::string& message)
        : NoiseError("Deserialization error: " + message) {}
};

// Port I/O errors
class EndOfStream : public NoiseError {
public:
    EndOfStream() : NoiseError("End of stream reached") {}
};

class IOError : public NoiseError {
public:
    explicit IOError(const std::string& message)
        : NoiseError("I/O error: " + message) {}
};

} // namespace Noise
