// NoiseBoot.hpp - Boot file path configuration for Windows
// Mirrors SwiftNoise/Sources/NoiseBoot_macOS/NoiseBoot.swift

#pragma once

#include <string>

#ifdef _WIN32
#include "chezscheme-x86_64-windows.h"
#else
#error "Unsupported platform"
#endif
#include "racketcs.h"

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

    /// Initialize the Racket runtime with configured boot files.
    static void boot() {
        racket_boot_arguments_t args = {};
        std::string petite = getPetitePath();
        std::string scheme = getSchemePath();
        std::string racket = getRacketPath();
        args.exec_file = const_cast<char*>("racket");
        args.boot1_path = const_cast<char*>(petite.c_str());
        args.boot2_path = const_cast<char*>(scheme.c_str());
        args.boot3_path = const_cast<char*>(racket.c_str());
        racket_boot(&args);
        Sdeactivate_thread();
    }
};

} // namespace Noise

