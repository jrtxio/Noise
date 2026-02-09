// Logger.hpp - Simple logging system for CppNoise

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>

namespace Noise {

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
    static LogLevel minLevel_;
    static std::mutex mutex_;

    static std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO ";
            case LogLevel::WARN:  return "WARN ";
            case LogLevel::ERROR: return "ERROR";
        }
        return "?????";
    }

    static std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t_now), "%H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }

public:
    static void setLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);
        minLevel_ = level;
    }

    static void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (level < minLevel_) return;
        
        std::cerr << "[" << getTimestamp() << "] "
                  << "[" << levelToString(level) << "] "
                  << message << std::endl;
    }

    static void debug(const std::string& message) { log(LogLevel::DEBUG, message); }
    static void info(const std::string& message)  { log(LogLevel::INFO, message); }
    static void warn(const std::string& message)  { log(LogLevel::WARN, message); }
    static void error(const std::string& message) { log(LogLevel::ERROR, message); }
};

// Static member initialization
inline LogLevel Logger::minLevel_ = LogLevel::INFO;
inline std::mutex Logger::mutex_;

// Convenience macros
#define LOG_DEBUG(msg) Noise::Logger::debug(msg)
#define LOG_INFO(msg)  Noise::Logger::info(msg)
#define LOG_WARN(msg)  Noise::Logger::warn(msg)
#define LOG_ERROR(msg) Noise::Logger::error(msg)

} // namespace Noise
