/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <string>
#include "engine/core/logger/Logger.h"
#include "engine/ecs/backend/component/ComponentManager.h"


#pragma once
/**
 * @brief Prints the name of each component with its ID and the number of components of that type.
 * It also prints the message with the context of the call.
 * @param componentArrays The array of component arrays of type
 * std::unordered_map<ComponentName, std::pair<IComponentArrayPtr, ComponentID>>
 */
#define PRINT_COMPONENTS_STATUS(componentArrays, nextComponentID, contextMessage) \
    { /* Scope for allowing calling the function in the same scope without redefinition error */ \
    Logger::get().info(std::string("Component print status - ") + contextMessage); \
    for (auto &componentArray : componentArrays) { \
        std::string componentName = componentArray.first; \
        std::pair<IComponentArrayPtr, ComponentID> componentArrayPair = componentArray.second; \
        IComponentArrayPtr componentArrayPtr = componentArrayPair.first; \
        ComponentID componentID = componentArrayPair.second; \
        \
        std::string componentListMessage =  \
        "Component: " + componentName + \
        " ID: " + std::to_string(componentID) + \
        " Size: " + std::to_string(componentArrayPtr->getSize()); \
        Logger::get().info(componentListMessage); \
    } \
    std::string nextComponentMessage = /* This causes the redefinition error */\
    "Next component ID: " + std::to_string(nextComponentID); \
    Logger::get().info(nextComponentMessage); \
    }