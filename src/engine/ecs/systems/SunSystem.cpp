/**************************************************************************************************
 * @file   SunSystem.cpp
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/ecs/frontend/system/systems/SunSystem.h"

#include "engine/ecs/frontend/component/SunComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/HudItemsManager.h"

namespace GLESC::ECS {
    SunSystem::SunSystem(ECSCoordinator& ecs,Render::Renderer& renderer) :
            System(ecs, "SunSystem"), renderer(renderer) {
        addComponentRequirement<SunComponent>();
        addComponentRequirement<TransformComponent>();
    };

    void SunSystem::update() {
        float globalIntensities = 0.0f;
        float globalColorR = 0.0f;
        float globalColorG = 0.0f;
        float globalColorB = 0.0f;
        const std::set<EntityID>& entities = getAssociatedEntities();
        for (auto& entity : entities) {
            auto& sun = getComponent<SunComponent>(entity);
            auto& transform = getComponent<TransformComponent>(entity);
            renderer.addSun(sun.sun, transform.transform);
            globalIntensities += sun.sun.getIntensity();
            globalColorR += sun.sun.getColor().getR();
            globalColorG += sun.sun.getColor().getG();
            globalColorB += sun.sun.getColor().getB();
            HudItemsManager::addItem(HudItemType::SUN, transform.transform.getPosition());
        }
        auto entitiesCount = static_cast<float>(entities.size());
        globalIntensities /= entitiesCount;
        globalColorR /= entitiesCount;
        globalColorG /= entitiesCount;
        globalColorB /= entitiesCount;
        Render::GlobalAmbienLight globalAmbienLight;
        globalAmbienLight.setIntensity(globalIntensities);
        globalAmbienLight.setColor({globalColorR, globalColorG, globalColorB});

        renderer.setGlobalAmbientLight(globalAmbienLight);
    }
} // namespace GLESC::ECS
