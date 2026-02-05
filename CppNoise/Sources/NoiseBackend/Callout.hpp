// Callout.hpp - Callback Support

#pragma once

#include <functional>

namespace Noise {

// Callable wrapper that can be invoked from Racket.
class Callout {
    std::function<void()> handler_;
public:
    Callout() = default;
    explicit Callout(std::function<void()> handler) : handler_(std::move(handler)) {}
    void operator()() const { if (handler_) handler_(); }
    explicit operator bool() const { return static_cast<bool>(handler_); }
};

} // namespace Noise
