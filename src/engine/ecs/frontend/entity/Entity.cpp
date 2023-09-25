
/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/entity/Entity.h"

using namespace GLESC;
GLESC::Entity::Entity(const EntityName& name, ECS& ecs) : ID(ecs.createEntity(name)), ecs(ecs) {
}

GLESC::Entity::Entity(EntityID id, ECS& ecs) : ID(id), ecs(ecs) {
}

void Entity::destroy() {
    ecs.destroyEntity(ID);
}

EntityName Entity::getName() const {
    return ecs.getEntityName(ID);
}

