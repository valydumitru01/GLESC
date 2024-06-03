/**************************************************************************************************
 * @file   ShootTheChickenGame.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/window/WindowManager.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/scene/Scene.h"
#include "engine/scene/SceneManager.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/input/MouseCommand.h"
#include "engine/subsystems/physics/Collider.h"
#include "engine/subsystems/physics/PhysicsTypes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/TransformTypes.h"

class ShootTheChickenGame : public GLESC::Scene::Scene {
public:
    ShootTheChickenGame(GLESC::WindowManager& windowManager,
                        GLESC::ECS::EntityFactory& entityFactory,
                        GLESC::Input::InputManager& inputManager,
                        GLESC::Scene::SceneManager& sceneManager,
                        GLESC::EngineCamera& camera)
        : Scene(windowManager, entityFactory, inputManager, sceneManager, camera) {
    }

    ~ShootTheChickenGame() override {
        destroyEntities();
    }

    void createChickenMesh();
    void createBulletMesh();
    void createFloorEntity();
    void generateChickenEntities();

    void setUpControls();

    void shootBulletActionFunc();
    void jumpActionFunc();
    void collisionCallback(GLESC::ECS::EntityID chicken, GLESC::Physics::Collider& bulletCollider);

    void init() override;
    void update() override;
    void destroy() override;
    static const std::string getSceneName() { return "shoot-the-chicken"; }

private:
    GLESC::Input::KeyCommand shootBulletAction;
    GLESC::Input::KeyCommand jumpAction;
    GLESC::Input::KeyCommand moveLeftAction;
    GLESC::Input::KeyCommand moveRightAction;
    GLESC::Input::KeyCommand moveForwardAction;
    GLESC::Input::KeyCommand moveBackwardAction;

    GLESC::Render::ColorMesh chickenMesh;
    GLESC::Render::ColorMesh bulletMesh;
    std::vector<GLESC::ECS::EntityID> chickens;
    // This will lead to memory leak
    std::vector<GLESC::ECS::EntityID> bullets;
}; // class ShootTheChickenGame
