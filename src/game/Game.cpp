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
    entityFactory.createEntity("player")
            .addComponent(ECS::RenderComponent())
            .addComponent(ECS::TransformComponent())
            .addComponent(ECS::PhysicsComponent())
            .addComponent(ECS::InputComponent())
            .getComponent<ECS::RenderComponent>().mesh = Render::MeshFactory::cube(Render::Rgba(255, 0, 0, 255));
    entityFactory.getEntity("player").getComponent<ECS::TransformComponent>().transform.setPosition(
            Transform::Position(1, 2, 0));
    
    entityFactory.createEntity("entity1")
            .addComponent(ECS::RenderComponent())
            .addComponent(ECS::TransformComponent())
            .addComponent(ECS::PhysicsComponent())
            .addComponent(ECS::InputComponent())
            .getComponent<ECS::RenderComponent>().mesh = Render::MeshFactory::cube(Render::Rgba(255, 0, 0, 255));
    entityFactory.getEntity("entity1").getComponent<ECS::TransformComponent>().transform.setPosition(
            Transform::Position(0, 0, 2));
    
    entityFactory.createEntity("entity2")
            .addComponent(ECS::RenderComponent())
            .addComponent(ECS::TransformComponent())
            .addComponent(ECS::PhysicsComponent())
            .addComponent(ECS::InputComponent())
            .getComponent<ECS::RenderComponent>().mesh = Render::MeshFactory::cube(Render::Rgba(255, 0, 0, 255));
    entityFactory.getEntity("entity2").getComponent<ECS::TransformComponent>().transform.setPosition(
            Transform::Position(0, 5, 0));
    
    entityFactory.createEntity("entity3")
            .addComponent(ECS::RenderComponent())
            .addComponent(ECS::TransformComponent())
            .addComponent(ECS::PhysicsComponent())
            .addComponent(ECS::InputComponent())
            .getComponent<ECS::RenderComponent>().mesh = Render::MeshFactory::cube(Render::Rgba(255, 0, 0, 255));
    entityFactory.getEntity("entity3").getComponent<ECS::TransformComponent>().transform.setPosition(
            Transform::Position(0, 0, 5));
    
    
    
    entityFactory.createEntity("light1")
            .addComponent(ECS::TransformComponent())
            .addComponent(ECS::RenderComponent())
            .addComponent(ECS::LightComponent())
            .getComponent<ECS::TransformComponent>().transform.setPosition(Transform::Position(2, 3, 0));
    entityFactory.getEntity("light1").getComponent<ECS::RenderComponent>().mesh =
            Render::MeshFactory::sphere(10, 10, Render::Rgba(255, 255, 255, 255));
    
}

void Game::update() {
    // Rotating entity
    ECS::Entity entity = entityFactory.getEntity("entity1");
    entity.getComponent<ECS::TransformComponent>().transform.addRotation(Transform::Rotation(0.01f, 0.01f, 0.01f));
    
    ECS::Entity light = entityFactory.getEntity("light1");
    light.getComponent<ECS::TransformComponent>().transform.addRotation(Transform::Rotation(0, 1, 0));
    // Move light
    light.getComponent<ECS::TransformComponent>().transform.addPosition(
            light.getComponent<ECS::TransformComponent>().transform.forward() * 0.01f);
}
