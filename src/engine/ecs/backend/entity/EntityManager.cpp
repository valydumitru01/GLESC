

/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/entity/EntityManager.h"
#include "engine/ecs/backend/asserts/entity/EntityAsserts.h"
#include "engine/ecs/backend/debugger/entity/EntityManagerDebugger.h"

using namespace GLESC;


EntityManager::EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (EntityID entity = EntityID(); static_cast<unsigned int>(entity) < maxEntities; ++entity) {
        availableEntities.push(entity);
    }
}

EntityID EntityManager::createNextEntity(EntityName name) {
    ASSERT_ENTITY_CAN_BE_CREATED(name);
    PRINT_ENTITIES_STATUS(*this, "Before creating entity");
    
    EntityID id = availableEntities.front();
    availableEntities.pop();
    entityIDs.insert({name, id});
    ++livingEntityCount;
    
    PRINT_ENTITIES_STATUS(*this, "After creating entity");
    ASSERT_ENTITY_IS_ALIVE(id);
    return id;
}

void EntityManager::destroyEntity(EntityID entity) {
    ASSERT_ENTITY_IS_ALIVE(entity);
    PRINT_ENTITIES_STATUS(*this, "After destroying entity");
    
    signatures[entity].reset();
    availableEntities.push(entity);
    entityIDs.right.erase(entity);
    --livingEntityCount;
    
    PRINT_ENTITIES_STATUS(*this, "Before destroying entity");
    ASSERT_ENTITY_IS_NOT_ALIVE(entity);
    ASSERT_ENTITY_NAME_IS_NOT_ALIVE(getEntityName(entity));
}

Signature EntityManager::getSignature(EntityID entity) const {
    ASSERT_ENTITY_IS_ALIVE(entity);
    return signatures[entity];
}

bool EntityManager::doesEntityHaveComponent(EntityID entity, ComponentID componentID) const {
    ASSERT_ENTITY_IS_ALIVE(entity);
    ASSERT_COMPONENT_IS_IN_RANGE(componentID);
    return signatures[entity][componentID];
}

EntityName EntityManager::getEntityName(EntityID entity) const {
    ASSERT_ENTITY_IS_ALIVE(entity);
    return entityIDs.right.at(entity);
}

EntityID EntityManager::getEntity(EntityName name) const {
    ASSERT_ENTITY_NAME_IS_ALIVE(name);
    return entityIDs.left.at(name);
}
EntityID EntityManager::tryGetEntity(EntityName name) const {
    if(!doesEntityExist(name))
        return NULL_ENTITY;
    return entityIDs.left.at(name);
}


bool EntityManager::doesEntityExist(EntityName name) const {
    return entityIDs.left.find(name) != entityIDs.left.end();
}

bool EntityManager::doesEntityExist(EntityID entity) const {
    return entityIDs.right.find(entity) != entityIDs.right.end();
}

bool EntityManager::isEntityAlive(EntityID entity) const {
    // Entity is alive if it is in the entityIDs map
    return entityIDs.right.find(entity) != entityIDs.right.end();
}

bool EntityManager::isEntityNameAlive(EntityName name) const {
    // Entity is alive if it is in the entityIDs map, and it's entity ID is alive
    return entityIDs.left.find(name) != entityIDs.left.end() && isEntityAlive(entityIDs.left.at(name));
}

[[maybe_unused]] bool EntityManager::isComponentInRange(ComponentID componentID) const {
    return componentID < signatures[0].size();
}

bool EntityManager::canEntityBeCreated(EntityName name) const {
    return livingEntityCount < maxEntities
    && !availableEntities.empty()
    && entityIDs.left.find(name) == entityIDs.left.end();
}