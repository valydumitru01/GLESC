/**************************************************************************************************
 * @file   Scene.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "SceneDependecies.h"
#include "SceneManager.h"

namespace GLESC::Scene {
    class Scene : public SceneDependecies {
    public:
        virtual ~Scene() = default;

        Scene(WindowManager& windowManager,
              ECS::EntityFactory& entityFactory,
              SceneManager& sceneManager) :
            SceneDependecies(entityFactory, windowManager),
            sceneManager(sceneManager) {
        }

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;

        ECS::Entity getCamera() { return entityFactory.getEntity("camera"); }
        void switchScene(const std::string& sceneName) { sceneManager.switchScene(sceneName); }

    private:
        SceneManager& sceneManager;
    }; // class Scene
} // namespace GLESC::Scene
