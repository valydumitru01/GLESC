/**************************************************************************************************
 * @file   DebugInfoSystem.cpp
 * @author Valentin Dumitru
 * @date   2024-03-24
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/ecs/frontend/system/systems/DebugInfoSystem.h"

#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/EntityListManager.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

using namespace GLESC::ECS;

DebugInfoSystem::DebugInfoSystem(ECSCoordinator& ecs, Render::Renderer& renderer) : System(ecs, "DebugInfoSystem"),
    renderer(renderer) {
    addComponentRequirement<TransformComponent>();
}

void DebugInfoSystem::setEntityData(const EntityName& name) {
    EntityStatsManager::EntityData entityData;
    EntityID entityId = getEntity(name);
    if(selectedEntity == entityId) return;

    std::vector<IComponent*> components = getComponents(entityId);

    for (IComponent* component : components) {
        EntityStatsManager::ComponentData componentData;
        componentData.name = component->getName();
        componentData.values = &component->getDebuggingValues();
        entityData.components.push_back(componentData);
    }
    selectedEntity = entityId;
    EntityStatsManager::setEntityData(entityData);
}


void DebugInfoSystem::update() {
    for (EntityID id : getAssociatedEntities()) {
        EntityListManager::addEntity(getEntityName(id), getEntityMetadata(id).type);
    }
    if(!EntityListManager::getSelectedEntity().empty())
        setEntityData(EntityListManager::getSelectedEntity());
}
