// Callout.hpp - Callback Support for Racket-to-C++ communication

#pragma once

#include "NoiseSerde/Port.hpp"
#include "NoiseSerde/DataInputPort.hpp"
#include "Future.hpp"
#include <functional>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <cstdint>
#include <vector>

namespace Noise {

// Global callback registry
class CallbackRegistry {
    static std::mutex mutex_;
    static std::unordered_map<uint64_t, std::function<void(InputPort&)>> callbacks_;

public:
    static void registerCallback(uint64_t id, std::function<void(InputPort&)> callback) {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_[id] = std::move(callback);
    }

    static void unregisterCallback(uint64_t id) {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.erase(id);
    }

    static std::function<void(InputPort&)> getCallback(uint64_t id) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = callbacks_.find(id);
        if (it != callbacks_.end()) {
            return it->second;
        }
        return nullptr;
    }
};

// Static member initialization (should be in .cpp, but for header-only we do it here)
inline std::mutex CallbackRegistry::mutex_;
inline std::unordered_map<uint64_t, std::function<void(InputPort&)>> CallbackRegistry::callbacks_;

// C function bridge for Racket to call
extern "C" {
    inline void callbackHandler(uint64_t id, int len, const char* data) {
        auto callback = CallbackRegistry::getCallback(id);
        if (!callback) {
            // Callback not found - this is an error but we can't throw across C boundary
            return;
        }

        // Create InputPort from data
        std::vector<uint8_t> buffer(data, data + len);
        DataInputPort port(std::move(buffer));
        
        // Execute callback
        callback(port);
    }
}

// Install a callback that can be invoked from Racket
// Returns a future that completes when the callback is registered
template<typename RpcFunc>
std::shared_ptr<Future<std::string, void>> installCallback(
    uint64_t id,
    RpcFunc rpc,
    std::function<void(InputPort&)> callback
) {
    // Register the callback
    CallbackRegistry::registerCallback(id, std::move(callback));
    
    // Get the address of the callback handler
    int64_t handlerAddr = reinterpret_cast<int64_t>(&callbackHandler);
    
    // Call the RPC to register on Racket side
    return rpc(id, handlerAddr);
}

// Uninstall a callback
inline void uninstallCallback(uint64_t id) {
    CallbackRegistry::unregisterCallback(id);
}

// Simple callable wrapper (for compatibility with existing code)
class Callout {
    std::function<void()> handler_;
public:
    Callout() = default;
    explicit Callout(std::function<void()> handler) : handler_(std::move(handler)) {}
    void operator()() const { if (handler_) handler_(); }
    explicit operator bool() const { return static_cast<bool>(handler_); }
};

} // namespace Noise
