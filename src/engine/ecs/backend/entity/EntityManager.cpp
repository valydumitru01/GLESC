

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
    ASSERT_ENTITY_CAN_BE_CREATED(livingEntityCount, maxEntities, availableEntities, entityIDs);
    PRINT_ENTITIES_STATUS(availableEntities, signatures, entityIDs, livingEntityCount, "Before creating entity");
    
    EntityID id = availableEntities.front();
    availableEntities.pop();
    entityIDs.insert({name, id});
    ++livingEntityCount;
    
    PRINT_ENTITIES_STATUS(availableEntities, signatures, entityIDs, livingEntityCount, "After creating entity");
    ASSERT_ENTITY_IS_ALIVE(id, signatures);
    return id;
}

void EntityManager::destroyEntity(EntityID entity) {
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    PRINT_ENTITIES_STATUS(availableEntities, signatures, entityIDs, livingEntityCount, "After destroying entity");
    
    signatures[entity].reset();
    availableEntities.push(entity);
    entityIDs.right.erase(entity);
    --livingEntityCount;
    
    PRINT_ENTITIES_STATUS(availableEntities, signatures, entityIDs, livingEntityCount, "Before destroying entity");
    ASSERT_ENTITY_IS_NOT_ALIVE(entity, signatures);
    ASSERT_ENTITY_NAME_IS_NOT_ALIVE(getEntityName(entity), entityIDs);
}

Signature EntityManager::getSignature(EntityID entity) const {
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    return signatures[entity];
}

bool EntityManager::doesEntityHaveComponent(EntityID entity, ComponentID componentID) const {
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    ASSERT_COMPONENT_IS_IN_RANGE(componentID, signatures);
    return signatures[entity][componentID];
}

EntityName EntityManager::getEntityName(EntityID entity) const {
    ASSERT_ENTITY_IS_ALIVE(entity, signatures);
    return entityIDs.right.at(entity);
}

EntityID EntityManager::getEntity(EntityName name) const {
    ASSERT_ENTITY_NAME_IS_ALIVE(name, entityIDs);
    return entityIDs.left.at(name);
}

bool EntityManager::doesEntityExist(EntityName name) const {
    return entityIDs.left.find(name) != entityIDs.left.end();
}

bool EntityManager::doesEntityExist(EntityID entity) const {
    return entityIDs.right.find(entity) != entityIDs.right.end();
}
