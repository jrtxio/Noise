// Backend.cpp - HN Backend implementation (Noise/Chez Scheme headers isolated here)
//
// This file is the ONLY place that includes Chez Scheme / Noise headers.
// It must NOT include pch.h or any WinRT headers — they conflict with
// Chez Scheme's typedef of `ptr` and macros like EXPORT, UNLOCK, etc.

#include "NoiseBoot_Windows/NoiseBoot.hpp"
#include "NoiseBackend/Backend.hpp"
#include "NoiseSerde/Serde.hpp"
#include "Backend.hpp"

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

namespace HN {

// Deserialization helpers (called within the Noise reader thread).
static Comment readComment(Noise::InputPort& inp) {
    return Comment{
        Noise::readUVarint(inp),
        Noise::readString(inp),
        Noise::readString(inp),
        Noise::readString(inp)
    };
}

static Story readStory(Noise::InputPort& inp) {
    return Story{
        Noise::readUVarint(inp),
        Noise::readString(inp),
        Noise::readVector<uint64_t>(inp, Noise::readUVarint)
    };
}

// Pimpl holds the Noise::Backend instance.
struct HNBackend::Impl {
    std::unique_ptr<Noise::Backend> backend;

    Impl(const std::string& zoPath) {
        Noise::NoiseBoot::boot();
        backend = std::make_unique<Noise::Backend>(zoPath, "main", "main");
    }
};

HNBackend::HNBackend(const std::string& zoPath)
    : impl_(std::make_unique<Impl>(zoPath)) {}

HNBackend::~HNBackend() = default;

void HNBackend::getTopStories(StoriesCallback onSuccess, ErrorCallback onError) {
    auto future = impl_->backend->send(
        [](Noise::OutputPort& out) {
            Noise::writeUVarint(out, 0x0001);
        },
        [](Noise::InputPort& inp) -> std::vector<Story> {
            return Noise::readVector<Story>(inp, readStory);
        }
    );
    future->sink(
        [onSuccess = std::move(onSuccess)](std::vector<Story> s) { onSuccess(std::move(s)); },
        [onError = std::move(onError)](std::string e) { onError(std::move(e)); }
    );
}

void HNBackend::getComments(uint64_t itemId, CommentsCallback onSuccess, ErrorCallback onError) {
    auto future = impl_->backend->send(
        [itemId](Noise::OutputPort& out) {
            Noise::writeUVarint(out, 0x0000);
            Noise::writeUVarint(out, itemId);
        },
        [](Noise::InputPort& inp) -> std::vector<Comment> {
            return Noise::readVector<Comment>(inp, readComment);
        }
    );
    future->sink(
        [onSuccess = std::move(onSuccess)](std::vector<Comment> c) { onSuccess(std::move(c)); },
        [onError = std::move(onError)](std::string e) { onError(std::move(e)); }
    );
}

std::string resolveZoPath() {
#ifdef _WIN32
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    std::filesystem::path p(exePath);
    auto dir = p.parent_path();
#if defined(_M_ARM64)
    auto zo = dir / "res" / "core-arm64.zo";
#else
    auto zo = dir / "res" / "core-x86_64.zo";
#endif
    return zo.string();
#else
    return "./res/core.zo";
#endif
}

} // namespace HN
