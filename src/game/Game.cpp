/******************************************************************************
 * @file   Game.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/


// Components
#include "game/Game.h"

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"

using namespace GLESC;
static std::vector<ECS::Entity> entities;

void Game::init() {
    int numOfEntities = 20;
    for (int i = 0; i < numOfEntities; i++) {
        ECS::Entity entity = entityFactory.createEntity("entity" + std::to_string(i))
                                          .addComponent(ECS::TransformComponent())
                                          .addComponent(ECS::RenderComponent());
        float increment = Math::clamp(0.1f * static_cast<float>(i), 0.0f, 1.0f);
        Transform::Position position = Transform::Position(i * 3, 0, 0);

        // Setting position
        entity.getComponent<ECS::TransformComponent>().transform.setPosition(position);

        // Setting scale
        entity.getComponent<ECS::TransformComponent>().transform.setScale(
            Transform::Scale(1 + i * 0.1, 1 + i * 0.1, 1 + i * 0.1));

        // Choosing a color
        Render::ColorRgba color = Render::ColorRgba(increment * 255, 255 - 255 * increment, 255 - 255 * increment, 255);


        // Setting mesh, cube, sphere, pyramid, in this order
        if (i % 3 == 0)
            entity.getComponent<ECS::RenderComponent>().mesh =
                Render::MeshFactory::cube(color);
        else if (i % 3 == 1)
            entity.getComponent<ECS::RenderComponent>().mesh =
                Render::MeshFactory::sphere(4 + i, 4 + i, color);
        else
            entity.getComponent<ECS::RenderComponent>().mesh =
                Render::MeshFactory::cube(color);

        // Put a light every 3 entities
        if (i % 3 == 0) {
            ECS::Entity light = entityFactory.createEntity("light" + std::to_string(i))
                         .addComponent(ECS::TransformComponent())
                         .addComponent(ECS::LightComponent());
            light.getComponent<ECS::TransformComponent>().transform.setPosition(
                Transform::Position(position + Transform::Position(0 , 0, 1 + increment)));
        }


        // Setting material
        entity.getComponent<ECS::RenderComponent>().material.setShininess(increment);
        entity.getComponent<ECS::RenderComponent>().material.setSpecularColor(
            Render::ColorRgb(increment * 255, increment * 255, increment * 255));


        entities.push_back(entity);
    }

/*
    // Add a entity that is a big plane
    entityFactory.createEntity("plane")
                 .addComponent(ECS::TransformComponent())
                 .addComponent(ECS::RenderComponent());
    entityFactory.getEntity("plane").getComponent<ECS::TransformComponent>().transform.setPosition(
        Transform::Position(0, -1, 0));

    entityFactory.getEntity("plane").getComponent<ECS::RenderComponent>().mesh =
        Render::MeshFactory::cuboid(10, 1, 10, Render::ColorRgba(255, 255, 255, 255));

    entityFactory.getEntity("plane").getComponent<ECS::RenderComponent>().material.setShininess(0.5);

    entityFactory.getEntity("plane").getComponent<ECS::TransformComponent>().transform.setScale(
        Transform::Scale(1, 1, 1));*/
}

void Game::update() {
    for (auto& entity : entities) {
        auto& transform = entity.getComponent<ECS::TransformComponent>().transform;
        transform.addRotation(Transform::Rotation(0.01, 0.01, 0.1));
    }
}
