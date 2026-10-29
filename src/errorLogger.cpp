#include "main.h"
#include "errorLogger.h"
#include "robodash/api.h"

#include <vector>
#include <string>

namespace ErrorLogger {

    static rd::Console console("Error Logger");
    static std::vector<std::string> logs;

    constexpr int MAX_LOGS = 30;

    static void refresh() {
        console.clear();
        console.println("=== ERROR LOGGER ===");
        console.println("Time since program start");
        console.println("----------------------");

        if (logs.empty()) {
            console.println("No events recorded.");
            return;
        }

        for (const auto& log : logs) {
            console.println(log);
        }
    }

    static void write(const char* level, const std::string& message) {
        std::string entry =
            "[" + std::to_string(pros::millis() / 1000) +
            "s] [" + level + "] " + message;

        if (logs.size() >= MAX_LOGS) {
            logs.erase(logs.begin());
        }

        logs.push_back(entry);
        refresh();
    }

    void info(const std::string& message) {
        write("INFO", message);
    }

    void warning(const std::string& message) {
        write("WARN", message);
    }

    void error(const std::string& message) {
        write("ERROR", message);
    }

    void clear() {
        logs.clear();
        refresh();
    }

    void show() {
        refresh();
        console.focus();
    }
}