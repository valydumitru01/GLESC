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

#include "engine/ecs/frontend/component/CollisionComponent.h"
#include "engine/ecs/frontend/component/FogComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"
#include "game/scenes/shoot-chicken/ChickenKillCountHUD.h"

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

void ShootTheChickenGame::createPlayerMesh() {
    Render::ColorMesh playerGun = Render::MeshFactory::cuboid(0.5f, 0.5f, 5, Render::ColorRgb::BROWN);
    Render::ColorMesh playerGunHandle = Render::MeshFactory::cuboid(0.5f, 0.5f, 3, Render::ColorRgb::DARK_BROWN);
    // Rotate the gun to the left
    Transform::Transformer::rotateMesh(playerGun, {25, 25, 0});
    Transform::Transformer::rotateMesh(playerGunHandle, {25, 25, 0});
    // Lift the gun to the player's hands
    Transform::Transformer::translateMesh(playerGun, {1.3, -1, -3});
    Transform::Transformer::translateMesh(playerGunHandle, {1.3, -1.55, -3});
    playerMesh.startBuilding();
    playerMesh.attatchMesh(playerGun);
    playerMesh.attatchMesh(playerGunHandle);
    playerMesh.finishBuilding();
}

void ShootTheChickenGame::createTreeMesh() {
    Render::ColorMesh treeTrunk = Render::MeshFactory::cuboid(1.5f, 10, 1.5f, Render::ColorRgb::BROWN);
    Render::ColorMesh treeTop = Render::MeshFactory::cuboid(10, 10, 10, Render::ColorRgb::GREEN);
    Transform::Transformer::translateMesh(treeTop, {0, 10, 0});
    treeMesh.startBuilding();
    treeMesh.attatchMesh(treeTrunk);
    treeMesh.attatchMesh(treeTop);
    treeMesh.finishBuilding();
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
    floor.addComponent<ECS::CollisionComponent>();
    floor.getComponent<ECS::TransformComponent>().transform.setPosition({0, -1, 0});
    floor.getComponent<ECS::RenderComponent>().copyMesh(
        Render::MeshFactory::cuboid(1000, 2.f, 1000, Render::ColorRgb::GREEN));
    floor.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);
    floor.getComponent<ECS::PhysicsComponent>().physics.setStatic(true);
    floor.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
        floor.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
}

void ShootTheChickenGame::createTreeEntities() {
    int numTrees = 10;
    for (int i = 0; i < numTrees; i++) {
        Transform::Position position = Transform::Position(Math::generateRandomNumber(-100, 100),
                                                           -1,
                                                           Math::generateRandomNumber(-100, 100));
        // Add a constant for the position so the tree is not on top of the player
        position+={10, 0, 10};
        ECS::Entity tree = createEntity("tree", {EntityType::Instance});
        tree.addComponent<ECS::TransformComponent>();
        tree.addComponent<ECS::RenderComponent>();
        tree.addComponent<ECS::PhysicsComponent>();
        tree.addComponent<ECS::CollisionComponent>();
        tree.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        tree.getComponent<ECS::RenderComponent>().copyMesh(treeMesh);
        tree.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
            tree.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
        tree.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(false);

        float randomScale = Math::generateRandomNumber(1.f, 3.f);
        tree.getComponent<ECS::TransformComponent>().transform.setScale({
            randomScale,
            randomScale,
            randomScale
        });
    }
}


void ShootTheChickenGame::generateChickenEntities() {
    int numChickens = 10;
    for (int i = 0; i < numChickens; i++) {
        Transform::Position position = generateChickenPosition();
        ECS::Entity chicken = createEntity("chicken", {EntityType::Instance});
        chicken.addComponent<ECS::TransformComponent>();
        chicken.addComponent<ECS::RenderComponent>();
        chicken.addComponent<ECS::PhysicsComponent>();
        chicken.addComponent<ECS::CollisionComponent>();
        auto& transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
        chicken.getComponent<ECS::TransformComponent>().transform.setPosition({position});
        chicken.getComponent<ECS::RenderComponent>().copyMesh(chickenMesh);
        chicken.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
            chicken.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
        chicken.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
        transform.setPosition({transform.getPosition().getX(), 100, transform.getPosition().getZ()});
        chickens.push_back(chicken.getID());
    }
}

GLESC::Transform::Position ShootTheChickenGame::generateChickenPosition() {
    // Make the chicken reappear in a circle around the center of the map
    float radius = 100;
    return {
        Math::generateRandomNumber(-radius, radius),
        10,
        Math::generateRandomNumber(-radius, radius)
    };
}

void ShootTheChickenGame::collisionCallback(GLESC::ECS::EntityID chicken, GLESC::Physics::Collider& bulletCollider) {
    // Find the chicken that collided with the bullet
    auto it = std::find_if(chickens.begin(), chickens.end(),
                           [this, &bulletCollider](ECS::EntityID chickenID) {
                               return &bulletCollider == &getEntity(chickenID)
                                                          .getComponent<ECS::CollisionComponent>().collider;
                           });

    if (it != chickens.end()) {
        ECS::EntityID chickenID = *it;
        getEntity(chickenID).getComponent<ECS::TransformComponent>().transform.setPosition(generateChickenPosition());
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
    bullet.addComponent<ECS::CollisionComponent>();

    bullet.getComponent<ECS::TransformComponent>().transform.setPosition(
        cameraTransformCopy.transform.getPosition() - cameraTransformCopy.transform.forward() * 2.f);
    bullet.getComponent<ECS::TransformComponent>().transform.setRotation(
        cameraTransformCopy.transform.getRotation());


    // Capture the bullet ID by value in the lambda
    ECS::EntityID bulletID = bullet.getID();
    bullet.getComponent<ECS::CollisionComponent>().collider.setCollisionCallback(
        [bulletID, this](Physics::Collider& otherCollider) {
            collisionCallback(bulletID, otherCollider);
        });

    Console::log("Shooting" + getEntity(bulletID).getName());

    bullet.getComponent<ECS::RenderComponent>().copyMesh(bulletMesh);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setDirectionalForce(
        -bullet.getComponent<ECS::TransformComponent>().transform.forward(), 1000.f);
    bullet.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
}

void ShootTheChickenGame::jumpActionFunc() {
    if (getCamera().getEntity().getComponent<ECS::CollisionComponent>().collider.
                    getCollisionInformation().isOnGround()) {
        getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.addForce({0, 200, 0});
    }
}


void ShootTheChickenGame::createPlayerEntity() {
    shootBulletAction = Input::KeyCommand([&]() { shootBulletActionFunc(); });
    jumpAction = Input::KeyCommand([&]() { jumpActionFunc(); });
    getCamera().getEntity().addComponent<ECS::CollisionComponent>();
    getCamera().getEntity().addComponent<ECS::RenderComponent>();
    getCamera().getEntity().getComponent<ECS::RenderComponent>().moveMesh(playerMesh);
    getCamera().getEntity().getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
    getCamera().getEntity().getComponent<ECS::CollisionComponent>().collider.setSolid(true);
    getCamera().getEntity().getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
        Math::BoundingVolume::createFromVulume(1, 5, 1));
    getCamera().getEntity().getComponent<ECS::TransformComponent>().transform.setPosition({0, 100, 0});
    getCamera().getEntity().getComponent<ECS::CameraComponent>().perspective.setFovDegrees(90);
    // Remove default fly up and down camera
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.unsubscribeKey(
        {Input::Key::SPACE, Input::KeyAction::ONGOING_PRESSED});
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.unsubscribeKey(
        {Input::Key::LEFT_SHIFT, Input::KeyAction::ONGOING_PRESSED});
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_CLICK, Input::KeyAction::ONCE_PRESSED}, shootBulletAction);
    getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::SPACE, Input::KeyAction::ONCE_PRESSED}, jumpAction);
    getCamera().setSpeed(100);
}

void ShootTheChickenGame::init() {
    getEntity("fog").getComponent<ECS::FogComponent>().fog.setDensity(0);
    hudManager.addWindow(chickenKillCountHUD, "ChickenKillCountHUD");
    createChickenMesh();
    createBulletMesh();
    createPlayerMesh();
    createTreeMesh();

    createFloorEntity();
    createTreeEntities();
    generateChickenEntities();

    createPlayerEntity();
}

void ShootTheChickenGame::update() {
    // Every 1 seconds, give upword force to all chickens
    for (int i = 0; i < chickens.size(); i++) {
        GLESC::ECS::EntityID chickenID = chickens.at(i);
        GLESC::ECS::Entity chicken = getEntity(chickenID);
        if (!chicken.isAlive()) {
            chickens.erase(chickens.begin() + i);
            i--;
            continue;
        }
        // Jump every random seconds between 1 and 10
        if (getSceneTimeInSec() % Math::generateRandomNumber(1, 10) == 0) {
            auto transform = chicken.getComponent<GLESC::ECS::TransformComponent>().transform;
            if (chicken.getComponent<GLESC::ECS::CollisionComponent>().collider.getCollisionInformation().isOnGround())
                chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addForce(
                    transform.up() * Math::generateRandomNumber(100.f, 500.f));
        }
        // Rotate the chickens so they look at the oppsite direction of where the camera is positioned
        // But not in the Y rotation so they dont look up or down
        Transform::Position cameraPosition =
            getCamera().getEntity().getComponent<GLESC::ECS::TransformComponent>().transform.getPosition();
        Render::Position chickenPosition =
            chicken.getComponent<GLESC::ECS::TransformComponent>().transform.getPosition();

        Transform::Rotation newChickenRotation = Transform::Transformer::lookAt(
            cameraPosition, chickenPosition, Transform::Transform::worldUp);
        Transform::Rotation currentRotation = chicken.getComponent<GLESC::ECS::TransformComponent>().transform.
                                                      getRotation();
        bool isCloseToPlayer = (cameraPosition - chickenPosition).length() < 20;
        if (isCloseToPlayer) {
            float rotationSmoothStep = 1.0f;
            // If the rotation is too different, rotate by rotationSmoothStep degree, making the rotation smooth
            if (currentRotation.getY() - newChickenRotation.getY() > rotationSmoothStep) {
                newChickenRotation.setY(currentRotation.getY() - rotationSmoothStep);
            }
            else if (currentRotation.getY() - newChickenRotation.getY() < -rotationSmoothStep) {
                newChickenRotation.setY(currentRotation.getY() + rotationSmoothStep);
            }
            chicken.getComponent<GLESC::ECS::TransformComponent>().transform.setRotation(newChickenRotation);

            chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addDirectionalForce(
                chicken.getComponent<GLESC::ECS::TransformComponent>().transform.forward(),
                Math::remap((chickenPosition - cameraPosition).length(), 0, 20, 10, 0)
            );
        }
        else {
            chicken.getComponent<GLESC::ECS::TransformComponent>().transform.
                    setRotation({0, currentRotation.getY(), 0});
            // Rotate for 4 seconds every 4 seconds
            if (getSceneTimeInSec() / 4 % 4 == 0) {
                chicken.getComponent<GLESC::ECS::TransformComponent>().transform.addRotation(
                    Transform::RotationAxis::Yaw,
                    4
                );
                chicken.getComponent<GLESC::ECS::PhysicsComponent>().physics.addDirectionalForce(
                    chicken.getComponent<GLESC::ECS::TransformComponent>().transform.forward(),
                    10
                );
            }
        }
    }
}
