// FutureTest.cpp - Simple test for Future functionality

#include "NoiseBackend/Future.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace Noise;
using namespace std::chrono_literals;

void testBasicResolve() {
    std::cout << "Testing basic future resolution..." << std::endl;
    auto future = std::make_shared<Future<std::string, int>>();
    
    std::thread([future]() {
        std::this_thread::sleep_for(100ms);
        future->resolve(42);
    }).detach();
    
    int result = future->wait();
    if (result == 42) {
        std::cout << "  PASSED" << std::endl;
    } else {
        std::cerr << "  FAILED" << std::endl;
    }
}

void testCancellation() {
    std::cout << "Testing future cancellation..." << std::endl;
    auto future = std::make_shared<Future<std::string, int>>();
    
    std::thread([future]() {
        std::this_thread::sleep_for(100ms);
        future->cancel();
    }).detach();
    
    try {
        future->wait();
        std::cerr << "  FAILED - no exception thrown" << std::endl;
    } catch (const Future<std::string, int>::Canceled&) {
        std::cout << "  PASSED" << std::endl;
    }
}

void testTimeout() {
    std::cout << "Testing future timeout..." << std::endl;
    auto future = std::make_shared<Future<std::string, int>>();
    
    auto result = future->wait_for(100ms);
    
    if (!result.has_value()) {
        std::cout << "  PASSED" << std::endl;
    } else {
        std::cerr << "  FAILED" << std::endl;
    }
}

void testMap() {
    std::cout << "Testing future map..." << std::endl;
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
        std::cout << "  PASSED" << std::endl;
    } else {
        std::cerr << "  FAILED: " << result << std::endl;
    }
}

void testFactoryMethods() {
    std::cout << "Testing factory methods..." << std::endl;
    
    auto resolved = Future<std::string, int>::resolved(100);
    int result = resolved->wait();
    
    if (result == 100) {
        std::cout << "  PASSED" << std::endl;
    } else {
        std::cerr << "  FAILED" << std::endl;
    }
}

int main() {
    std::cout << "=== Future Tests ===" << std::endl;
    testBasicResolve();
    testCancellation();
    testTimeout();
    testMap();
    testFactoryMethods();
    std::cout << "=== Done ===" << std::endl;
    return 0;
}
