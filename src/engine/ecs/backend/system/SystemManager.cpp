/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/system/SystemManager.h"


#include "engine/core/logger/Logger.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/ecs/backend/asserts/system/SystemAsserts.h"


[[nodiscard]] std::set<EntityID> SystemManager::getAssociatedEntities(const SystemName& name) const {
    ASSERT_SYSTEM_IS_REGISTERED(name);
    return associatedEntities.find(name)->second;
}

void SystemManager::registerSystem(const SystemName& name) {
    ASSERT_SYSTEM_IS_NOT_REGISTERED(name);
    systemSignatures.try_emplace(name, Signature{});
    associatedEntities.try_emplace(name);
    ASSERT_SYSTEM_IS_REGISTERED(name);
}

void SystemManager::entitySignatureChanged(EntityID entity, Signature entitySignature) {
    /*
#ifdef DEBUG
    Logger::get().importantInfoBlue("Entity signature changed. Updated systems: ");
    for (auto &pair : systems) {
        auto const &system = pair.first;
        auto const &systemSignature = pair.second.first;
        if ((entitySignature & systemSignature) == systemSignature) {
            Logger::get().infoBlue("Entity" + std::to_string(entity) + " is added to " + system);
        } else {
            Logger::get().infoBlue("Entity" + std::toString(entity) + " is removed from " + system);
        }
    }
#endif*/
    // Notify each system that an entity's signature changed
    for (auto &[name, entitySet] : associatedEntities) {
        if ((entitySignature & systemSignatures[name]) == systemSignatures[name]) {
            // If the systemSignature of the entity matches the systemSignature of the system, insert it into the set
            entitySet.insert(entity);
        } else {
            entitySet.erase(entity);
        }
    }
}

void SystemManager::entityDestroyed(EntityID entity) {
    // Erase a destroyed entity from all system lists
    for (auto &[name, entitySet] : associatedEntities) {
        entitySet.erase(entity);
        ASSERT_ENTITY_IS_NOT_ASSOCIATED_WITH_SYSTEM(name,entity);
    }
}

bool SystemManager::isSystemRegistered(const SystemName& name) const{
    return systemSignatures.contains(name);
}

void SystemManager::addComponentRequirementToSystem(const SystemName& name, ComponentID componentID) {
    ASSERT_SYSTEM_IS_REGISTERED(name);
    ASSERT_COMPONENT_IS_NOT_REQUIRED_BY_SYSTEM(name, componentID);
    systemSignatures.find(name)->second.set(componentID);
    ASSERT_COMPONENT_IS_REQUIRED_BY_SYSTEM(name, componentID);
}

[[maybe_unused]] bool SystemManager::isEntityAssociatedWithSystem(const SystemName& name, EntityID entity) const {
    return associatedEntities.find(name)->second.contains(entity);
}

[[maybe_unused]] bool SystemManager::isComponentRequiredBySystem(const SystemName& system, ComponentID component) const {
    return systemSignatures.find(system)->second.test(component);
}