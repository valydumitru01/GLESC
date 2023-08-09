/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/system/SystemManager.h"


#include "engine/core/logger/Logger.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/ecs/backend/asserts/system/SystemAsserts.h"


[[nodiscard]] std::set<EntityID> SystemManager::getAssociatedEntities(SystemName name) const {
    ASSERT_SYSTEM_IS_REGISTERED(name, systems)
    return systems.find(name)->second.second;
}

void SystemManager::registerSystem(SystemName name) {
    ASSERT_SYSTEM_IS_NOT_REGISTERED(name, systems);
    systems.insert({name, {Signature{}, std::set<EntityID>{}}});
}

void SystemManager::setSignature(SystemName name, Signature signature) {
    ASSERT_SYSTEM_IS_REGISTERED(name, systems);
    systems.find(name)->second.first = signature;
}

[[nodiscard]] Signature SystemManager::getSignature(const char *name) const {
    ASSERT_SYSTEM_IS_REGISTERED(name, systems);
    return systems.find(name)->second.first;
}

void SystemManager::entitySignatureChanged(EntityID entity, Signature entitySignature) {
#ifdef DEBUG
    Logger::get().importantInfoBlue("Entity signature changed. Updated systems: ");
    for (auto &pair : systems) {
        auto const &system = pair.first;
        auto const &systemSignature = pair.second.first;
        if ((entitySignature & systemSignature) == systemSignature) {
            Logger::get().infoBlue("Entity" + std::to_string(entity) + " is added to " + system);
        } else {
            Logger::get().infoBlue("Entity" + std::to_string(entity) + " is removed from " + system);
        }
    }
#endif
    // Notify each system that an entity's signature changed
    for (auto &pair : systems) {
        auto const &signature = pair.second.first;
        auto &entities = pair.second.second;
        auto const &systemSignature = pair.second.first;
        if ((entitySignature & systemSignature) == signature) {
            // If the signature of the entity matches the signature of the system, insert it into the set
            entities.insert(entity);
        } else {
            entities.erase(entity);
        }
    }
}

void SystemManager::entityDestroyed(EntityID entity) {
    // Erase a destroyed entity from all system lists
    for (auto &pair : systems) {
        auto &entities = pair.second.second;
        entities.erase(entity);
    }
}