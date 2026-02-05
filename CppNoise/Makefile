# CppNoise Build System
# Mirrors SwiftNoise structure for Windows

CXX = cl
CXXFLAGS = /std:c++20 /EHsc /W4 /I Lib/include /I Sources

ARCH = x86_64-windows

# Source files
NOISE_SOURCES = Sources/Noise/Racket.cpp
SERDE_SOURCES = Sources/NoiseSerde/Port.cpp
BACKEND_SOURCES = Sources/NoiseBackend/Backend.cpp

# Output
BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib

.PHONY: all clean

all: $(LIB_DIR)/Noise.lib $(LIB_DIR)/NoiseSerde.lib $(LIB_DIR)/NoiseBackend.lib

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_DIR)/Noise.lib: $(NOISE_SOURCES) | $(LIB_DIR)
	$(CXX) $(CXXFLAGS) /c $(NOISE_SOURCES) /Fo$(BUILD_DIR)/
	lib /OUT:$@ $(BUILD_DIR)/*.obj

$(LIB_DIR)/NoiseSerde.lib: $(SERDE_SOURCES) | $(LIB_DIR)
	$(CXX) $(CXXFLAGS) /c $(SERDE_SOURCES) /Fo$(BUILD_DIR)/
	lib /OUT:$@ $(BUILD_DIR)/*.obj

$(LIB_DIR)/NoiseBackend.lib: $(BACKEND_SOURCES) | $(LIB_DIR)
	$(CXX) $(CXXFLAGS) /c $(BACKEND_SOURCES) /Fo$(BUILD_DIR)/
	lib /OUT:$@ $(BUILD_DIR)/*.obj

clean:
	rm -rf $(BUILD_DIR)
