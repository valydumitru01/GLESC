/******************************************************************************
 * @file   Entity.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/entity/Entity.h"
using namespace GLESC::ECS;

Entity::Entity(const EntityName& name, ECSCoordinator& ecs) : ID(ecs.createEntity(name)), ecs(ecs) {}

Entity::Entity(ECSCoordinator& ecs) : ID(ecs.createEntity()), ecs(ecs) {}

Entity::Entity(EntityID id, ECSCoordinator& ecs) : ID(id), ecs(ecs) {}

void Entity::destroy() {
    ecs.destroyEntity(ID);
}

EntityName Entity::getName() const {
    return ecs.getEntityName(ID);
}
