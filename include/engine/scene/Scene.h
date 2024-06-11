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
#include "SceneManager.h"
#include "SceneTypes.h"
#include "engine/EngineCamera.h"
#include "engine/core/window/WindowManager.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/subsystems/input/InputManager.h"
#include "engine/core/counter/Timer.h"

namespace GLESC::Scene {
#define SCENE_DEFINITION(sceneName) \
    sceneName(GLESC::WindowManager& windowManager,\
    GLESC::ECS::EntityFactory& entityFactory,\
    GLESC::Input::InputManager& inputManager,\
    GLESC::Scene::SceneManager& sceneManager,\
    GLESC::HUD::HUDManager& hudManager,\
    GLESC::EngineCamera& camera)\
    : Scene(windowManager, entityFactory, inputManager, sceneManager,hudManager, camera) {} \
    \
    ~sceneName() override {\
        destroyEntities();\
    } \
    static const std::string getSceneName() { return #sceneName; } \
    void destroy() override { destroyEntities(); }


    class Scene {
    public:
        virtual ~Scene() {
            destroyEntities();
        };

        Scene(WindowManager& windowManager,
              ECS::EntityFactory& entityFactory,
              Input::InputManager& inputManager,
              SceneManager& sceneManager,
              HUD::HUDManager& hudManager,
              EngineCamera& camera)
            : entityFactory(entityFactory),
              windowManager(windowManager),
              inputManager(inputManager),
              sceneManager(sceneManager),
              hudManager(hudManager),
              camera(camera) {
            sceneTimer.start();
        }

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;

        EngineCamera& getCamera() { return camera; }


        void switchScene(const std::string& sceneName) { sceneManager.switchScene(sceneName); }
        Time getSceneTimeMillis() { return sceneTimer.getCurrentTime(); }
        Time getSceneTimeInSec() { return getSceneTimeMillis() / 1000.0; }

    protected:
        std::vector<ECS::EntityID>& getSceneEntities() { return sceneEntities; }

        ECS::Entity createEntity(const std::string& entityName, const ECS::EntityMetadata& metadata = {}) {
            ECS::Entity entity = entityFactory.createEntity(entityName, metadata);
            sceneEntities.push_back(entity.getID());
            return entityFactory.getEntity(sceneEntities.back());
        }

        ECS::Entity createEntity() {
            ECS::Entity entity = entityFactory.createEntity();
            sceneEntities.push_back(entity.getID());
            return entityFactory.getEntity(sceneEntities.back());
        }

        ECS::Entity getEntity(const std::string& entityName) {
            return entityFactory.getEntity(entityName);
        }

        ECS::Entity getEntity(const ECS::EntityID& entityID) {
            return entityFactory.getEntity(entityID);
        }

        void destroyEntity(const std::string& entityName) {
            auto entity = entityFactory.getEntity(entityName);
            entity.destroy();
            sceneEntities.erase(std::remove(sceneEntities.begin(), sceneEntities.end(), entity.getID()),
                                sceneEntities.end());
        }

        void destroyEntity(const ECS::EntityID& entityID) {
            auto entity = entityFactory.getEntity(entityID);
            entity.destroy();
            sceneEntities.erase(std::remove(sceneEntities.begin(), sceneEntities.end(), entityID),
                                sceneEntities.end());
        }


        void destroyEntities() {
            for (auto& entity : getSceneEntities()) {
                entityFactory.getEntity(entity).destroy();
            }
            sceneEntities.clear();
        }

        ECS::EntityFactory& entityFactory;
        WindowManager& windowManager;
        Input::InputManager& inputManager;
        HUD::HUDManager& hudManager;

    private:

        std::vector<ECS::EntityID> sceneEntities;
        SceneManager& sceneManager;
        SceneID sceneID{};
        Timer sceneTimer;
        EngineCamera& camera;
    }; // class Scene
} // namespace GLESC::Scene
