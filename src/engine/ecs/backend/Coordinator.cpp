/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/Coordinator.h"

using namespace GLESC;

std::set<EntityID> Coordinator::getAssociatedEntities(SystemName name) const {
    if(!systemManager.isSystemRegistered(name))
        return {};
    return systemManager.getAssociatedEntities(name);
}

void Coordinator::registerSystem(SystemName name) {
    if(systemManager.isSystemRegistered(name))
        return;
    systemManager.registerSystem(name);
}

EntityID Coordinator::createEntity(EntityName name) {
    if(entityManager.doesEntityExist(name))
        return NULL_ENTITY;
    return entityManager.createNextEntity(name);
}

bool Coordinator::destroyEntity(EntityID entity) {
    if(!entityManager.doesEntityExist(entity))
        return false;
    entityManager.destroyEntity(entity);
    componentManager.entityDestroyed(entity);
    systemManager.entityDestroyed(entity);
    return true;
}

EntityID Coordinator::getEntityID(EntityName name) const{
    if(entityManager.doesEntityExist(name))
        return NULL_ENTITY;
    return entityManager.getEntity(name);
}

EntityName Coordinator::getEntityName(EntityID entity) {
    if(entityManager.doesEntityExist(entity))
        return nullptr;
    return entityManager.getEntityName(entity);
}

