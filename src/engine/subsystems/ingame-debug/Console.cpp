

#include "engine/subsystems/ingame-debug/Console.h"

using namespace GLESC;

#ifndef NDEBUG_GLESC
std::vector<LogEntry> Console::messages = {};
std::unordered_map<std::string, size_t> Console::messageIndices = {};
std::mutex Console::mutex = {};


void Console::addMessage(const std::string& message, LogLevel level) {
    std::lock_guard lock(mutex);
    auto it = messageIndices.find(message);
    if (it != messageIndices.end()) {
        messages[it->second].count++;
    }
    else {
        messageIndices[message] = messages.size();
        messages.push_back({message, 1, level});
    }
}

#endif
