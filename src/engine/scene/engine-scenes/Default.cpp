/**************************************************************************************************
 * @file   default.cpp
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/scene/engine-scenes/Default.h"

#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"

using namespace GLESC;
static std::vector<ECS::Entity> entities;
void Default::init() {
    int numOfEntities = 20;
    for (int i = 0; i < numOfEntities; i++) {
        ECS::Entity entity = createEntity("entity" + std::to_string(i))
                                          .addComponent<ECS::TransformComponent>()
                                          .addComponent<ECS::RenderComponent>();
        float increment = Math::clamp(0.1f * static_cast<float>(i), 0.0f, 1.0f);
        Transform::Position position = Transform::Position(i * 3, 0, 0);

        // Setting position
        entity.getComponent<ECS::TransformComponent>().transform.setPosition(position);

        // Setting scale
        entity.getComponent<ECS::TransformComponent>().transform.setScale(
            Transform::Scale(1 + i * 0.1, 1 + i * 0.1, 1 + i * 0.1));

        // Choosing a color
        Render::ColorRgba color = Render::ColorRgba(increment * 255,
                                                    255 - 255 * increment,
                                                    255 - 255 * increment,
                                                    255);


        // Setting mesh, cube, sphere, pyramid, in this order
        if (i % 3 == 1)
            entity.getComponent<ECS::RenderComponent>().moveMesh(
                Render::MeshFactory::sphere(4 + i, 4 + i, 1, color));
        else
            entity.getComponent<ECS::RenderComponent>().moveMesh(
                Render::MeshFactory::cube(color));

        // Put a light every 3 entities
        if (i % 3 == 0) {
            ECS::Entity light = createEntity("light" + std::to_string(i))
                                             .addComponent<ECS::TransformComponent>()
                                             .addComponent<ECS::LightComponent>();
            light.getComponent<ECS::TransformComponent>().transform.setPosition(
                Transform::Position(position + Transform::Position(0, 0, 1 + increment)));
        }


        // Setting material
        entity.getComponent<ECS::RenderComponent>().getMaterial().setShininess(increment);
        entity.getComponent<ECS::RenderComponent>().getMaterial().setSpecularColor(
            Render::ColorRgb(increment * 255, increment * 255, increment * 255));


        entities.push_back(entity);
    }
}

void Default::update() {
    for (auto& entity : entities) {
        auto& transform = entity.getComponent<ECS::TransformComponent>().transform;
        transform.addRotation(Transform::Rotation(0.01, 0.01, 0.1));
    }
}
