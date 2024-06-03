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

using namespace GLESC;

void ShootTheChickenGame::createChickenMesh() {
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

void ShootTheChickenGame::createBulletMesh() {
    bulletMesh = Render::MeshFactory::cube(Render::ColorRgb::WHITE, 0.1f);
}

void ShootTheChickenGame::createFloorEntity() {
    // Create a floor
    ECS::Entity floor = createEntity("floor");
    floor.addComponent<ECS::TransformComponent>();
    floor.addComponent<ECS::RenderComponent>();
    floor.addComponent<ECS::PhysicsComponent>();
    floor.getComponent<ECS::TransformComponent>().transform.setPosition({0, -1, 0});
    floor.getComponent<ECS::RenderComponent>().copyMesh(
        Render::MeshFactory::cuboid(1000, 2.f, 1000, Render::ColorRgb::GREEN));
    floor.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
    floor.getComponent<ECS::PhysicsComponent>().physics.setFriction(0.5f);
    floor.getComponent<ECS::PhysicsComponent>().collider.setBoundingVolume(
        floor.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
}

void ShootTheChickenGame::generateChickenEntities() {
    int numChickens = 10;
    for (int i = 0; i < numChickens; i++) {
        Transform::Position position = Transform::Position(i * 3, 0, 0);
        ECS::Entity chicken = createEntity("chicken", {EntityType::Instance});
        chicken.addComponent<ECS::TransformComponent>();
        chicken.addComponent<ECS::RenderComponent>();
        chicken.addComponent<ECS::PhysicsComponent>();
        auto& transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
        chicken.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        chicken.getComponent<ECS::RenderComponent>().copyMesh(chickenMesh);
        chicken.getComponent<ECS::PhysicsComponent>().collider.setBoundingVolume(
            chicken.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
        chicken.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
        transform.setPosition({transform.getPosition().getX(), 100, transform.getPosition().getZ()});
        chickens.push_back(chicken.getID());
    }
}

void ShootTheChickenGame::collisionCallback(GLESC::ECS::EntityID chicken, GLESC::Physics::Collider& bulletCollider) {
    // Find the chicken that collided with the bullet
    auto it = std::find_if(chickens.begin(), chickens.end(),
                           [this, &bulletCollider](ECS::EntityID chickenID) {
                               return &bulletCollider == &getEntity(chickenID)
                                                          .getComponent<ECS::PhysicsComponent>().collider;
                           });

    if (it != chickens.end()) {
        ECS::EntityID chickenID = *it;
        // Destroy the chicken entity
        getEntity(chickenID).getComponent<ECS::TransformComponent>().transform.setPosition(
            {0, 0, 0});
        Console::log("Collide with" + getEntity(chickenID).getName());
    }

    // Destroy the bullet entity
    destroyEntity(chicken);
}


void ShootTheChickenGame::shootBulletActionFunc() {
    if (!inputManager.isMouseRelative()) return;
    // Create a bullet
    ECS::Entity bullet = createEntity("bullet", {EntityType::Instance});
    // Copy the camera transform
    auto cameraTransformCopy = getCamera().getEntity().getComponent<ECS::TransformComponent>();
    bullet.addComponent<ECS::TransformComponent>();
    bullet.addComponent<ECS::RenderComponent>();
    bullet.addComponent<ECS::PhysicsComponent>();

    bullet.getComponent<ECS::TransformComponent>().transform.setPosition(
        cameraTransformCopy.transform.getPosition());
    bullet.getComponent<ECS::TransformComponent>().transform.setRotation(
        cameraTransformCopy.transform.getRotation());


    // Capture the bullet ID by value in the lambda
    ECS::EntityID bulletID = bullet.getID();
    bullet.getComponent<ECS::PhysicsComponent>().collider.setCollisionCallback(
        [bulletID, this](Physics::Collider& otherCollider) {
            collisionCallback(bulletID, otherCollider);
        });

    Console::log("Shooting" + getEntity(bulletID).getName());

    bullet.getComponent<ECS::RenderComponent>().copyMesh(bulletMesh);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setDirectionalForce(
        bullet.getComponent<ECS::TransformComponent>().transform.forward(), 10.f);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
}

void ShootTheChickenGame::jumpActionFunc() {
    if (getCamera().getEntity().getComponent<ECS::PhysicsComponent>().collider.isOnAir()) {
        return;
    }
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.addForce({0, 100, 0});
}


void ShootTheChickenGame::setUpControls() {
    shootBulletAction = Input::KeyCommand([&]() { shootBulletActionFunc(); });
    jumpAction = Input::KeyCommand([&]() { jumpActionFunc(); });
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().collider.setSolid(true);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().collider.setBoundingVolume(
        Math::BoundingVolume::createFromVulume(1, -10, 1));
    getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.setPosition({0, 100, 0});

    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_CLICK, Input::KeyAction::ONCE_PRESSED}, shootBulletAction);
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::SPACE, Input::KeyAction::ONCE_PRESSED}, jumpAction);
    getCamera().setSpeed(100);
}

void ShootTheChickenGame::init() {
    createChickenMesh();
    createBulletMesh();

    createFloorEntity();
    generateChickenEntities();

    setUpControls();
}

void ShootTheChickenGame::update() {
    // Every 2 seconds, give upword force to all chickens
    for (int i = 0; i < chickens.size(); i++) {
        GLESC::ECS::EntityID chickenID = chickens.at(i);
        GLESC::ECS::Entity chicken = getEntity(chickenID);
        if (!chicken.isAlive()) {
            chickens.erase(chickens.begin() + i);
            i--;
            continue;
        }
        if ((getSceneTime() / 1000) % 20 == 0) {
            auto transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
            chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addForce(transform.up());
        }
        // Rotate the chickens so they look at the oppsite direction of where the camera is positioned
        // But not in the Y rotation so they dont look up or down
        Transform::Position cameraPosition =
            getCamera().getEntity().getComponent<GLESC::ECS::TransformComponent>().transform.getPosition();
        Render::Position chickenPosition =
            chicken.getComponent<GLESC::ECS::TransformComponent>().transform.getPosition();
        Math::Direction cameraChickenDirection = cameraPosition - chickenPosition;
        cameraChickenDirection = cameraChickenDirection.normalize();
        cameraChickenDirection.setY(0);
        chicken.getComponent<GLESC::ECS::TransformComponent>().transform.setRotation(cameraChickenDirection);
    }
}

void ShootTheChickenGame::destroy() {
    destroyEntities();
}
