/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <utility>

#include "engine/ecs/backend/ECS.h"

using namespace GLESC;

std::set<EntityID> ECS::getAssociatedEntities(const SystemName& name) const {
    if(!systemManager.isSystemRegistered(name))
        return {};
    return systemManager.getAssociatedEntities(name);
}

void ECS::registerSystem(const SystemName& name) {
    if(systemManager.isSystemRegistered(name))
        return;
    systemManager.registerSystem(name);
}

EntityID ECS::createEntity(const EntityName& name) {
    if(entityManager.doesEntityExist(name))
        return NULL_ENTITY;
    return entityManager.createNextEntity(name);
}

bool ECS::destroyEntity(EntityID entity) {
    if(!entityManager.doesEntityExist(entity))
        return false;
    entityManager.destroyEntity(entity);
    componentManager.entityDestroyed(entity);
    systemManager.entityDestroyed(entity);
    return true;
}

EntityID ECS::getEntityID(EntityName name) const{
    return entityManager.getEntity(std::move(name));
}

EntityName ECS::getEntityName(EntityID entity) {
    if(entityManager.doesEntityExist(entity))
        return nullptr;
    return entityManager.getEntityName(entity);
}

EntityID ECS::tryGetEntityID(EntityName name) const {
    return entityManager.tryGetEntity(std::move(name));
}