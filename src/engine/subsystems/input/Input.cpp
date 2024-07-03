/**************************************************************************************************
 * @file   Input.cpp
 * @author Valentin Dumitru
 * @date   13/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/input/debugger/InputDebugger.h"
#include "engine/subsystems/input/Input.h"

#include <sstream>

using namespace GLESC::Input;
#ifndef NDEBUG_GLESC
std::vector<EntityStatsManager::Value> Input::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value subscribedKeysValue;
    subscribedKeysValue.name = "Subscribed keys";
    subscribedKeysValue.isString = true;
    std::stringstream ss;
    for (const auto& [key, command] : subscribedKeys) {
        ss << keyToString(key.key) << "\n";
    }
    subscribedKeysValue.stringData = ss.str();
    values.push_back(subscribedKeysValue);
    return values;
}
#endif

std::string Input::Input::toString() const {
    std::stringstream ss;
    ss << "Subscribed keys:\n";
    for (const auto& [key, command] : subscribedKeys) {
        ss << keyToString(key.key) << "\n";
    }
    return ss.str();
}
