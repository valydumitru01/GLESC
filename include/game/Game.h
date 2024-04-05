/******************************************************************************
 * @file   Game.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/counter/Timer.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/subsystems/input/InputManager.h"
#include "engine/subsystems/physics/PhysicsManager.h"
#include "engine/core/window/WindowManager.h"

class Game {
public:
    using Entity = GLESC::ECS::Entity;

    Game(GLESC::ECS::ECSCoordinator &ecs,
         GLESC::PhysicsManager &physicsManager,
         GLESC::Input::InputManager &inputManager,
         GLESC::WindowManager &windowManager,
         GLESC::ECS::EntityFactory &entityFactory) :
        ecs(ecs), physicsManager(physicsManager), inputManager(inputManager), windowManager(windowManager),
        entityFactory(entityFactory) {}

    void init();

    void update();

private:
    float targetRotationX = 0.0f;
    float targetRotationY = 0.0f;
    float sensitivity = 3.f;


    GLESC::ECS::ECSCoordinator &ecs;
    GLESC::ECS::EntityFactory &entityFactory;
    GLESC::PhysicsManager &physicsManager;
    GLESC::Input::InputManager &inputManager;
    GLESC::WindowManager &windowManager;
}; // class Game
