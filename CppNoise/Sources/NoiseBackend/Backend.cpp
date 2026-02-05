// Backend.cpp - Backend Implementation

#include "NoiseBackend/Backend.hpp"
#include "NoiseBoot/NoiseBoot.hpp"

#include <iostream>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#include <unistd.h>
#endif

namespace Noise {

Backend::Backend(const std::filesystem::path& zo,
                 const std::string& modname,
                 const std::string& proc)
{
    inputPipe_ = createPipe();
    outputPipe_ = createPipe();

    out_ = std::make_unique<FileOutputPort>(inputPipe_.writeFd);

    serverThread_ = std::thread([this, zo, modname, proc]() {
        serve(zo, modname, proc);
    });

    readerThread_ = std::thread([this]() {
        read();
    });
}

Backend::~Backend() {
    // Note: In production, you'd want proper shutdown handling
    if (serverThread_.joinable()) {
        serverThread_.detach();
    }
    if (readerThread_.joinable()) {
        readerThread_.detach();
    }
}

Backend::Pipe Backend::createPipe() {
    Pipe p;
    #ifdef _WIN32
    int fds[2];
    if (_pipe(fds, 4096, _O_BINARY) == 0) {
        p.readFd = fds[0];
        p.writeFd = fds[1];
    }
    #else
    int fds[2];
    if (pipe(fds) == 0) {
        p.readFd = fds[0];
        p.writeFd = fds[1];
    }
    #endif
    return p;
}

void Backend::serve(const std::filesystem::path& zo,
                    const std::string& modname,
                    const std::string& proc)
{
    // Boot Racket
    Racket r(zo.string());

    r.bracket([&]() {
        // Load the backend module
        r.load(zo);

        // Create module path: (quote modname)
        Val mod = Val::cons(Val::symbol("quote"),
                            Val::cons(Val::symbol(modname), Val::null()));

        // Get file descriptors
        Val ifd = Val::fixnum(inputPipe_.readFd);
        Val ofd = Val::fixnum(outputPipe_.writeFd);

        // Require and call the serve procedure
        Val serve = r.require(Val::symbol(proc), mod).unsafeCar();
        serve.unsafeApply(Val::cons(ifd, Val::cons(ofd, Val::null())));

        // Should not return
        std::cerr << "Racket server exited unexpectedly" << std::endl;
        return 0;
    });
}

void Backend::read() {
    FileInputPort inp(outputPipe_.readFd);
    std::vector<uint8_t> buf(8 * 1024);

    while (true) {
        uint64_t id = readUVarint(inp);

        std::shared_ptr<ResponseHandler> handler;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = pending_.find(id);
            if (it == pending_.end()) {
                std::cerr << "Future is gone for id: " << id << std::endl;
                continue;
            }
            handler = it->second;
        }

        auto t0 = std::chrono::steady_clock::now();
        handler->handle(inp);
        auto readDuration = std::chrono::steady_clock::now() - t0;

        {
            std::lock_guard<std::mutex> lock(mutex_);
            pending_.erase(id);
            auto requestDuration = std::chrono::steady_clock::now() - handler->time;
            stats_.totalRequests++;
            stats_.totalWaitDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(requestDuration);
            stats_.totalReadDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(readDuration);
        }
    }
}

BackendStats Backend::stats() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return stats_;
}

} // namespace Noise
