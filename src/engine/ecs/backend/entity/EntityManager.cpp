/******************************************************************************
 * @file   EntityManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/entity/EntityManager.h"
#include "engine/ecs/backend/asserts/entity/EntityAsserts.h"

using namespace GLESC::ECS;


EntityManager::EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (EntityID entity = firstEntity; entity < maxEntities + firstEntity; ++entity) {
        availableEntities.push(entity);
    }
}

EntityID EntityManager::createNextEntity(const EntityName& name) {
    ASSERT_ENTITY_CAN_BE_CREATED(name);
    
    EntityID id = availableEntities.front();
    availableEntities.pop();
    entityIDs.insert({name, id});
    ++livingEntityCount;

    ASSERT_ENTITY_EXISTS(id);
    return id;
}

void EntityManager::destroyEntity(EntityID entity) {
    ASSERT_THERE_ARE_LIVING_ENTITIES();
    ASSERT_ENTITY_EXISTS(entity);
    
    signatures[entity].reset();
    availableEntities.push(entity);
    entityIDs.right.erase(entity);
    --livingEntityCount;

    ASSERT_ENTITY_DOESNT_EXIST(entity);
    ASSERT_ENTITY_IS_NOT_ALIVE(entity);
}

Signature EntityManager::getSignature(EntityID entity) const {
    ASSERT_ENTITY_EXISTS(entity);
    return signatures[entity];
}

bool EntityManager::doesEntityHaveComponent(EntityID entity, ComponentID componentID) const {
    ASSERT_ENTITY_EXISTS(entity);
    ASSERT_COMPONENT_IS_IN_RANGE(componentID);
    return signatures[entity][componentID];
}

EntityName EntityManager::getEntityName(EntityID entity) const {
    ASSERT_ENTITY_EXISTS(entity);
    return entityIDs.right.at(entity);
}

EntityID EntityManager::getEntityID(const EntityName& name) const {
    return entityIDs.left.at(name);
}
EntityID EntityManager::tryGetEntity(const EntityName& name) const {
    if(!doesEntityExist(name))
        return nullEntity;
    return entityIDs.left.at(name);
}

void EntityManager::removeComponentFromEntity(EntityID entity, ComponentID componentID) {
    ASSERT_ENTITY_IS_ALIVE(entity);
    ASSERT_COMPONENT_IS_IN_RANGE(componentID);
    ASSERT_ENTITY_HAS_COMPONENT(entity, componentID);
    signatures[entity].reset(componentID);
}

void EntityManager::addComponentToEntity(EntityID entity, ComponentID componentID) {
    ASSERT_ENTITY_EXISTS(entity);
    ASSERT_COMPONENT_IS_IN_RANGE(componentID);
    ASSERT_ENTITY_DOESNT_HAVE_COMPONENT(entity, componentID);
    signatures[entity].set(componentID);
}

bool EntityManager::doesEntityExist(const EntityName& name) const {
    return entityIDs.left.find(name) != entityIDs.left.end();
}

bool EntityManager::doesEntityExist(EntityID entity) const {
    return entityIDs.right.find(entity) != entityIDs.right.end();
}

bool EntityManager::isEntityAlive(EntityID entity) const {
    // Entity is alive if it has a signature that is not empty
    return doesEntityExist(entity) && !signatures[entity].none();
}

bool EntityManager::isEntityAlive(const EntityName& name) const {
    // Entity is alive if it has a signature that is not empty
    return isEntityAlive(getEntityID(name));
}

[[maybe_unused]] bool EntityManager::isComponentInRange(ComponentID componentID) const {
    return componentID < signatures[0].size();
}

bool EntityManager:: canEntityBeCreated(const EntityName& name) const {
    return livingEntityCount < maxEntities
    && !availableEntities.empty()
    && entityIDs.left.find(name) == entityIDs.left.end();
}
bool EntityManager::areThereLivingEntities() const {
    return livingEntityCount > 0;
}
