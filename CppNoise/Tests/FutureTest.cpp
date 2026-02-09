// FutureTest.cpp - Simple test for Future functionality

#include "NoiseBackend/Future.hpp"
#include "NoiseBackend/Logger.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace Noise;
using namespace std::chrono_literals;

void testBasicResolve() {
    LOG_INFO("Testing basic future resolution...");
    auto future = std::make_shared<Future<std::string, int>>();
    
    std::thread([future]() {
        std::this_thread::sleep_for(100ms);
        future->resolve(42);
    }).detach();
    
    int result = future->wait();
    LOG_INFO("Result: " + std::to_string(result));
    if (result == 42) {
        LOG_INFO("✓ Basic resolve test PASSED");
    } else {
        LOG_ERROR("✗ Basic resolve test FAILED");
    }
}

void testCancellation() {
    LOG_INFO("Testing future cancellation...");
    auto future = std::make_shared<Future<std::string, int>>();
    
    std::thread([future]() {
        std::this_thread::sleep_for(100ms);
        future->cancel();
    }).detach();
    
    try {
        future->wait();
        LOG_ERROR("✗ Cancellation test FAILED - no exception thrown");
    } catch (const FutureCanceled&) {
        LOG_INFO("✓ Cancellation test PASSED");
    }
}

void testTimeout() {
    LOG_INFO("Testing future timeout...");
    auto future = std::make_shared<Future<std::string, int>>();
    
    // Don't resolve it - let it timeout
    auto result = future->wait_for(100ms);
    
    if (!result.has_value()) {
        LOG_INFO("✓ Timeout test PASSED");
    } else {
        LOG_ERROR("✗ Timeout test FAILED");
    }
}

void testMap() {
    LOG_INFO("Testing future map...");
    auto future1 = std::make_shared<Future<std::string, int>>();
    
    auto future2 = future1->map<std::string>([](int x) {
        return "Value: " + std::to_string(x);
    });
    
    std::thread([future1]() {
        std::this_thread::sleep_for(100ms);
        future1->resolve(42);
    }).detach();
    
    std::string result = future2->wait();
    if (result == "Value: 42") {
        LOG_INFO("✓ Map test PASSED");
    } else {
        LOG_ERROR("✗ Map test FAILED: " + result);
    }
}

void testFactoryMethods() {
    LOG_INFO("Testing factory methods...");
    
    auto resolved = Future<std::string, int>::resolved(100);
    int result = resolved->wait();
    
    if (result == 100) {
        LOG_INFO("✓ Factory method test PASSED");
    } else {
        LOG_ERROR("✗ Factory method test FAILED");
    }
}

int main() {
    Logger::setLevel(LogLevel::INFO);
    
    LOG_INFO("=== Starting Future Tests ===");
    
    testBasicResolve();
    testCancellation();
    testTimeout();
    testMap();
    testFactoryMethods();
    
    LOG_INFO("=== All tests completed ===");
    
    return 0;
}
