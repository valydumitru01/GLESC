/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"


/**
 * @brief Asserts that an entity can be created.
 * @detailed If livingEntityCount is equal to maxEntities, then there are no more entities to be created.
 * If availableEntitiesQueue is empty, then there are no more entity IDs to be used.
 * If the entity name is already in the entityIDs map, then the entity is already alive.
 * @param livingEntityCount The number of living entities.
 * @param maxEntities The maximum number of entities that can be created.
 * @param availableEntitiesQueue The queue of available entity IDs.
 * @param entityIDs The entityIDs map.
 */
#define ASSERT_ENTITY_CAN_BE_CREATED(livingEntityCount, maxEntities, availableEntitiesQueue, entityIDs) \
    ASSERT(livingEntityCount < maxEntities \
    && !availableEntitiesQueue.empty() \
    && entityIDs.left.find(name) == entityIDs.left.end() \
    , "No entities to be created");

/**
 * @brief Asserts the entity has any component, if it has then it is alive.
 * @detailed In the list of signatures of the entities, if the entity has any component, then it is alive.
 * @param entity The entity to be checked.
 * @param signatures The list of signatures of the entities.
 */
#define ASSERT_ENTITY_IS_ALIVE(entity, signatures) \
    ASSERT(signatures[entity].any(), "Entity is not alive, but should be")
#define ASSERT_ENTITY_IS_NOT_ALIVE(entity, signatures) \
    ASSERT_FALSE(signatures[entity].any(), "Entity is alive, but should not be")
/**
 * @brief Asserts that the entity is alive by name.
 * @detailed This assert is used when we want to check if an entity name is stored in the entityIDs map,
 * if it is then the entity is alive.
 * @param entityName The entity name to be checked.
 * @param entityIDs The entityIDs map.
 */
#define ASSERT_ENTITY_NAME_IS_ALIVE(entityName, entityIDs) \
    ASSERT_EQUAL(entityIDs.left.find(entityName), entityIDs.left.end(), "Entity is not alive, but should be")

#define ASSERT_ENTITY_NAME_IS_NOT_ALIVE(entityName, entityIDs) \
    ASSERT_NOT_EQUAL(entityIDs.left.find(entityName), entityIDs.left.end(), "Entity is alive, but should not be")
/**
 * @brief Asserts that the component is in range.
 * @detailed This assert is used when we want to check if a component is in the range of the bits in the signature.
 * @param componentID The component ID to be checked.
 * @param signatures The signatures of the entities.
 */
#define ASSERT_COMPONENT_IS_IN_RANGE(componentID, signatures) \
    ASSERT(componentID < signatures[0].size(), "Component is out of range")