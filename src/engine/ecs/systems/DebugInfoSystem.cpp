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

DebugInfoSystem::DebugInfoSystem(ECSCoordinator &ecs, Render::Renderer &renderer) : System(ecs, "DebugInfoSystem"),
                                                                                    renderer(renderer) {
    addComponentRequirement<TransformComponent>();
}

void DebugInfoSystem::setEntityData(const EntityID &id) {
    std::vector<IComponent *> components = getComponents(id);
    EntityDataFunctions entityFuncs;
    entityFuncs.name = [&]() { return getEntityName(id); };

    ComponentDataFunctions componentDataFuncs;
    for (IComponent *component : components) {
        componentDataFuncs.name = [component]() { return component->getName(); };
        componentDataFuncs.dataString = [component]() { return component->toString(); };
        entityFuncs.components.push_back(componentDataFuncs);
    }

    EntityStatsManager::setEntityData(entityFuncs);
}
bool intersects(const GLESC::Math::Line &line, const GLESC::Math::Point &point) {
    return line.distance(point) < 10;
}
void DebugInfoSystem::update() {
    double minDistanceFromCam = std::numeric_limits<double>::max();
    EntityID closestEntity = 0;
    for (EntityID id : getAssociatedEntities()) {
        Math::Line cameraForwardLine = Math::Line(renderer.getCameraTrasnform().getPosition(),
                                                  renderer.getCameraTrasnform().forward());
        const Math::Point entityPos = getComponent<TransformComponent>(id).transform.getPosition();
        // Skip if the forward line of the camera does not intersect with the bounding volume of the entity
        if (!intersects(cameraForwardLine, entityPos)) continue;

        const Transform::Transform &cameraTransform = renderer.getCameraTrasnform();
        double entityDistanceFromCam = entityPos.distance(cameraTransform.getPosition());

        // Skip if the entity is the camera itself
        if (entityDistanceFromCam == 0) continue;
        if (entityDistanceFromCam < minDistanceFromCam) {
            minDistanceFromCam = entityDistanceFromCam;
            closestEntity = id;
        }
    }
    if (closestEntity != 0)
        setEntityData(closestEntity);
}
