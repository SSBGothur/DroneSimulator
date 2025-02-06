#include "logger.hpp"
#include <iostream>
#include <ctime>

namespace Logger {
    void log(const std::string &message) {
        std::time_t now = std::time(nullptr);
        char buf[64];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        std::cout << "[" << buf << "] " << message << std::endl;
    }
} 