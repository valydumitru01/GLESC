/******************************************************************************
 * @file   EntityManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <functional>
#include "engine/ecs/backend/entity/EntityManager.h"


#include "engine/core/debugger/Stringer.h"

using namespace GLESC::ECS;


EntityManager::EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (EntityID entity = firstEntity; entity < maxEntities + firstEntity; ++entity) {
        availableEntities.push(entity);
    }
}

EntityID EntityManager::createNextEntity(const EntityName& nameParam, const EntityMetadata& metadata) {
    EntityID id = availableEntities.front();

    EntityName name = nameParam;
    if (metadata.type == EntityType::Instance) {
        instancedEntities[nameParam].push_back(id);
        name.append(std::to_string(instancesNextID[nameParam]));
        instancesNextID[nameParam]++;
    }


    D_ASSERT_TRUE(canEntityBeCreated(name), "Entity must be able to be created");

    availableEntities.pop();
    entityIDToName.insert({id, name});
    entityNameToID.insert({name, id});
    entityMetadata.insert({id, metadata});
    ++livingEntityCount;
    ++entityCounter;

    D_ASSERT_TRUE(doesEntityExist(id), "Entity must exist after creation");
    return id;
}

void EntityManager::destroyEntity(EntityID entity) {
    D_ASSERT_TRUE(areThereLivingEntities(), "There must be living entities to destroy one");
    D_ASSERT_TRUE(doesEntityExist(entity), "Entity must exist before destruction");
    D_ASSERT_TRUE((entity != GLESC::ECS::EntityManager::nullEntity), "Entity must not be nullEntity");

    if (isEntityInstanced(entityIDToName[entity])) {
        EntityName instanceName = Stringer::strip(entityIDToName[entity], "1234567890");
        std::vector<EntityID>& instancedList = this->instancedEntities[instanceName];

        auto it = std::find(instancedList.begin(), instancedList.end(), entity);
        if (it != instancedList.end())
            instancedList.erase(it);
    }


    signatures[entity].reset();
    availableEntities.push(entity);
    entityNameToID.erase(entityIDToName[entity]);
    entityIDToName.erase(entity);
    entityMetadata.erase(entity);


    --livingEntityCount;

    D_ASSERT_FALSE(doesEntityExist(entity), "Entity must not exist after destruction");
    D_ASSERT_FALSE(isEntityAlive(entity), "Entity must not be alive after destruction");
}

Signature EntityManager::getSignature(EntityID entity) const {
    D_ASSERT_TRUE(doesEntityExist(entity), "Entity must exist to get its signature");
    return signatures[entity];
}

bool EntityManager::doesEntityHaveComponent(EntityID entity, ComponentID componentID) const {
    D_ASSERT_TRUE(doesEntityExist(entity), "Entity must exist to check if it has a component");
    D_ASSERT_TRUE(isComponentInRange(componentID), "Component must be in range to check if entity has it");
    return signatures[entity][componentID];
}

const EntityName& EntityManager::getEntityName(EntityID entity) const {
    D_ASSERT_TRUE(doesEntityExist(entity), "Entity must exist to get its name");
    return entityIDToName.at(entity);
}

const EntityMetadata& EntityManager::getEntityMetadata(EntityID entity) const {
    D_ASSERT_TRUE(doesEntityExist(entity), "Entity must exist to get its metadata");
    return entityMetadata.at(entity);
}

EntityID EntityManager::getEntityID(const EntityName& name) const {
    D_ASSERT_TRUE(doesEntityExist(name), "Entity must exist to get its ID");
    return entityNameToID.at(name);
}

EntityID EntityManager::tryGetEntity(const EntityName& name) const {
    if (!doesEntityExist(name))
        return nullEntity;
    return entityNameToID.at(name);
}

const std::vector<EntityID>& EntityManager::getInstancedEntities(const EntityName& name) const {
    return instancedEntities.at(name);
}

bool EntityManager::isEntityInstanced(const EntityName& name) const {
    std::string strippedName = Stringer::strip(name, "1234567890");
    return instancedEntities.find(strippedName) != instancedEntities.end();
}

void EntityManager::removeComponentFromEntity(EntityID entity, ComponentID componentID) {
    D_ASSERT_TRUE(isEntityAlive(entity), "Entity must be alive to remove a component");
    D_ASSERT_TRUE(isComponentInRange(componentID), "Component must be in range to be removed");
    D_ASSERT_TRUE(doesEntityHaveComponent(entity, componentID), "Entity must have the component to remove it");
    signatures[entity].reset(componentID);
}

void EntityManager::addComponentToEntity(EntityID entity, ComponentID componentID) {
    D_ASSERT_TRUE(doesEntityExist(entity), "Entity must exist to add a component");
    D_ASSERT_TRUE(isComponentInRange(componentID), "Component must be in range to be added");
    if (doesEntityHaveComponent(entity, componentID)) return;
    signatures[entity].set(componentID);
}

bool EntityManager::doesEntityExist(const EntityName& name) const {
    return entityNameToID.find(name) != entityNameToID.end();
}

bool EntityManager::doesEntityExist(EntityID entity) const {
    return entityIDToName.find(entity) != entityIDToName.end();
}

bool EntityManager::isEntityAlive(EntityID entity) const {
    // Entity is alive if it has a signature that is not empty
    return doesEntityExist(entity) && !signatures[entity].none();
}

bool EntityManager::isEntityAlive(const EntityName& name) const {
    // Entity is alive if it has a signature that is not empty
    return isEntityAlive(getEntityID(name));
}

[[maybe_unused]] bool EntityManager::isComponentInRange(ComponentID componentID) const {
    return componentID < signatures[0].size();
}

bool EntityManager::canEntityBeCreated(const EntityName& name) const {
    return livingEntityCount < maxEntities
        && !availableEntities.empty()
        && entityNameToID.find(name) == entityNameToID.end();
}

bool EntityManager::areThereLivingEntities() const {
    return livingEntityCount > 0;
}
