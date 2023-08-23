/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <string>
#include "engine/core/debugger/Debugger.h"
#include "engine/core/logger/Logger.h"
/**
 * @brief Prints the name of each component with its ID and the number of components of that type.
 * It also prints the message with the context of the call.
 * @param componentArrays Map of component names to component arrays
 * @param componentIDs Map of component names to component IDs
 * @param nextComponentID The ID of the next component to be registered
 * @param contextMessage The message with the context of the call
 */
#define PRINT_COMPONENTS_STATUS(componentArrays, nextComponentID, contextMessage) \
    DEBUG_CODE(                                                                   \
        "Component print status - " contextMessage,                             \
        printComponentStatus(componentArrays, componentIDs, nextComponentID, contextMessage); \
    )

void printComponentStatus(const std::unordered_map<ComponentName, IComponentArrayPtr> &componentArrays,
                          const std::unordered_map<ComponentName, ComponentID> &componentIDs,
                          ComponentID nextComponentID,
                          const std::string &contextMessage) {
    for (const auto &[name, array] : componentArrays) {
        Logger::get().info(std::string("Component name: ") + name);
        for (int i = 0; i < static_cast<int>(array->getSize()); i++) {
            Logger::get().info(
                    std::string("Component Index: ") + std::to_string(i) +
                    std::string(" Component Values: ") + std::to_string(array->getComponent(i)));
        }
    }
    Logger::get().info(std::string("Next component ID: ") + std::to_string(nextComponentID));
}