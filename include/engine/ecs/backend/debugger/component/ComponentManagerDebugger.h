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
 * @param componentManager The component manager
 */
#define PRINT_COMPONENTS_STATUS(componentManager, contextMessage) \
    DEBUG_CODE( \
        "Component print status - " contextMessage, \
        GLESC::printComponentStatus(componentManager); \
    )

#ifdef DEBUG
namespace GLESC {
    [[maybe_unused]] void printComponentStatus(const ComponentManager &componentManager) noexcept {
        for (const auto &[name, array] : componentManager.componentArrays) {
            Logger::get().info(std::string("Component name: ") + name);
            for (int i = 0; i < static_cast<int>(array->getSize()); i++) {
                Logger::get().info(
                        std::string("Component Index: ") + std::to_string(i) +
                        std::string(" Component Values: ") + array->getComponent(i).toString());
            }
        }
        Logger::get().info(std::string("Next component ID: ") + std::to_string(componentManager.nextComponentID));
    }
}
#endif