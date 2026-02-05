// Backend.hpp - Backend Client
// Mirrors SwiftNoise/Sources/NoiseBackend/Backend.swift

#pragma once

#include "NoiseSerde/Port.hpp"
#include "NoiseSerde/Serde.hpp"
#include "NoiseSerde/FileInputPort.hpp"
#include "NoiseSerde/FileOutputPort.hpp"
#include "Future.hpp"
#include "Noise/Racket.hpp"

#include <thread>
#include <mutex>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Noise {

/// Statistics reported by Backends.
struct BackendStats {
    uint64_t totalRequests = 0;
    std::chrono::nanoseconds totalWaitDuration{0};
    std::chrono::nanoseconds totalReadDuration{0};
    std::chrono::nanoseconds totalWriteDuration{0};
};

/// Client implementation for an async Racket backend.
class Backend {
public:
    /// Creates a backend with the given compiled Racket module.
    /// @param zo Path to the compiled .zo file
    /// @param modname Module name
    /// @param proc Procedure name to call
    Backend(const std::filesystem::path& zo,
            const std::string& modname,
            const std::string& proc);

    ~Backend();

    // Non-copyable
    Backend(const Backend&) = delete;
    Backend& operator=(const Backend&) = delete;

    /// Sends a request to the backend and returns a future for the response.
    template<typename WriteFunc, typename ReadFunc>
    auto send(WriteFunc writeProc, ReadFunc readProc)
        -> std::shared_ptr<Future<std::string, decltype(readProc(std::declval<InputPort&>()))>>;

    /// Returns backend statistics.
    BackendStats stats() const;

private:
    struct Pipe {
        int readFd = -1;
        int writeFd = -1;
    };

    void serve(const std::filesystem::path& zo,
               const std::string& modname,
               const std::string& proc);

    void read();

    Pipe createPipe();

    Pipe inputPipe_;   // input from Racket's perspective
    Pipe outputPipe_;  // output from Racket's perspective

    mutable std::mutex mutex_;
    std::unique_ptr<OutputPort> out_;
    uint64_t seq_ = 0;

    struct ResponseHandler {
        virtual ~ResponseHandler() = default;
        virtual void handle(InputPort& port) = 0;
        std::chrono::steady_clock::time_point time;
    };

    std::unordered_map<uint64_t, std::shared_ptr<ResponseHandler>> pending_;

    BackendStats stats_;

    std::thread serverThread_;
    std::thread readerThread_;
};

// Template implementation
template<typename WriteFunc, typename ReadFunc>
auto Backend::send(WriteFunc writeProc, ReadFunc readProc)
    -> std::shared_ptr<Future<std::string, decltype(readProc(std::declval<InputPort&>()))>>
{
    using T = decltype(readProc(std::declval<InputPort&>()));
    auto future = std::make_shared<Future<std::string, T>>();

    struct Handler : ResponseHandler {
        std::shared_ptr<Future<std::string, T>> fut;
        ReadFunc read;

        Handler(std::shared_ptr<Future<std::string, T>> f, ReadFunc r)
            : fut(std::move(f)), read(std::move(r)) {
            time = std::chrono::steady_clock::now();
        }

        void handle(InputPort& port) override {
            uint8_t status = port.readByte();
            if (status == 1) {
                fut->resolve(read(port));
            } else {
                fut->reject(readString(port));
            }
        }
    };

    std::lock_guard<std::mutex> lock(mutex_);
    uint64_t id = seq_++;

    auto t0 = std::chrono::steady_clock::now();
    writeUVarint(*out_, id);
    writeProc(*out_);
    out_->flush();
    auto dt = std::chrono::steady_clock::now() - t0;

    auto handler = std::make_shared<Handler>(future, std::move(readProc));
    pending_[id] = handler;
    stats_.totalWriteDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

    return future;
}

} // namespace Noise
