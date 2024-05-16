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

#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"

void ShootTheChickenGame::createChickenMesh() {
    using namespace GLESC;
    Render::ColorMesh chickenBody = Render::MeshFactory::cube(Render::ColorRgb::WHITE);

    Render::ColorMesh chickenHead = Render::MeshFactory::cube(Render::ColorRgb::WHITE, 0.5f);
    Transform::Transformer::translateMesh(chickenHead, {0, 0.5, 0.5});

    Render::ColorMesh chickenPeak = Render::MeshFactory::cube(Render::ColorRgb::RED, 0.1f);
    Transform::Transformer::translateMesh(chickenPeak, {0, 0.5, 0.5 + 0.5 / 2});

    Render::ColorMesh chickenEye1 = Render::MeshFactory::cube(Render::ColorRgb::BLACK, 0.1f);
    Transform::Transformer::translateMesh(chickenEye1, {0.5 / 2, 0.6, 0.6});

    Render::ColorMesh chickenEye2 = Render::MeshFactory::cube(Render::ColorRgb::BLACK, 0.1f);
    Transform::Transformer::translateMesh(chickenEye2, {-0.5 / 2, 0.6, 0.6});

    Render::ColorMesh chickenLeg1 = Render::MeshFactory::cuboid(0.1f, 1, 0.1f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateMesh(chickenLeg1, {0.25, -0.5, 0});

    Render::ColorMesh chickenLeg2 = Render::MeshFactory::cuboid(0.1f, 1, 0.1f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateMesh(chickenLeg2, {-0.25, -0.5, 0});

    Render::ColorMesh chickenFoot1 = Render::MeshFactory::cuboid(0.2f, 0.1f, 0.2f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateMesh(chickenFoot1, {0.25, -1, 0.1f});

    Render::ColorMesh chickenFoot2 = Render::MeshFactory::cuboid(0.2f, 0.1f, 0.2f, Render::ColorRgb::YELLOW);
    Transform::Transformer::translateMesh(chickenFoot2, {-0.25, -1, 0.1f});


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
        /*transform.addRotation(GLESC::Transform::Rotation(Math::generateRandomNumber(0, 360),
                                                         Math::generateRandomNumber(0, 360),
                                                         Math::generateRandomNumber(0, 360)));*/
        chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
        //chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.setForwardAcceleration(0.1f);
    }

    Input::KeyCommand shootBullet = Input::KeyCommand([&]() {
        // Create a bullet
        ECS::Entity bullet = createEntity("bullet" + std::to_string(bullets.size()));
        // Copy the camera transform
        bullet.addComponent<ECS::TransformComponent>(bullet.getComponent<ECS::TransformComponent>());
        bullet.addComponent<ECS::RenderComponent>();
        bullet.addComponent<ECS::PhysicsComponent>();
        bullet.getComponent<ECS::PhysicsComponent>().collider.setCollisionCallback(
            [&]() {
                Console::log("Collide!");
            });
        bullet.getComponent<ECS::RenderComponent>().copyMesh(Render::MeshFactory::cube(Render::ColorRgb::WHITE, 0.1f));
        bullet.getComponent<ECS::PhysicsComponent>().physics.giveForwardForce(0.1f);
        bullets.push_back(bullet);
    });

    //getCamera().getComponent<ECS::InputComponent>().input.subscribeKey(
    //    {Input::Key::SPACE, Input::KeyAction::ONCE_PRESSED}, shootBullet);

    // Create a floor
    ECS::Entity floor = createEntity("floor");
    floor.addComponent<ECS::TransformComponent>();
    floor.addComponent<ECS::RenderComponent>();
    floor.addComponent<ECS::PhysicsComponent>();
    floor.getComponent<ECS::TransformComponent>().transform.setPosition({0, -1, 0});
    floor.getComponent<ECS::RenderComponent>().copyMesh(
        Render::MeshFactory::cuboid(1000, 0.1f, 1000, Render::ColorRgb::GREEN));
    floor.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);


}

void ShootTheChickenGame::update() {
    // Every 2 seconds, give upword force to all chickens
    if ((getSceneTime() / 1000) % 20 == 0) {
        for (auto& chicken : chickens) {
            auto transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
            chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addForce(transform.up() * 0.1f);
        }
    }
}

void ShootTheChickenGame::destroy() {
    destroyEntities();
}
