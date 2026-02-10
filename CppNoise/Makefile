# CppNoise Build System
# Header-only library

CXX = cl
CXXFLAGS = /std:c++20 /EHsc /W4 /I Lib/include /I Sources

# Output
BUILD_DIR = build

.PHONY: all clean tests

all: tests

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Tests
tests: $(BUILD_DIR) \
	$(BUILD_DIR)/FutureTest.exe \
	$(BUILD_DIR)/SerdeTest.exe \
	$(BUILD_DIR)/CoroutineTest.exe

$(BUILD_DIR)/FutureTest.exe: Tests/FutureTest.cpp
	$(CXX) $(CXXFLAGS) Tests/FutureTest.cpp /Fo$(BUILD_DIR)/FutureTest.obj /Fe$@

$(BUILD_DIR)/SerdeTest.exe: Tests/SerdeTest.cpp
	$(CXX) $(CXXFLAGS) Tests/SerdeTest.cpp /Fo$(BUILD_DIR)/SerdeTest.obj /Fe$@

$(BUILD_DIR)/CoroutineTest.exe: Tests/CoroutineTest.cpp
	$(CXX) $(CXXFLAGS) Tests/CoroutineTest.cpp /Fo$(BUILD_DIR)/CoroutineTest.obj /Fe$@

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
