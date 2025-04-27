#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <memory>
#include <sstream>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(LogLevel level = LogLevel::INFO, const std::string& filename = "");
    ~Logger();

    void log(LogLevel level, const std::string& message);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

private:
    LogLevel log_level;
    std::ofstream file_stream;
    std::mutex mtx;
    std::string log_file;

    std::string formatLogEntry(LogLevel level, const std::string& message);
    std::string getCurrentTime();
    std::string logLevelToString(LogLevel level);
};

#endif // LOGGER_HPP
