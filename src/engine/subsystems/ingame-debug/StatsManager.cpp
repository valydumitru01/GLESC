/**************************************************************************************************
 * @file   StatsManager.cpp
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/ingame-debug/StatsManager.h"
using namespace GLESC;
std::unordered_map<std::string, std::string> StatsManager::getStats() {
    std::unordered_map<std::string, std::string> result;
    for (auto& source : sources) {
        result[source.first] = source.second();
    }
    return result;
}

std::map<std::string, std::function<std::string()>> StatsManager::sources = {};