// NoiseBoot.hpp - Boot file path configuration for Windows
// Mirrors SwiftNoise/Sources/NoiseBoot_macOS/NoiseBoot.swift

#pragma once

#include <string>
#include <filesystem>

namespace Noise {

/// Boot file paths for Windows.
struct NoiseBoot {
    /// Returns the path to petite.boot
    static std::string getPetitePath() {
        return getBootDirectory() + "/petite.boot";
    }

    /// Returns the path to scheme.boot
    static std::string getSchemePath() {
        return getBootDirectory() + "/scheme.boot";
    }

    /// Returns the path to racket.boot
    static std::string getRacketPath() {
        return getBootDirectory() + "/racket.boot";
    }

    /// Returns the boot directory path.
    /// Override this to customize boot file location.
    static std::string getBootDirectory() {
        // Default: relative to executable
        // Users can override by setting the static bootDir before initialization
        if (!bootDir.empty()) {
            return bootDir;
        }
        return getDefaultBootDirectory();
    }

    /// Sets a custom boot directory.
    static void setBootDirectory(const std::string& path) {
        bootDir = path;
    }

private:
    static inline std::string bootDir;

    static std::string getDefaultBootDirectory() {
        // Default: relative to CWD for now, can be improved to be relative to DLL/Exe
        // This expects the 'boot' folder to be in the current working directory
        return "./Sources/NoiseBoot_Windows/boot/x86_64-windows";
    }
};

} // namespace Noise
