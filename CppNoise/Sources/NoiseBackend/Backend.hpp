// Backend.hpp - Async Racket Backend Client

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
#include <iostream>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#include <unistd.h>
#endif

namespace Noise {

struct BackendStats {
    uint64_t totalRequests = 0;
    std::chrono::nanoseconds totalWaitDuration{0};
    std::chrono::nanoseconds totalReadDuration{0};
    std::chrono::nanoseconds totalWriteDuration{0};
};

// Async Racket backend client.
class Backend {
    struct Pipe { int readFd = -1, writeFd = -1; };
    struct ResponseHandler {
        virtual ~ResponseHandler() = default;
        virtual void handle(InputPort& port) = 0;
        std::chrono::steady_clock::time_point time;
    };

    Pipe inputPipe_, outputPipe_;
    mutable std::mutex mutex_;
    std::unique_ptr<OutputPort> out_;
    uint64_t seq_ = 0;
    std::unordered_map<uint64_t, std::shared_ptr<ResponseHandler>> pending_;
    BackendStats stats_;
    std::thread serverThread_, readerThread_;

    Pipe createPipe() {
        Pipe p;
        #ifdef _WIN32
        int fds[2];
        if (_pipe(fds, 4096, _O_BINARY) == 0) { p.readFd = fds[0]; p.writeFd = fds[1]; }
        #else
        int fds[2];
        if (pipe(fds) == 0) { p.readFd = fds[0]; p.writeFd = fds[1]; }
        #endif
        return p;
    }

    void serve(const std::string& zo, const std::string& modname, const std::string& proc) {
        Racket r(zo);
        r.bracket([&]() {
            r.load(zo);
            Val mod = Val::cons(Val::symbol("quote"), Val::cons(Val::symbol(modname), Val::null()));
            Val ifd = Val::fixnum(inputPipe_.readFd);
            Val ofd = Val::fixnum(outputPipe_.writeFd);
            Val serve = r.require(Val::symbol(proc), mod).unsafeCar();
            serve.unsafeApply(Val::cons(ifd, Val::cons(ofd, Val::null())));
            std::cerr << "Racket server exited unexpectedly" << std::endl;
            return 0;
        });
    }

    void read() {
        FileInputPort inp(outputPipe_.readFd);
        while (true) {
            uint64_t id = readUVarint(inp);
            std::shared_ptr<ResponseHandler> handler;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                auto it = pending_.find(id);
                if (it == pending_.end()) continue;
                handler = it->second;
            }
            auto t0 = std::chrono::steady_clock::now();
            handler->handle(inp);
            auto readDuration = std::chrono::steady_clock::now() - t0;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                pending_.erase(id);
                stats_.totalRequests++;
                stats_.totalWaitDuration += std::chrono::steady_clock::now() - handler->time;
                stats_.totalReadDuration += readDuration;
            }
        }
    }

public:
    Backend(const std::string& zo, const std::string& modname, const std::string& proc) {
        inputPipe_ = createPipe();
        outputPipe_ = createPipe();
        out_ = std::make_unique<FileOutputPort>(inputPipe_.writeFd);
        serverThread_ = std::thread([this, zo, modname, proc]() { serve(zo, modname, proc); });
        readerThread_ = std::thread([this]() { read(); });
    }

    ~Backend() {
        if (serverThread_.joinable()) serverThread_.detach();
        if (readerThread_.joinable()) readerThread_.detach();
    }

    Backend(const Backend&) = delete;
    Backend& operator=(const Backend&) = delete;

    template<typename WriteFunc, typename ReadFunc>
    auto send(WriteFunc writeProc, ReadFunc readProc)
        -> std::shared_ptr<Future<std::string, decltype(readProc(std::declval<InputPort&>()))>> {
        using T = decltype(readProc(std::declval<InputPort&>()));
        auto future = std::make_shared<Future<std::string, T>>();

        struct Handler : ResponseHandler {
            std::shared_ptr<Future<std::string, T>> fut;
            ReadFunc read;
            Handler(std::shared_ptr<Future<std::string, T>> f, ReadFunc r)
                : fut(std::move(f)), read(std::move(r)) { time = std::chrono::steady_clock::now(); }
            void handle(InputPort& port) override {
                if (port.readByte() == 1) fut->resolve(read(port));
                else fut->reject(readString(port));
            }
        };

        std::lock_guard<std::mutex> lock(mutex_);
        uint64_t id = seq_++;
        auto t0 = std::chrono::steady_clock::now();
        writeUVarint(*out_, id);
        writeProc(*out_);
        out_->flush();
        pending_[id] = std::make_shared<Handler>(future, std::move(readProc));
        stats_.totalWriteDuration += std::chrono::steady_clock::now() - t0;
        return future;
    }

    BackendStats stats() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return stats_;
    }
};

} // namespace Noise
