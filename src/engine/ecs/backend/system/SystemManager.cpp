/******************************************************************************
 * @file   SystemManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/system/SystemManager.h"


#include "engine/core/logger/Logger.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/ecs/backend/asserts/system/SystemAsserts.h"

using namespace GLESC::ECS;

const std::set<EntityID>&
SystemManager::getAssociatedEntitiesOfSystem(const SystemName& name) const {
    ASSERT_SYSTEM_IS_REGISTERED(name);
    return associatedEntities.at(name);
}

void SystemManager::registerSystem(const SystemName& name) {
    ASSERT_SYSTEM_IS_NOT_REGISTERED(name);
    systemSignatures.try_emplace(name, Signature{});
    associatedEntities.try_emplace(name);
    ASSERT_SYSTEM_IS_REGISTERED(name);
}

void SystemManager::entitySignatureChanged(EntityID entity, Signature entitySignature) {
    D_ASSERT_FALSE(systemSignatures.empty(),
                   "All systems must be registered before entities can be associated with them");
    // Notify each system that an entity's signature changed
    for (auto& [name, entitySet] : associatedEntities) {
        if ((entitySignature & systemSignatures[name]) == systemSignatures[name]) {
            // If the systemSignature of the entity matches the systemSignature of the system, insert it into the set
            entitySet.insert(entity);
        }
        else {
            entitySet.erase(entity);
        }
    }
}

void SystemManager::entityDestroyed(EntityID entity) {
    // Erase a destroyed entity from all system lists
    for (auto& [name, entitySet] : associatedEntities) {
        entitySet.erase(entity);
        ASSERT_ENTITY_IS_NOT_ASSOCIATED_WITH_SYSTEM(name, entity);
    }
}

bool SystemManager::isSystemRegistered(const SystemName& name) const {
    // Check if name is contained in systems
    return systemSignatures.find(name) != systemSignatures.end();
}

void SystemManager::addComponentRequirementToSystem(const SystemName& name,
                                                    ComponentID componentID) {
    ASSERT_SYSTEM_IS_REGISTERED(name);
    ASSERT_COMPONENT_IS_NOT_REQUIRED_BY_SYSTEM(name, componentID);
    systemSignatures.find(name)->second.set(componentID);
    ASSERT_COMPONENT_IS_REQUIRED_BY_SYSTEM(name, componentID);
}

[[maybe_unused]] bool SystemManager::isEntityAssociatedWithSystem(const SystemName& name, EntityID entity) const {
    auto it = associatedEntities.find(name);
    return it != associatedEntities.end() && it->second.find(entity) != it->second.end();
}

[[maybe_unused]] bool
SystemManager::isComponentRequiredBySystem(const SystemName& system, ComponentID component) const {
    return systemSignatures.find(system)->second.test(component);
}
