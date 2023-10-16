/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
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
    LOG( \
        "Component print status - " contextMessage, \
        GLESC::printComponentStatus(componentManager); \
    )

#ifndef NLOGGING
namespace GLESC {
    [[maybe_unused]] inline void printComponentStatus(const ComponentManager &componentManager) noexcept {
        for (const auto &[name, array] : componentManager.componentArrays) {
           GLESC::Logger::get().info(std::string("Component name: ") + name);
            for (int i = 0; i < static_cast<int>(array->getSize()); i++) {
               GLESC::Logger::get().importantInfo(
                        std::string("Component Index: ") + std::to_string(i) +
                        std::string(" Component Values: \n") + array->getComponent(i).toString());
            }
        }
       GLESC::Logger::get().info(std::string("Next component ID: ") + std::to_string(componentManager.nextComponentID));
    }
}
#endif