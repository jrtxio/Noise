// Model.hpp - Data structures for Hacker News

#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "NoiseSerde/Serde.hpp"

namespace NoiseBackendExample {

// Story data structure matching Racket's Story record
struct Story {
    uint64_t id;
    std::string title;
    std::vector<uint64_t> comments;

    static Story read(Noise::InputPort& p) {
        Story s;
        s.id = Noise::readUVarint(p);
        s.title = Noise::readString(p);
        // Read list of comment IDs
        uint64_t len = Noise::readUVarint(p);
        s.comments.reserve(len);
        for (uint64_t i = 0; i < len; ++i) {
            s.comments.push_back(Noise::readUVarint(p));
        }
        return s;
    }

    void write(Noise::OutputPort& p) const {
        Noise::writeUVarint(p, id);
        Noise::writeString(p, title);
        Noise::writeUVarint(p, comments.size());
        for (auto cid : comments) {
            Noise::writeUVarint(p, cid);
        }
    }
};

// Comment data structure matching Racket's Comment record
struct Comment {
    uint64_t id;
    std::string author;
    std::string timestamp;
    std::string text;

    static Comment read(Noise::InputPort& p) {
        Comment c;
        c.id = Noise::readUVarint(p);
        c.author = Noise::readString(p);
        c.timestamp = Noise::readString(p);
        c.text = Noise::readString(p);
        return c;
    }

    void write(Noise::OutputPort& p) const {
        Noise::writeUVarint(p, id);
        Noise::writeString(p, author);
        Noise::writeString(p, timestamp);
        Noise::writeString(p, text);
    }
};

// Helper to read a list of items
template<typename T>
std::vector<T> readList(Noise::InputPort& p) {
    uint64_t len = Noise::readUVarint(p);
    std::vector<T> result;
    result.reserve(len);
    for (uint64_t i = 0; i < len; ++i) {
        result.push_back(T::read(p));
    }
    return result;
}

} // namespace NoiseBackendExample
