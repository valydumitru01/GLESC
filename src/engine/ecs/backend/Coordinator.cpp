/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/Coordinator.h"

using namespace GLESC;

std::set<EntityID> Coordinator::getAssociatedEntities(SystemName name) {
    return systemManager.getAssociatedEntities(name);
}

void Coordinator::registerSystem(SystemName name) {
    systemManager.registerSystem(name);
}

EntityID Coordinator::createEntity(EntityName name) {
    return entityManager.createNextEntity(name);
}

void Coordinator::destroyEntity(EntityID entity) {
    entityManager.destroyEntity(entity);
    componentManager.entityDestroyed(entity);
    systemManager.entityDestroyed(entity);
}

EntityID Coordinator::getEntityID(EntityName name) {
    return entityManager.getEntity(name);
}

EntityName Coordinator::getEntityName(EntityID entity) {
    return entityManager.getEntityName(entity);
}

