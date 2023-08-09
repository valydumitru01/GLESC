/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#define PRINT_SYSTEMS_STATUS(systems, contextMessage) \
    { /* Scope for allowing calling the function in the same scope without redefinition error */ \
    Logger::get().info(std::string("System print status - ") + contextMessage); \
    for (const auto &systemPair : systems) { \
        SystemName systemName = systemPair.first; \
        const SystemData& systemData = systemPair.second; \
        Signature signature = systemData.first; \
        const std::set<EntityID>& associatedEntities = systemData.second; \
        \
        std::string systemListMessage = \
        "System: " + std::string(systemName) + \
        " Signature: " + signature.to_string(); \
        Logger::get().info(systemListMessage); \
        \
        std::string associatedEntitiesMessage = "Associated entities for system " + std::string(systemName) + ": "; \
        for(const EntityID &entityID : associatedEntities) { \
            associatedEntitiesMessage += std::to_string(entityID) + ", "; \
        } \
        Logger::get().info(associatedEntitiesMessage); \
    } \
    }