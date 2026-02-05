// main.cpp - CppNoise Demo
// Mirrors SwiftNoise/Tests/NoiseTest

#include <iostream>
#include <cassert>
#include <cmath>

#include "Noise/Racket.hpp"
#include "NoiseSerde/Serde.hpp"
#include "NoiseSerde/DataInputPort.hpp"
#include "NoiseSerde/DataOutputPort.hpp"

using namespace Noise;

// Helper macros
#define TEST(name) void test_##name()
#define RUN(name) do { std::cout << "  " #name "... "; test_##name(); std::cout << "OK" << std::endl; } while(0)
#define ASSERT_EQ(a, b) do { if ((a) != (b)) { std::cerr << "FAIL: " << (a) << " != " << (b) << std::endl; assert(false); } } while(0)

// ============================================================================
// Serde Tests (mirrors SerdeTest.swift)
// ============================================================================

TEST(bool_roundtrip) {
    DataOutputPort out;
    writeBool(out, true);
    writeBool(out, false);
    DataInputPort in(out.data());
    ASSERT_EQ(readBool(in), true);
    ASSERT_EQ(readBool(in), false);
}

TEST(varint_roundtrip) {
    std::vector<int64_t> tests = {0, 1, -1, 0x7F, -0x7F, 0x80, -0x80, 0xFF, -0xFF, 0xFFF, -0xFFF, 0xFFFFF, -0xFFFFF};
    DataOutputPort out;
    for (auto n : tests) writeVarint(out, n);
    DataInputPort in(out.data());
    for (auto n : tests) ASSERT_EQ(readVarint(in), n);
}

TEST(uvarint_roundtrip) {
    std::vector<uint64_t> tests = {0, 1, 0x7F, 0x80, 0xFF, 0xFFF, 0xFFFFF};
    DataOutputPort out;
    for (auto n : tests) writeUVarint(out, n);
    DataInputPort in(out.data());
    for (auto n : tests) ASSERT_EQ(readUVarint(in), n);
}

TEST(int32_roundtrip) {
    std::vector<int32_t> tests = {0, 0xFF, -0xFF, 0x7FFFFFFF, -0x7FFFFFFF};
    DataOutputPort out;
    for (auto n : tests) writeInt32(out, n);
    DataInputPort in(out.data());
    for (auto n : tests) ASSERT_EQ(readInt32(in), n);
}

TEST(float32_roundtrip) {
    std::vector<float> tests = {0.0f, 0.5f, 1.25f, -5.0f};
    DataOutputPort out;
    for (auto n : tests) writeFloat32(out, n);
    DataInputPort in(out.data());
    for (auto n : tests) ASSERT_EQ(readFloat32(in), n);
}

TEST(float64_roundtrip) {
    std::vector<double> tests = {0.0, 0.5, 1.25, -5.0};
    DataOutputPort out;
    for (auto n : tests) writeFloat64(out, n);
    DataInputPort in(out.data());
    for (auto n : tests) ASSERT_EQ(readFloat64(in), n);
}

TEST(string_roundtrip) {
    std::vector<std::string> tests = {"", "hello", "hello, world!", "你好世界"};
    DataOutputPort out;
    for (const auto& s : tests) writeString(out, s);
    DataInputPort in(out.data());
    for (const auto& s : tests) ASSERT_EQ(readString(in), s);
}

TEST(data_roundtrip) {
    std::vector<uint8_t> data = {1, 2, 128, 255};
    DataOutputPort out;
    writeData(out, data);
    DataInputPort in(out.data());
    auto result = readData(in);
    ASSERT_EQ(result.size(), data.size());
    for (size_t i = 0; i < data.size(); i++) ASSERT_EQ(result[i], data[i]);
}

void run_serde_tests() {
    std::cout << "Serde Tests:" << std::endl;
    RUN(bool_roundtrip);
    RUN(varint_roundtrip);
    RUN(uvarint_roundtrip);
    RUN(int32_roundtrip);
    RUN(float32_roundtrip);
    RUN(float64_roundtrip);
    RUN(string_roundtrip);
    RUN(data_roundtrip);
}

// ============================================================================
// Racket Tests (mirrors RacketTest.swift)
// ============================================================================

TEST(val_creation) {
    // Test basic Val creation
    auto nil = Val::null();
    auto t = Val::t();
    auto f = Val::f();
    auto num = Val::fixnum(42);
    auto sym = Val::symbol("hello");
    auto str = Val::string("world");
    auto pair = Val::cons(sym, str);

    ASSERT_EQ(num.isFixnum(), true);
    ASSERT_EQ(num.fixnumValue(), 42);
    ASSERT_EQ(pair.isPair(), true);
}

TEST(val_pair_operations) {
    auto a = Val::fixnum(1);
    auto b = Val::fixnum(2);
    auto pair = Val::cons(a, b);
    ASSERT_EQ(pair.car().fixnumValue(), 1);
    ASSERT_EQ(pair.cdr().fixnumValue(), 2);
}

TEST(val_list_building) {
    // Build a list: (1 2 3)
    auto list = Val::cons(Val::fixnum(1),
                Val::cons(Val::fixnum(2),
                Val::cons(Val::fixnum(3), Val::null())));
    ASSERT_EQ(list.car().fixnumValue(), 1);
    ASSERT_EQ(list.cdr().car().fixnumValue(), 2);
    ASSERT_EQ(list.cdr().cdr().car().fixnumValue(), 3);
}

void run_racket_tests() {
    std::cout << "Racket Value Tests:" << std::endl;
    
    Racket r;
    r.bracket([&]() {
        RUN(val_creation);
        RUN(val_pair_operations);
        RUN(val_list_building);
        return 0;
    });
}

// ============================================================================
// Main
// ============================================================================

int main() {
    std::cout << "=== CppNoise Demo ===" << std::endl;
    std::cout << std::endl;

    try {
        run_serde_tests();
        std::cout << std::endl;
        run_racket_tests();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "=== All Tests Passed ===" << std::endl;
    return 0;
}
