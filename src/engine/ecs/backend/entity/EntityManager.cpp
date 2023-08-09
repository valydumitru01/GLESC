

/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
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
    ASSERT_ENTITY_CAN_BE_CREATED(livingEntityCount, maxEntities, availableEntities);
    PRINT_ENTITIES_STATUS(availableEntities, signatures, entityIDs, livingEntityCount, "Before creating entity");
    EntityID id = availableEntities.front();
    availableEntities.pop();
    entityIDs.insert({name, id});
    ++livingEntityCount;
    return id;
}

void EntityManager::destroyEntity(EntityID entity) {
    ASSERT_ENTITY_IS_IN_RANGE(entity, signatures);
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    
    signatures[entity].reset();
    availableEntities.push(entity);
    --livingEntityCount;
}

void EntityManager::setSignature(EntityID entity, Signature signature) {
    ASSERT_ENTITY_IS_IN_RANGE(entity, signatures);
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    // Set the bit that represents the component to 1
    signatures[entity] = signature;
}

Signature EntityManager::getSignature(EntityID entity) {
    ASSERT_ENTITY_IS_IN_RANGE(entity, signatures);
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    return signatures[entity];
}

bool EntityManager::doesEntityHaveComponent(EntityID entity, ComponentID componentID) const {
    ASSERT_ENTITY_IS_IN_RANGE(entity, signatures);
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    return signatures[entity][componentID];
}

EntityName EntityManager::getEntityName(EntityID entity) {
    ASSERT_ENTITY_IS_IN_RANGE(entity, signatures);
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    return entityIDs.right.at(entity);
}

EntityID EntityManager::getEntity(EntityName name) {
    ASSERT_ENTITY_NAME_IS_ALIVE(name, entityIDs);
    return entityIDs.left.at(name);
}