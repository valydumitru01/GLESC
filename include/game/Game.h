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
#include "engine/scene/SceneContainer.h"
#include "engine/scene/SceneManager.h"

class Game {
public:
    Game(GLESC::Scene::SceneManager& sceneManager,
         GLESC::Scene::SceneContainer& sceneContainer) :
        sceneManager(sceneManager), sceneContainer(sceneContainer) {
    }

    void init();
    void update();

private:
    template <typename SceneType>
    void registerScene(const std::string& sceneName) {
        GLESC::Scene::SceneID id = sceneContainer.registerScene<SceneType>();
        sceneManager.addScene(sceneName, id);
    }

    void switchScene(const std::string& sceneName) {
        sceneManager.switchScene(sceneName);
        sceneContainer.getScene(sceneManager.getCurrentScene()).init();
    }

    GLESC::Scene::SceneManager& sceneManager;
    GLESC::Scene::SceneContainer& sceneContainer;
}; // class Game
