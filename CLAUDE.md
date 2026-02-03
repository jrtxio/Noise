# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Noise is a multi-language wrapper around the Racket CS runtime for simplifying embedding. The project consists of:
- **Swift/**: Primary implementation with Noise (core runtime), NoiseSerde (data serialization), and NoiseBackend (client-server)
- **Racket/**: Racket packages for serialization and backend support
- **CSharp/**: C# implementation of similar functionality

## Development Commands

### Building
```bash
# Build all artifacts (xcframeworks, compiled modules)
make

# Build Swift package
swift build

# Clean build artifacts
make clean
```

### Testing
```bash
# Run all tests
swift test

# Run specific test (use swift test --filter for specific tests)
```

### Racket Package Installation
```bash
# Install noise-serde packages locally
raco pkg install Racket/noise-serde-lib/
raco pkg install Racket/noise-serde-doc/

# View documentation
raco docs noise
```

### Updating Racket Binaries

The shared libraries in `Swift/Lib/` and boot files in `Swift/Sources/Noise/boot/` must match your Racket version. To update:

```bash
# Build Racket from source first, then:
./Bin/copy-libs.sh <target> /path/to/src/racket

# Targets: arm64-macos, x86_64-macos, arm64-ios, arm64-iphonesimulator
```

Pre-built binaries are available on version-specific branches (e.g., `racket-9.0`, `racket-8.18`).

## Architecture

### Swift Packages Structure
- **Noise**: Core Racket CS runtime embedding
  - Uses platform-specific boot files via `NoiseBoot_iOS` / `NoiseBoot_macOS`
  - Links to RacketCS via xcframeworks (`RacketCS-ios.xcframework`, `RacketCS-macos.xcframework`)
- **NoiseSerde**: Serialization/deserialization between Racket and Swift data structures
- **NoiseBackend**: Client-server implementation where Racket runs in background thread, communicates via pipes

### Racket Packages
- **noise-serde-lib**: Core serialization library with macros for defining shared data structures
- **noise-serde-doc**: Documentation for noise-serde
- **noise-serde-lint-lib**: Linting/validation for noise-serde code

### Threading Model (Critical)
The Racket runtime instance must be created on the "main Racket place" thread. All Racket operations must execute on that thread. Chez Scheme values and primitives may be used from other threads (see `Racket.swift:28-31`).

### Platform Support
- **iOS**: arm64 only (requires portable bytecode build with `--enable-pb`)
- **macOS**: Universal binary (x86_64 + arm64)
- **iPhone Simulator**: arm64 only

## Git LFS

Binary files (`.a` libraries, boot files) are stored via Git LFS. Ensure LFS is installed before cloning:
```bash
git lfs install
git lfs pull
```

## Build Artifacts

- `Swift/RacketCS-ios.xcframework`: iOS RacketCS static library
- `Swift/RacketCS-macos.xcframework`: macOS RacketCS static library (universal)
- `Swift/Tests/NoiseTest/Modules/mods.zo`: Compiled Racket test modules

## CI/CD

- **push.yml**: Runs on every push - builds, runs tests, validates Swift code
- **release-build.yml**: Manual workflow to build Racket from source for specific platforms and create release branches

## Module Testing

Test modules in `Swift/Tests/NoiseTest/Modules/` must be compiled to `.zo` format before running Swift tests. The Makefile handles this automatically.
