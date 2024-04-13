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

void Game::init() {
    int numOfCubes = 5;
    for (int i = 0; i < numOfCubes; i++) {
        ECS::Entity entity = entityFactory.createEntity("entity" + std::to_string(i))
                                          .addComponent(ECS::TransformComponent())
                                          .addComponent(ECS::RenderComponent());
        entity.getComponent<ECS::TransformComponent>().transform.setPosition(Transform::Position(i, 2, 0));
        Render::ColorMesh& mesh = entity.getComponent<ECS::RenderComponent>().mesh;
        mesh = Render::MeshFactory::cube(Render::ColorRgba(255, 0, 0, 255));
        if (i < numOfCubes / 2)
            entity.getComponent<ECS::RenderComponent>().material.setShininess(1);
        else
            entity.getComponent<ECS::RenderComponent>().material.setShininess(0);
        entity.getComponent<ECS::RenderComponent>().material.setSpecularColor(Render::ColorRgb(255, 255, 255));
        if (i == numOfCubes - 1)
            i = numOfCubes - 1;
    }

    entityFactory.getEntity("entity1").getComponent<ECS::TransformComponent>().transform.setPosition(
        Transform::Position(10, 10, 0));

    // Creating a sphere to always be on the camera position
    entityFactory.createEntity("CameraBulb")
                 .addComponent(ECS::TransformComponent())
                 .addComponent(ECS::RenderComponent());
    entityFactory.getEntity("CameraBulb").getComponent<ECS::RenderComponent>().mesh =
        Render::MeshFactory::sphere(5, 5, Render::ColorRgba(255, 255, 255, 255));


    entityFactory.createEntity("light1")
                 .addComponent(ECS::TransformComponent())
                 .addComponent(ECS::RenderComponent())
                 .addComponent(ECS::LightComponent())
                 .getComponent<ECS::TransformComponent>().transform.setPosition(Transform::Position(20, 30, 0));

    entityFactory.getEntity("light1").getComponent<ECS::RenderComponent>().mesh =
        Render::MeshFactory::sphere(10, 10, Render::ColorRgba(255, 255, 255, 255));
}

void Game::update() {
    // Rotating entity
    ECS::Entity entity = entityFactory.getEntity("entity1");
    entity.getComponent<ECS::TransformComponent>().transform.addRotation(Transform::Rotation(0.01f, 0.01f, 0.01f));
    if(entity.getComponent<ECS::TransformComponent>().transform.getScale().getX() < 4)
        entity.getComponent<ECS::TransformComponent>().transform.addScale(Transform::Scale(0.001f, 0.001f, 0));

    ECS::Entity light = entityFactory.getEntity("light1");
    light.getComponent<ECS::TransformComponent>().transform.addRotation(Transform::Rotation(0, 1, 0));
    // Move light
    light.getComponent<ECS::TransformComponent>().transform.addPosition(
        light.getComponent<ECS::TransformComponent>().transform.forward() * 0.01f);

    entityFactory.getEntity("CameraBulb").getComponent<ECS::TransformComponent>()
                 .transform.setPosition(entityFactory.getEntity("entity1").
                     getComponent<ECS::TransformComponent>().transform.getPosition());
}
