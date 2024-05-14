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

#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/core/window/WindowManager.h"
#include "engine/scene/SceneManager.h"

class Game {
public:
    Game(GLESC::WindowManager& windowManager,
         GLESC::ECS::EntityFactory& entityFactory,
         GLESC::Scene::SceneManager& sceneManager) :
        windowManager(windowManager),
        entityFactory(entityFactory),
        sceneManager(sceneManager) {
    }

    void init();
    void update();

private:
    GLESC::ECS::EntityFactory& entityFactory;
    GLESC::WindowManager& windowManager;
    GLESC::Scene::SceneManager& sceneManager;
}; // class Game
