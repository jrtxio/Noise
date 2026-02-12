// Backend.hpp - Clean interface for HN Backend (no Noise/Chez Scheme headers)

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace HN {

struct Comment {
    uint64_t id;
    std::string author;
    std::string timestamp;
    std::string text;
};

struct Story {
    uint64_t id;
    std::string title;
    std::vector<uint64_t> comments;
};

// Async result callback types.
using StoriesCallback = std::function<void(std::vector<Story>)>;
using CommentsCallback = std::function<void(std::vector<Comment>)>;
using ErrorCallback = std::function<void(std::string)>;

// Opaque backend - implementation hidden in Backend.cpp.
class HNBackend {
    struct Impl;
    std::unique_ptr<Impl> impl_;
public:
    explicit HNBackend(const std::string& zoPath);
    ~HNBackend();

    void getTopStories(StoriesCallback onSuccess, ErrorCallback onError);
    void getComments(uint64_t itemId, CommentsCallback onSuccess, ErrorCallback onError);
};

std::string resolveZoPath();

} // namespace HN
