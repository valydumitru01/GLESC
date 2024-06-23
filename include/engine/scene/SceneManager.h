/**************************************************************************************************
 * @file   SceneManager.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Scene handler and switcher.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "SceneTypes.h"
#include "engine/core/window/WindowManager.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/core/hash/Hasher.h"

namespace GLESC::Scene {
    class Scene;
    /**
     * @brief Manages the scenes of the game.
     * @details It contains the scenes and the current scene. Allows switching between scenes.
     */
    class SceneManager {
    public:
        SceneManager(ECS::EntityFactory& entityFactory,
                     WindowManager& windowManager)
            : entityFactory(entityFactory),
              windowManager(windowManager) {
        }

        void addScene(const std::string& sceneName, SceneID sceneID) {
            scenes[Hasher::hash(sceneName)] = sceneID;
        }

        void switchScene(const std::string& sceneName) {
            auto it = scenes.find(Hasher::hash(sceneName));
            D_ASSERT_TRUE(it != scenes.end(), "Scene not found");
            oldSceneID = currentScene;
            currentScene = it->second;
            oldSceneDestroyed = false;
            changingScene = true;
            windowManager.setWindowTitle(sceneName);
        }

        [[nodiscard]] bool isChangingScene() const {
            return changingScene;
        }

        [[nodiscard]] bool hasOldSceneBeenDestroyed() const {
            return oldSceneDestroyed;
        }

        void setOldSceneDestroyed(bool destroyed) {
            oldSceneDestroyed = destroyed;
        }

        void finishSwitchingScene() {
            changingScene = false;
        }

        SceneID& getCurrentScene() {
            return currentScene;
        }

        SceneID& getOldScene() {
            return oldSceneID;
        }



    private:
        ECS::EntityFactory& entityFactory;
        WindowManager& windowManager;
        bool changingScene{false};
        bool oldSceneDestroyed{true};
        SceneID currentScene{-1};
        SceneID oldSceneID{-1};
        std::unordered_map<Hasher::Hash, SceneID> scenes{};
    }; // class SceneManager
}; // namespace GLESC::Scene
