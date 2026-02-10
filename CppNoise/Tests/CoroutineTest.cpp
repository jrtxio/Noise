// CoroutineTest.cpp - Test C++20 coroutine support for Future

#include "NoiseBackend/Future.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <coroutine>

using namespace Noise;
using namespace std::chrono_literals;

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

Task testAsyncAwait() {
    std::cout << "Testing co_await..." << std::endl;
    
    auto future = std::make_shared<Future<std::string, int>>();
    
    std::thread([future]() {
        std::this_thread::sleep_for(100ms);
        future->resolve(42);
    }).detach();
    
    int result = co_await *future;
    
    if (result == 42) {
        std::cout << "  PASSED" << std::endl;
    } else {
        std::cerr << "  FAILED" << std::endl;
    }
}

int main() {
    std::cout << "=== Coroutine Tests ===" << std::endl;
    testAsyncAwait();
    std::this_thread::sleep_for(200ms);
    std::cout << "=== Done ===" << std::endl;
    return 0;
}
