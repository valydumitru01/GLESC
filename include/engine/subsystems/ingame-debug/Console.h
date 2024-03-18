/**************************************************************************************************
 * @file   Console.h
 * @author Valentin Dumitru
 * @date   06/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

namespace GLESC {
    enum class LogLevel {
        Info,
        Warning,
        Error
    };

    struct LogEntry {
        std::string message;
        int count;
        LogLevel level;
    };

    class Console {
    public:
        static void log(const std::string& message) { addMessage(message, LogLevel::Info); }
        static void warn(const std::string& message) { addMessage(message, LogLevel::Warning); }
        static void error(const std::string& message) { addMessage(message, LogLevel::Error); }

        static const std::vector<LogEntry>& GetMessages() { return messages; }

    private:
        static std::vector<LogEntry> messages;
        static std::unordered_map<std::string, size_t> messageIndices;
        static std::mutex mutex;

        static void addMessage(const std::string& message, LogLevel level);
    };

}
