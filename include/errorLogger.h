#pragma once

#include <string>

namespace ErrorLogger {
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

    void clear();
    void show();
}