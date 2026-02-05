// NoiseBoot.hpp - Boot file path configuration for Windows
// Mirrors SwiftNoise/Sources/NoiseBoot_macOS/NoiseBoot.swift

#pragma once

#include <string>

#if defined(_M_ARM64)
#define ARCH "arm64"
#elif defined(_M_AMD64) || defined(_M_X64)
#define ARCH "x86_64"
#else
#error "Unsupported architecture"
#endif
#define OS "windows"

namespace Noise {

/// Boot file paths for Windows.
/// Set bootDir before initializing Racket to customize boot file location.
struct NoiseBoot {
    static inline std::string bootDir = "./boot/" ARCH "-" OS;

    static std::string getPetitePath() { return bootDir + "/petite.boot"; }
    static std::string getSchemePath() { return bootDir + "/scheme.boot"; }
    static std::string getRacketPath() { return bootDir + "/racket.boot"; }
};

} // namespace Noise

