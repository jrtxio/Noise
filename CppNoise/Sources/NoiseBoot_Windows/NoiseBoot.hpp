// NoiseBoot.hpp - Boot file path configuration for Windows
// Mirrors SwiftNoise/Sources/NoiseBoot_macOS/NoiseBoot.swift

#pragma once

#include <string>

#define ARCH "x86_64"
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

