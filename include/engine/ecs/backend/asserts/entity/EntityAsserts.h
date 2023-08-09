/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"
#define ASSERT_ENTITY_IS_IN_RANGE(entity, entities) \
    ASSERT(entity < entities.size(), "Entity is out of range")

#define ASSERT_ENTITY_IS_ALIVE(entity, signatures) \
    ASSERT(signatures[entity].any(), "Entity is not alive, but should be")

#define ASSERT_ENTITY_CAN_BE_CREATED(livingEntityCount, maxEntities, availableEntitiesQueue) \
    ASSERT(livingEntityCount < maxEntities && !availableEntitiesQueue.empty(), "No entities to be created")

#define ASSERT_ENTITY_NAME_IS_ALIVE(entityName, entityIDs) \
    ASSERT(entityIDs.left.find(entityName) != entityIDs.left.end(), "Entity is not alive, but should be")