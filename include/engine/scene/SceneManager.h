/**************************************************************************************************
 * @file   SceneManager.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "SceneDependecies.h"

namespace GLESC::Scene {
    class Scene;

    class SceneManager : public SceneDependecies {
    public:
        SceneManager(ECS::EntityFactory& entityFactory,
                     WindowManager& windowManager) :
            SceneDependecies(entityFactory, windowManager) {
        }

        template <typename SceneType>
        void registerScene(const std::string& sceneName) {
            S_ASSERT_TRUE(std::is_base_of_v<Scene, SceneType>, "SceneType must inherit from Scene");
            D_ASSERT_TRUE(scenes.find(sceneName) == scenes.end(), "Scene already registered");
            scenes[sceneName] =
                std::make_unique<SceneType>(entityFactory, windowManager);
        }

        void switchScene(const std::string& sceneName) {
            auto it = scenes.find(sceneName);
            D_ASSERT_TRUE(it != scenes.end(), "Scene not found");
            currentScene = std::move(it->second);
        }

        Scene& getCurrentScene() {
            S_ASSERT_TRUE(currentScene, "No scene set");
            return *currentScene;
        }

    private:
        std::unique_ptr<Scene> currentScene{};
        std::unordered_map<std::string, std::unique_ptr<Scene>> scenes{};
    }; // class SceneManager
}; // namespace GLESC::Scene
