/**************************************************************************************************
 * @file   ShootTheChickenGame.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "ShootTheChickenHUD.h"
#include "STCGameOverHUD.h"
#include "engine/core/window/WindowManager.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/scene/Scene.h"
#include "engine/scene/SceneManager.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/physics/Collider.h"
#include "engine/subsystems/physics/PhysicsTypes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/TransformTypes.h"

class ShootTheChickenGame : public GLESC::Scene::Scene {
public:
    SCENE_DEFINITION(ShootTheChickenGame)

    void createChickenMesh();
    void createPlayerMesh();
    void createBulletMesh();
    void createTreeMesh();
    void createGrassMesh();
    void createBushesMeshes();

    void createFloorEntity();
    void createTreeEntities();
    void createBushesEntity();
    void createGrassEntity();
    void generateChickenEntities();

    GLESC::Transform::Position generateChickenPosition();

    void createPlayerEntity();


    void shootBulletActionFunc();
    void jumpActionFunc();
    void collisionCallback(GLESC::ECS::EntityID chicken, GLESC::Physics::Collider& bulletCollider);

    void init() override;
    void update() override;

private:
    GLESC::Input::KeyCommand shootBulletAction;
    GLESC::Input::KeyCommand jumpAction;
    GLESC::Input::KeyCommand moveLeftAction;
    GLESC::Input::KeyCommand moveRightAction;
    GLESC::Input::KeyCommand moveForwardAction;
    GLESC::Input::KeyCommand moveBackwardAction;

    GLESC::Render::ColorMesh playerMesh;
    GLESC::Render::ColorMesh chickenMesh;
    GLESC::Render::ColorMesh bulletMesh;
    GLESC::Render::ColorMesh treeMesh;
    GLESC::Render::ColorMesh allBushesMesh;
    GLESC::Render::ColorMesh allGrassMesh;

    GLESC::HUD::HUDManager::WindowID gameOverWindow{};
    GLESC::HUD::HUDManager::WindowID statsWindow{};

    std::vector<GLESC::ECS::EntityID> chickens;
    // This will lead to memory leak
    std::vector<GLESC::ECS::EntityID> bullets;
    bool hasAlreadyInitialized = false;
}; // class ShootTheChickenGame
