/**************************************************************************************************
 * @file   SceneContainer.h
 * @author Valentin Dumitru
 * @date   2024-05-14
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <unordered_map>
#include <memory>

#include "Scene.h"
#include "SceneTypes.h"

namespace GLESC::Scene {

    class SceneContainer {
    public:
        /**
         * @brief Default constructor.
         */
        SceneContainer(WindowManager& windowManager, ECS::EntityFactory& entityFactory, SceneManager& sceneManager)
            : windowManager(windowManager),
              entityFactory(entityFactory),
              sceneManager(sceneManager) {
        }

        Scene& getScene(SceneID sceneID) {
            auto it = scenes.find(sceneID);
            if (it == scenes.end()) {
                throw std::runtime_error("Scene not found");
            }
            return *(it->second);
        }

        template <typename SceneType>
        SceneID registerScene() {
            static_assert(std::is_base_of_v<Scene, SceneType>, "SceneType must inherit from Scene");
            scenes[nextSceneID] = std::make_unique<SceneType>(windowManager, entityFactory, sceneManager);
            return nextSceneID++;
        }

    private:
        SceneID nextSceneID{};
        std::unordered_map<SceneID, std::unique_ptr<Scene>> scenes;
        WindowManager& windowManager;
        ECS::EntityFactory& entityFactory;
        SceneManager& sceneManager;
    }; // class SceneContainer

} // namespace GLESC::Scene