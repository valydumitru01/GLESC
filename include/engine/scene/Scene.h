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
#include "SceneTypes.h"
#include "engine/core/counter/Timer.h"

namespace GLESC::Scene {
    class Scene : public SceneDependecies {
    public:
        virtual ~Scene() {
            destroyEntities();
        };

        Scene(WindowManager& windowManager,
              ECS::EntityFactory& entityFactory,
              SceneManager& sceneManager) :
            SceneDependecies(entityFactory, windowManager),
            sceneManager(sceneManager) {
            sceneTimer.start();
        }

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;

        ECS::Entity getCamera() { return entityFactory.getEntity("camera"); }
        void switchScene(const std::string& sceneName) { sceneManager.switchScene(sceneName); }
        Time getSceneTime() { return sceneTimer.getCurrentTime(); }

    protected:
        std::vector<ECS::Entity>& getSceneEntities() { return sceneEntities; }

        ECS::Entity& createEntity(const std::string& entityName) {
            ECS::Entity entity = entityFactory.createEntity(entityName);
            sceneEntities.push_back(entity);
            return sceneEntities.back();
        }
        void destroyEntities() {
            for (auto& entity : getSceneEntities()) {
                entity.destroy();
            }
            sceneEntities.clear();
        }
    private:
        std::vector<ECS::Entity> sceneEntities;
        SceneManager& sceneManager;
        SceneID sceneID{};
        Timer sceneTimer;
    }; // class Scene
} // namespace GLESC::Scene
