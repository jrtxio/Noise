// Future.hpp - Thread-safe Future

#pragma once

#include <mutex>
#include <condition_variable>
#include <optional>
#include <stdexcept>

namespace Noise {

// Thread-safe future that can be resolved with a value or rejected with an error.
template<typename E, typename T>
class Future {
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::optional<T> result_;
    std::optional<E> error_;
    bool resolved_ = false;

public:
    Future() = default;
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;
    Future(Future&&) = default;
    Future& operator=(Future&&) = default;

    void resolve(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        result_ = std::move(value);
        resolved_ = true;
        cv_.notify_all();
    }

    void reject(E error) {
        std::lock_guard<std::mutex> lock(mutex_);
        error_ = std::move(error);
        resolved_ = true;
        cv_.notify_all();
    }

    T wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return resolved_; });
        if (error_) throw std::runtime_error("Future rejected");
        return std::move(*result_);
    }

    bool isResolved() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return resolved_;
    }

    std::optional<E> error() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return error_;
    }
};

} // namespace Noise
