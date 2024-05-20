/******************************************************************************
 * @file   ECS.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <utility>

#include "engine/ecs/backend/ECS.h"

#include <shared_mutex>

using namespace GLESC::ECS;

void ECSCoordinator::printStatus(const std::string& contextMessage) {
    Logger::get().importantInfoBlue("==== ECS print status - context: " + contextMessage + "====");

    Logger::get().importantInfo("Systems with their associated entities: ");
    for (const auto& system : systemManager.getSystemSignatures()) {
        SystemName systemName = system.first;
        Signature signature = system.second;
        Logger::get().info("\tSystem Name: " + systemName + " | Signature: " + signature.to_string());
        Logger::get().info("\tAssociated Entities: ");
        if (systemManager.getAssociatedEntitiesOfSystem(systemName).empty()) {
            Logger::get().info("\t\tNone");
        }
        for (const EntityID& entity : systemManager.getAssociatedEntitiesOfSystem(systemName)) {
            printEntity(entity);
        }
    }

    Logger::get().importantInfoWhite("===============================================");
    Logger::get().importantInfo("Existing entities: ");
    for (const auto& entity : entityManager.getEntityNameToID()) {
        EntityID entityID = entity.second;
        printEntity(entityID);
    }
    Logger::get().importantInfoWhite("===============================================");
    Logger::get().importantInfo("Registered components: ");
    for (const auto& component : componentManager.getComponentIDs()) {
        ComponentName componentName = component.first;
        ComponentID componentID = component.second;
        Logger::get().info(
            "\tComponent Name: " + componentName + " | ComponentID: " + Stringer::toString(componentID));
    }
    Logger::get().importantInfoWhite("===============================================");
}

void ECSCoordinator::printEntity(EntityID entity) {
    Logger::get().info("\tEntity Name: " + entityManager.getEntityName(entity));
    Logger::get().info("\tEntityID: " + std::to_string(entity));
    Logger::get().info("\tEntity Signature: " + entityManager.getSignature(entity).to_string());
    Logger::get().info("\tEntity Components: ");
    for (const auto& component : componentManager.getComponentIDs()) {
        ComponentName componentName = component.first;
        ComponentID componentID = component.second;
        if (entityManager.doesEntityHaveComponent(entity, componentID)) {
            IComponent& componentData = componentManager.getComponent(entity, componentID);
            Logger::get().nonImportantInfo(GLESC::Stringer::replace(componentData.toString(), "\n", "\n\t\t"));
        }
    }
}

const std::set<EntityID>& ECSCoordinator::getAssociatedEntities(const SystemName& name) const {
    if (!systemManager.isSystemRegistered(name))
        return {};
    const auto& set = systemManager.getAssociatedEntitiesOfSystem(name);
    for (const auto& entity : set) {
        D_ASSERT_TRUE(entityManager.doesEntityExist(entity), "Entity must exist");
        D_ASSERT_TRUE(systemManager.isEntityAssociatedWithSystem(name, entity),
                      "Entity must be associated with system");
    }
    return set;
}

const std::unordered_map<EntityName, EntityID>& ECSCoordinator::getAllEntities() const {
    return entityManager.getEntityNameToID();
}

void ECSCoordinator::registerSystem(const SystemName& name) {
    std::lock_guard lock(ecsMutex);
    D_ASSERT_TRUE(!systemManager.isSystemRegistered(name), "System must not be registered");
    PRINT_ECS_STATUS("Before registering system: " + name);
    systemManager.registerSystem(name);
    PRINT_ECS_STATUS("After registering system: " + name);
}

std::vector<IComponent*> ECSCoordinator::getComponents(EntityID entity) const {
    std::vector<IComponent*> components;
    Signature signature = entityManager.getSignature(entity);
    for (size_t i = 0; i < signature.size(); ++i) {
        if (signature.test(i)) {
            components.push_back(&componentManager.getComponent(entity, i));
        }
    }
    return components;
}

EntityID ECSCoordinator::createEntity(const EntityName& name) {
    std::lock_guard lock(ecsMutex);
    D_ASSERT_FALSE(entityManager.doesEntityExist(name),
                   "Cannot create entity with name " + name + " because it already exists");

    PRINT_ECS_STATUS("Before creating entity: " + name);
    EntityID id = entityManager.createNextEntity(name);
    PRINT_ECS_STATUS("After entity created: " + name);
    return id;
}

bool ECSCoordinator::destroyEntity(EntityID entity) {
    std::lock_guard lock(ecsMutex);
    D_ASSERT_TRUE(entityManager.doesEntityExist(entity), "Entity must exist");
    PRINT_ECS_STATUS("Before destroying entity: " + std::to_string(entity));
    entityManager.destroyEntity(entity);
    componentManager.entityDestroyed(entity);
    systemManager.entityDestroyed(entity);
    PRINT_ECS_STATUS("After entity destroyed: " + std::to_string(entity));
    return true;
}

EntityID ECSCoordinator::getEntityID(const EntityName& name) const {
    return entityManager.getEntityID(name);
}

const EntityName& ECSCoordinator::getEntityName(EntityID entity) const {
    return entityManager.getEntityName(entity);
}

EntityID ECSCoordinator::tryGetEntityID(const EntityName& name) const {
    return entityManager.tryGetEntity(name);
}
