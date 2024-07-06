
#include "engine/ecs/backend/system/SystemManager.h"


#include "engine/core/logger/Logger.h"
#include "engine/core/asserts/Asserts.h"

using namespace GLESC::ECS;

const std::set<EntityID>&
SystemManager::getAssociatedEntitiesOfSystem(const SystemName& name) const {
    D_ASSERT_TRUE(isSystemRegistered(name), "System must be registered before getting associated entities");
    return associatedEntities.at(name);
}

void SystemManager::registerSystem(const SystemName& name) {
    D_ASSERT_FALSE(isSystemRegistered(name), "System must not be registered");
    systemSignatures.try_emplace(name, Signature{});
    associatedEntities.try_emplace(name);
    D_ASSERT_TRUE(isSystemRegistered(name), "System must be registered after calling registerSystem");
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
        D_ASSERT_TRUE(!isEntityAssociatedWithSystem(name, entity), "Entity must not be associated with system");
    }
}

bool SystemManager::isSystemRegistered(const SystemName& name) const {
    // Check if name is contained in systems
    return systemSignatures.find(name) != systemSignatures.end();
}

void SystemManager::addComponentRequirementToSystem(const SystemName& name,
                                                    ComponentID componentID) {
    D_ASSERT_TRUE(isSystemRegistered(name), "System must be registered before adding component requirement");
    D_ASSERT_FALSE(isComponentRequiredBySystem(name, componentID), "Component must not be required by system already");
    systemSignatures.find(name)->second.set(componentID);
    D_ASSERT_TRUE(isComponentRequiredBySystem(name, componentID), "Component must be required by system");
}

[[maybe_unused]] bool SystemManager::isEntityAssociatedWithSystem(const SystemName& name, EntityID entity) const {
    auto it = associatedEntities.find(name);
    return it != associatedEntities.end() && it->second.find(entity) != it->second.end();
}

[[maybe_unused]] bool
SystemManager::isComponentRequiredBySystem(const SystemName& system, ComponentID component) const {
    return systemSignatures.find(system)->second.test(component);
}
