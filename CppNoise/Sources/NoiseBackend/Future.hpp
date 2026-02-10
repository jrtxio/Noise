// Future.hpp - Thread-safe Future with chaining support

#pragma once

#include <mutex>
#include <condition_variable>
#include <optional>
#include <functional>
#include <memory>
#include <thread>
#include <chrono>
#include <coroutine>
#include <stdexcept>
#include <string>

namespace Noise {

// Thread-safe future that can be resolved with a value or rejected with an error.
template<typename E, typename T>
class Future : public std::enable_shared_from_this<Future<E, T>> {
public:
    // Error types (mirrors Swift's Future.Canceled / Future.WaitError)
    struct Canceled : std::runtime_error {
        Canceled() : std::runtime_error("Future was canceled") {}
    };

    struct Rejected : std::runtime_error {
        explicit Rejected(const std::string& reason)
            : std::runtime_error("Future rejected: " + reason) {}
    };

private:
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::optional<T> result_;
    std::optional<E> error_;
    bool resolved_ = false;
    bool canceled_ = false;

public:
    Future() = default;
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;
    Future(Future&&) = default;
    Future& operator=(Future&&) = default;

    void resolve(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (resolved_ || canceled_) return;
        result_ = std::move(value);
        resolved_ = true;
        cv_.notify_all();
    }

    void reject(E error) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (resolved_ || canceled_) return;
        error_ = std::move(error);
        resolved_ = true;
        cv_.notify_all();
    }

    void cancel() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (resolved_) return;
        canceled_ = true;
        resolved_ = true;
        cv_.notify_all();
    }

    T wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return resolved_; });
        if (canceled_) throw Canceled();
        if (error_) throw Rejected("Future rejected with error");
        return std::move(*result_);
    }

    template<typename Rep, typename Period>
    std::optional<T> wait_for(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (cv_.wait_for(lock, timeout, [this] { return resolved_; })) {
            if (canceled_) throw Canceled();
            if (error_) throw Rejected("Future rejected");
            return std::move(*result_);
        }
        return std::nullopt;
    }

    template<typename Clock, typename Duration>
    std::optional<T> wait_until(const std::chrono::time_point<Clock, Duration>& deadline) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (cv_.wait_until(lock, deadline, [this] { return resolved_; })) {
            if (canceled_) throw Canceled();
            if (error_) throw Rejected("Future rejected");
            return std::move(*result_);
        }
        return std::nullopt;
    }

    bool isResolved() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return resolved_;
    }

    bool isCanceled() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return canceled_;
    }

    std::optional<E> error() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return error_;
    }

    // Map the result value to a new type.
    template<typename R>
    std::shared_ptr<Future<E, R>> map(std::function<R(T)> fn) {
        auto future = std::make_shared<Future<E, R>>();
        std::thread([self = this->shared_from_this(), future, fn = std::move(fn)]() {
            try {
                T value = self->wait();
                future->resolve(fn(std::move(value)));
            } catch (const Canceled&) {
                future->cancel();
            } catch (const std::exception&) {
                if (auto err = self->error()) {
                    future->reject(*err);
                }
            }
        }).detach();
        return future;
    }

    // Map the error to a new error type.
    template<typename E2>
    std::shared_ptr<Future<E2, T>> mapError(std::function<E2(E)> fn) {
        auto future = std::make_shared<Future<E2, T>>();
        std::thread([self = this->shared_from_this(), future, fn = std::move(fn)]() {
            try {
                T value = self->wait();
                future->resolve(std::move(value));
            } catch (const Canceled&) {
                future->cancel();
            } catch (const std::exception&) {
                if (auto err = self->error()) {
                    future->reject(fn(*err));
                }
            }
        }).detach();
        return future;
    }

    // Chain futures together.
    template<typename R>
    std::shared_ptr<Future<E, R>> andThen(std::function<std::shared_ptr<Future<E, R>>(T)> fn) {
        auto future = std::make_shared<Future<E, R>>();
        std::thread([self = this->shared_from_this(), future, fn = std::move(fn)]() {
            try {
                T value = self->wait();
                auto next = fn(std::move(value));
                try {
                    R result = next->wait();
                    future->resolve(std::move(result));
                } catch (const typename Future<E, R>::Canceled&) {
                    future->cancel();
                } catch (const std::exception&) {
                    if (auto err = next->error()) {
                        future->reject(*err);
                    }
                }
            } catch (const Canceled&) {
                future->cancel();
            } catch (const std::exception&) {
                if (auto err = self->error()) {
                    future->reject(*err);
                }
            }
        }).detach();
        return future;
    }

    // Execute callbacks when future completes.
    void sink(
        std::function<void(T)> onComplete,
        std::function<void(E)> onError = nullptr,
        std::function<void()> onCancel = nullptr
    ) {
        std::thread([self = this->shared_from_this(),
                    onComplete = std::move(onComplete),
                    onError = std::move(onError),
                    onCancel = std::move(onCancel)]() {
            try {
                T value = self->wait();
                if (onComplete) onComplete(std::move(value));
            } catch (const Canceled&) {
                if (onCancel) onCancel();
            } catch (const std::exception&) {
                if (onError) {
                    if (auto err = self->error()) {
                        onError(*err);
                    }
                }
            }
        }).detach();
    }

    // Execute callback when future completes successfully.
    void onComplete(std::function<void(T)> callback) {
        sink(std::move(callback), nullptr, nullptr);
    }

    // Factory method: create a resolved future.
    static std::shared_ptr<Future<E, T>> resolved(T value) {
        auto future = std::make_shared<Future<E, T>>();
        future->resolve(std::move(value));
        return future;
    }

    // Factory method: create a rejected future.
    static std::shared_ptr<Future<E, T>> rejected(E error) {
        auto future = std::make_shared<Future<E, T>>();
        future->reject(std::move(error));
        return future;
    }

    // C++20 Coroutine Support
    bool await_ready() const {
        return isResolved();
    }

    void await_suspend(std::coroutine_handle<> h) {
        this->sink([h](T) mutable { h.resume(); },
                   [h](E) mutable { h.resume(); },
                   [h]() mutable { h.resume(); });
    }

    T await_resume() {
        return this->wait();
    }
};

} // namespace Noise
