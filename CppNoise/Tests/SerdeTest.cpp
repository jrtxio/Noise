// SerdeTest.cpp - Simple test for serialization functionality

#include "NoiseSerde/Serde.hpp"
#include "NoiseSerde/DataInputPort.hpp"
#include "NoiseSerde/DataOutputPort.hpp"
#include "NoiseBackend/Logger.hpp"
#include <iostream>
#include <cassert>

using namespace Noise;

void testBasicTypes() {
    LOG_INFO("Testing basic type serialization...");
    
    DataOutputPort out;
    
    // Write various types
    writeBool(out, true);
    writeInt16(out, -1234);
    writeUInt16(out, 5678);
    writeInt32(out, -123456);
    writeFloat32(out, 3.14159f);
    writeString(out, "Hello, Noise!");
    
    // Read them back
    DataInputPort in(out.data());
    
    assert(readBool(in) == true);
    assert(readInt16(in) == -1234);
    assert(readUInt16(in) == 5678);
    assert(readInt32(in) == -123456);
    assert(std::abs(readFloat32(in) - 3.14159f) < 0.001f);
    assert(readString(in) == "Hello, Noise!");
    
    LOG_INFO("✓ Basic types test PASSED");
}

void testVarint() {
    LOG_INFO("Testing varint serialization...");
    
    DataOutputPort out;
    
    writeVarint(out, 0);
    writeVarint(out, 127);
    writeVarint(out, -128);
    writeVarint(out, 12345);
    writeVarint(out, -9876);
    
    DataInputPort in(out.data());
    
    assert(readVarint(in) == 0);
    assert(readVarint(in) == 127);
    assert(readVarint(in) == -128);
    assert(readVarint(in) == 12345);
    assert(readVarint(in) == -9876);
    
    LOG_INFO("✓ Varint test PASSED");
}

void testVector() {
    LOG_INFO("Testing vector serialization...");
    
    DataOutputPort out;
    
    std::vector<int32_t> vec = {1, 2, 3, 4, 5};
    writeVector<int32_t>(out, vec, [](OutputPort& p, int32_t v) {
        writeInt32(p, v);
    });
    
    DataInputPort in(out.data());
    
    auto result = readVector<int32_t>(in, [](InputPort& p) {
        return readInt32(p);
    });
    
    assert(result.size() == 5);
    assert(result[0] == 1);
    assert(result[4] == 5);
    
    LOG_INFO("✓ Vector test PASSED");
}

void testMap() {
    LOG_INFO("Testing map serialization...");
    
    DataOutputPort out;
    
    std::unordered_map<std::string, int> map = {
        {"one", 1},
        {"two", 2},
        {"three", 3}
    };
    
    writeMap<std::string, int>(out, map,
        [](OutputPort& p, const std::string& k) { writeString(p, k); },
        [](OutputPort& p, int v) { writeInt32(p, v); }
    );
    
    DataInputPort in(out.data());
    
    auto result = readMap<std::string, int>(in,
        [](InputPort& p) { return readString(p); },
        [](InputPort& p) { return readInt32(p); }
    );
    
    assert(result.size() == 3);
    assert(result["one"] == 1);
    assert(result["two"] == 2);
    assert(result["three"] == 3);
    
    LOG_INFO("✓ Map test PASSED");
}

void testOptional() {
    LOG_INFO("Testing optional serialization...");
    
    DataOutputPort out;
    
    std::optional<int> some = 42;
    std::optional<int> none = std::nullopt;
    
    writeOptional<int>(out, some, [](OutputPort& p, int v) { writeInt32(p, v); });
    writeOptional<int>(out, none, [](OutputPort& p, int v) { writeInt32(p, v); });
    
    DataInputPort in(out.data());
    
    auto result1 = readOptional<int>(in, [](InputPort& p) { return readInt32(p); });
    auto result2 = readOptional<int>(in, [](InputPort& p) { return readInt32(p); });
    
    assert(result1.has_value());
    assert(*result1 == 42);
    assert(!result2.has_value());
    
    LOG_INFO("✓ Optional test PASSED");
}

int main() {
    Logger::setLevel(LogLevel::INFO);
    
    LOG_INFO("=== Starting Serde Tests ===");
    
    testBasicTypes();
    testVarint();
    testVector();
    testMap();
    testOptional();
    
    LOG_INFO("=== All Serde tests completed ===");
    
    return 0;
}
