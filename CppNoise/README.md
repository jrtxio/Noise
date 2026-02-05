# CppNoise

C++ implementation of the Noise library, mirroring SwiftNoise structure for Windows.

## Project Structure

```
CppNoise/
├── Makefile                # Build configuration
├── Bin/
│   └── copy-libs.sh        # Copy Racket libs script
├── Lib/
│   └── include/            # Racket headers
├── Sources/
│   ├── Noise/              # Core Racket bindings
│   ├── NoiseBackend/       # Backend client
│   ├── NoiseBoot_Windows/  # Boot file paths
│   └── NoiseSerde/         # Serialization
├── Template/               # App template
└── Tests/
```

## Setup

1. Build Racket for Windows
2. Run `./Bin/copy-libs.sh x86_64-windows /path/to/racket` to copy headers and libraries
3. Run `make` to build

## Usage

```cpp
#include "Noise/Racket.hpp"

int main() {
    Noise::NoiseBoot::setBootDirectory("path/to/boot");
    Noise::Racket r;

    r.bracket([&]() {
        r.load("backend.zo");
        auto mod = Noise::Val::cons(
            Noise::Val::symbol("quote"),
            Noise::Val::cons(Noise::Val::symbol("mymod"), Noise::Val::null())
        );
        auto proc = r.require(Noise::Val::symbol("serve"), mod);
        // ...
    });

    return 0;
}
```
