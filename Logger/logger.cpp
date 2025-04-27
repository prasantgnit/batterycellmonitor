#include "logger.hpp"

Logger::Logger(LogLevel level, const std::string& filename)
    : log_level(level), log_file(filename) {
    if (!log_file.empty()) {
        file_stream.open(log_file, std::ios::out | std::ios::app);
    }
}

Logger::~Logger() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < log_level) {
        return;
    }

    std::string log_entry = formatLogEntry(level, message);

    std::lock_guard<std::mutex> lock(mtx);
    std::cout << log_entry << std::endl;

    if (file_stream.is_open()) {
        file_stream << log_entry << std::endl;
    }
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

std::string Logger::formatLogEntry(LogLevel level, const std::string& message) {
    std::stringstream ss;
    ss << getCurrentTime() << " [" << logLevelToString(level) << "] " << message;
    return ss.str();
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time_now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
