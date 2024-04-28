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
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

using namespace GLESC::ECS;

DebugInfoSystem::DebugInfoSystem(ECSCoordinator& ecs, Render::Renderer& renderer) : System(ecs, "DebugInfoSystem"),
    renderer(renderer) {
    addComponentRequirement<TransformComponent>();
}

void DebugInfoSystem::setEntityData(const EntityID& id) {
    std::vector<IComponent*> components = getComponents(id);

    EntityStatsManager::EntityData entityData;
    entityData.name = getEntityName(id);
    for (IComponent* component : components) {
        EntityStatsManager::ComponentData componentData;
        componentData.name = component->getName();
        componentData.values = &component->getDebuggingValues();
        entityData.components.push_back(componentData);
    }
    EntityStatsManager::setEntityData(entityData);
}

bool intersects(const GLESC::Math::Line& line, const GLESC::Math::Point& point) {
    return line.distance(point) < 1;
}

void DebugInfoSystem::update() {
    double minDistanceFromCam = std::numeric_limits<double>::max();
    EntityID closestEntity{nullEntity};
    Math::Line cameraForwardLine;
    const Math::Point cameraPos = renderer.getCameraTrasnform().getPosition();
    const Math::Direction cameraForward = renderer.getCameraTrasnform().forward();
    EntityID cameraID{nullEntity};
    for (EntityID id : getAssociatedEntities()) {
        const Math::Point entityPos = getComponent<TransformComponent>(id).transform.getPosition();

        // Skip if the entity position is the same as the camera's
        if (entityPos == cameraPos) {
            cameraID = id;
            continue;
        }

        cameraForwardLine = Math::Line(cameraPos, cameraForward);

        // Skip if the forward line of the camera does not intersect with the bounding volume of the entity
        if (!intersects(cameraForwardLine, entityPos)) continue;

        double entityDistanceFromCam = entityPos.distance(cameraPos);

        // Skip if the entity is too far away
        if (entityDistanceFromCam > maxDetectionValue) continue;

        if (entityDistanceFromCam < minDistanceFromCam) {
            minDistanceFromCam = entityDistanceFromCam;
            closestEntity = id;
        }
    }
    if (closestEntity == nullEntity) {
        closestEntity = cameraID;
    }

    if (closestEntity == selectedEntity) return;

    selectedEntity = closestEntity;
    setEntityData(closestEntity);
}
