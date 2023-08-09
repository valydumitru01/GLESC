
/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/entity/Entity.h"

using namespace GLESC;
GLESC::Entity::Entity(EntityName name) : ID(GLESC::ECS::getECS()->createEntity(name)) {
}

GLESC::Entity::Entity(EntityID id) : ID(id) {
}

void Entity::destroy() {
    GLESC::ECS::getECS()->destroyEntity(ID);
}

EntityName Entity::getName() const {
    return GLESC::ECS::getECS()->getEntityName(ID);
}

