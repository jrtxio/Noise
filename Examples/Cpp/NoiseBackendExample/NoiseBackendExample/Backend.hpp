// Backend.hpp - RPC bindings for Hacker News backend
// Hand-written to match the Racket RPC definitions in core/main.rkt

#pragma once

#include "Model.hpp"
#include "NoiseBackend/Backend.hpp"
#include "NoiseBackend/Future.hpp"

#include <string>
#include <memory>
#include <filesystem>

namespace NoiseBackendExample {

// RPC command IDs (must match the order defined in main.rkt)
constexpr uint64_t RPC_GET_COMMENTS = 0x0000;
constexpr uint64_t RPC_GET_TOP_STORIES = 0x0001;

// Backend client for Hacker News example
class Backend {
    std::unique_ptr<Noise::Backend> impl_;

public:
    Backend(const std::string& zoPath, const std::string& modName, const std::string& procName)
        : impl_(std::make_unique<Noise::Backend>(zoPath, modName, procName)) {}

    // Get top stories from Hacker News
    auto getTopStories() {
        return impl_->send(
            [](Noise::OutputPort& out) {
                Noise::writeUVarint(out, RPC_GET_TOP_STORIES);
            },
            [](Noise::InputPort& inp) {
                return readList<Story>(inp);
            }
        );
    }

    // Get comments for a specific item
    auto getComments(uint64_t itemId) {
        return impl_->send(
            [itemId](Noise::OutputPort& out) {
                Noise::writeUVarint(out, RPC_GET_COMMENTS);
                Noise::writeUVarint(out, itemId);
            },
            [](Noise::InputPort& inp) {
                return readList<Comment>(inp);
            }
        );
    }

    Noise::BackendStats stats() const {
        return impl_->stats();
    }
};

// Determine architecture string for resource paths
#if defined(_M_X64) || defined(__x86_64__)
    constexpr const char* ARCH = "x86_64";
#elif defined(_M_ARM64) || defined(__aarch64__)
    constexpr const char* ARCH = "arm64";
#else
    constexpr const char* ARCH = "unknown";
#endif

// Helper to create Backend with default resource paths
inline std::unique_ptr<Backend> createBackend(const std::filesystem::path& resourceDir) {
    auto zoPath = resourceDir / ("core-" + std::string(ARCH) + ".zo");
    return std::make_unique<Backend>(zoPath.string(), "main", "main");
}

} // namespace NoiseBackendExample
