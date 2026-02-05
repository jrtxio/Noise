// Callout.hpp - Callout Support
// Mirrors SwiftNoise/Sources/NoiseBackend/Callout.swift

#pragma once

#include <functional>
#include <atomic>

namespace Noise {

/// A callable wrapper that can be invoked from Racket.
class Callout {
public:
    using Handler = std::function<void()>;

    Callout() = default;
    explicit Callout(Handler handler) : handler_(std::move(handler)) {}

    void operator()() const {
        if (handler_) {
            handler_();
        }
    }

    explicit operator bool() const {
        return static_cast<bool>(handler_);
    }

private:
    Handler handler_;
};

} // namespace Noise
