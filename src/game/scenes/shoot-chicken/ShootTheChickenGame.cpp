/**************************************************************************************************
 * @file   ShootTheChickenGame.cpp
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "game/scenes/shoot-chicken/ShootTheChickenGame.h"

#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"

void ShootTheChickenGame::createChickenMesh() {
    using namespace GLESC;
    Render::ColorMesh chickenBody = Render::MeshFactory::cube(Render::ColorRgb::WHITE);

    Render::ColorMesh chickenHead = Render::MeshFactory::cube(Render::ColorRgb::WHITE, 0.5f);
    Transform::Transformer::translateModelMesh(chickenHead, {0, 0.5, 0.5});

    Render::ColorMesh chickenPeak = Render::MeshFactory::cube(Render::ColorRgb::RED, 0.1f);
    Transform::Transformer::translateModelMesh(chickenPeak, {0, 0.5, 0.5 + 0.5 / 2});

    Render::ColorMesh chickenEye1 = Render::MeshFactory::cube(Render::ColorRgb::BLACK, 0.1f);
    Transform::Transformer::translateModelMesh(chickenEye1, {0.5 / 2, 0.6, 0.6});

    Render::ColorMesh chickenEye2 = Render::MeshFactory::cube(Render::ColorRgb::BLACK, 0.1f);
    Transform::Transformer::translateModelMesh(chickenEye2, {-0.5 / 2, 0.6, 0.6});

    Render::ColorMesh chickenLeg1 = Render::MeshFactory::cuboid(0.1f, 1, 0.1f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateModelMesh(chickenLeg1, {0.25, -0.5, 0});

    Render::ColorMesh chickenLeg2 = Render::MeshFactory::cuboid(0.1f, 1, 0.1f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateModelMesh(chickenLeg2, {-0.25, -0.5, 0});

    Render::ColorMesh chickenFoot1 = Render::MeshFactory::cuboid(0.2f, 0.1f, 0.2f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateModelMesh(chickenFoot1, {0.25, -1, 0.1f});

    Render::ColorMesh chickenFoot2 = Render::MeshFactory::cuboid(0.2f, 0.1f, 0.2f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateModelMesh(chickenFoot2, {-0.25, -1, 0.1f});


    chickenMesh.startBuilding();
    chickenMesh.attatchMesh(chickenHead);
    chickenMesh.attatchMesh(chickenBody);
    chickenMesh.attatchMesh(chickenLeg1);
    chickenMesh.attatchMesh(chickenLeg2);
    chickenMesh.attatchMesh(chickenFoot1);
    chickenMesh.attatchMesh(chickenFoot2);
    chickenMesh.attatchMesh(chickenPeak);
    chickenMesh.attatchMesh(chickenEye1);
    chickenMesh.attatchMesh(chickenEye2);
    chickenMesh.finishBuilding();
}

void ShootTheChickenGame::init() {
    using namespace GLESC;
    createChickenMesh();
    int numChickens = 10;
    for (int i = 0; i < numChickens; i++) {
        Transform::Position position = Transform::Position(i * 3, 0, 0);
        ECS::Entity& chicken = createEntity("chicken" + std::to_string(i));
        chicken.addComponent<ECS::TransformComponent>();
        chicken.addComponent<ECS::RenderComponent>();
        chicken.addComponent<ECS::PhysicsComponent>();
        chicken.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        chicken.getComponent<ECS::RenderComponent>().copyMesh(chickenMesh);
        chickens.push_back(chicken);
    }
    // Rotate once by a random amount
    for (auto& chicken : chickens) {
        auto& transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
        transform.addRotation(GLESC::Transform::Rotation(Math::generateRandomNumber(0, 360),
                                                         Math::generateRandomNumber(0, 360),
                                                         Math::generateRandomNumber(0, 360)));
        chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
    }
}

void ShootTheChickenGame::update() {
    for (auto& chicken : chickens) {
        chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addForwardForce(0.01f);

    }
}

void ShootTheChickenGame::destroy() {
    destroyEntities();
}
