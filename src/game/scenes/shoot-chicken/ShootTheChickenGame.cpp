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
        ECS::Entity chicken = createEntity("chicken" + std::to_string(i));
        chicken.addComponent<ECS::TransformComponent>();
        chicken.addComponent<ECS::RenderComponent>();
        chicken.addComponent<ECS::PhysicsComponent>();
        chicken.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        chicken.getComponent<ECS::RenderComponent>().copyMesh(chickenMesh);
        chickens.push_back(chicken.getID());
    }
    // Rotate once by a random amount
    for (auto& chickenID : chickens) {
        ECS::Entity chicken = getEntity(chickenID);
        auto& transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
        /*transform.addRotation(GLESC::Transform::Rotation(Math::generateRandomNumber(0, 360),
                                                         Math::generateRandomNumber(0, 360),
                                                         Math::generateRandomNumber(0, 360)));*/

        transform.setPosition({transform.getPosition().getX(), 100, transform.getPosition().getZ()});
        chicken.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
        chicken.getComponent<ECS::PhysicsComponent>().collider.setBoundingVolume(
            chicken.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
        //chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.setForwardAcceleration(0.1f);
    }

    Input::KeyCommand shootBullet = Input::KeyCommand([&]() {
        // Create a bullet
        ECS::Entity bullet = createEntity("bullet" + std::to_string(bullets.size()));
        // Copy the camera transform
        auto& cameraTransform = getCamera().getComponent<ECS::TransformComponent>();
        bullet.addComponent<ECS::TransformComponent>(cameraTransform);
        bullet.addComponent<ECS::RenderComponent>();
        bullet.addComponent<ECS::PhysicsComponent>();

        // Capture the bullet ID by value in the lambda
        auto bulletID = bullet.getID();
        bullet.getComponent<ECS::PhysicsComponent>().collider.setCollisionCallback(
            [bulletID, this]() {
                Console::log("Collide!");
                destroyEntity(bulletID);
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bulletID), bullets.end());
            });

        bullet.getComponent<ECS::RenderComponent>().copyMesh(Render::MeshFactory::cube(Render::ColorRgb::WHITE, 0.1f));
        bullet.getComponent<ECS::PhysicsComponent>().physics.giveForwardForce(10000.f);
        bullets.push_back(bulletID);
    });

    getCamera().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_CLICK, Input::KeyAction::ONCE_PRESSED}, shootBullet);

    // Create a floor
    ECS::Entity floor = createEntity("floor");
    floor.addComponent<ECS::TransformComponent>();
    floor.addComponent<ECS::RenderComponent>();
    floor.addComponent<ECS::PhysicsComponent>();
    floor.getComponent<ECS::TransformComponent>().transform.setPosition({0, -1, 0});
    floor.getComponent<ECS::RenderComponent>().copyMesh(
        Render::MeshFactory::cuboid(1000, 2.f, 1000, Render::ColorRgb::GREEN));
    floor.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
    floor.getComponent<ECS::PhysicsComponent>().collider.setBoundingVolume(
        floor.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
}

void ShootTheChickenGame::update() {
    // Every 2 seconds, give upword force to all chickens
    if ((getSceneTime() / 1000) % 20 == 0) {
        for (auto& chickenID : chickens) {
            GLESC::ECS::Entity chicken = getEntity(chickenID);
            auto transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
            chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addForce(transform.up() * 0.1f);
        }
    }
}

void ShootTheChickenGame::destroy() {
    destroyEntities();
}
