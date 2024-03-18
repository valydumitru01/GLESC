/**************************************************************************************************
 * @file   Console.cpp
 * @author Valentin Dumitru
 * @date   07/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include "engine/subsystems/ingame-debug/Console.h"

using namespace GLESC;

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
