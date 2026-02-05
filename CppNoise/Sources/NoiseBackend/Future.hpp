// Future.hpp - Async Future Implementation
// Mirrors SwiftNoise/Sources/NoiseBackend/Future.swift

#pragma once

#include <mutex>
#include <condition_variable>
#include <optional>
#include <variant>
#include <functional>

namespace Noise {

/// A thread-safe future that can be resolved with a value or rejected with an error.
template<typename E, typename T>
class Future {
public:
    Future() = default;

    // Non-copyable
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;

    // Movable
    Future(Future&&) = default;
    Future& operator=(Future&&) = default;

    /// Resolves the future with a value.
    void resolve(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        result_ = std::move(value);
        resolved_ = true;
        cv_.notify_all();
    }

    /// Rejects the future with an error.
    void reject(E error) {
        std::lock_guard<std::mutex> lock(mutex_);
        error_ = std::move(error);
        resolved_ = true;
        cv_.notify_all();
    }

    /// Waits for the future to be resolved or rejected.
    /// Returns the value if resolved, throws if rejected.
    T wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return resolved_; });
        if (error_) {
            throw std::runtime_error("Future rejected");
        }
        return std::move(*result_);
    }

    /// Returns true if the future is resolved.
    bool isResolved() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return resolved_;
    }

    /// Returns the error if rejected, nullopt otherwise.
    std::optional<E> error() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return error_;
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::optional<T> result_;
    std::optional<E> error_;
    bool resolved_ = false;
};

} // namespace Noise
