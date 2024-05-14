/**************************************************************************************************
 * @file   SceneDependecies.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/backend/ECS.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/subsystems/input/InputManager.h"
#include "engine/subsystems/physics/PhysicsManager.h"

namespace GLESC::Scene {
    class SceneDependecies {
        SceneDependecies(ECS::EntityFactory& entityFactory,
                         WindowManager& windowManager) :
            entityFactory(entityFactory), windowManager(windowManager) {
        }
    protected:
        ECS::EntityFactory& entityFactory;
        WindowManager& windowManager;
    }; // class SceneDependecies
} // namespace GLESC::Scene
