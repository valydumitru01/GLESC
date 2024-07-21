/**************************************************************************************************
 * @file   Scene.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
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
    /**
     * @brief Facilitates the creation of a scene.
     * @details It implements the constructor and the destructor of the scene, along with some helper functions.
     * @param sceneName
     */
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
        destroy();\
    } \
    static const std::string getSceneName() { return #sceneName; } \
    void destroy() override { destroyEntities();  }

    /**
     * @brief Contains all the classes and functions related to the scene management.
     * Any scene of the game should be derived from the Scene class.
     */
    class Scene {
    public:
        virtual ~Scene() = default;

        /**
         * @brief Constructor for the Scene class.
         * @param windowManager The window manager.
         * @param entityFactory The entity factory.
         * @param inputManager The input manager.
         * @param sceneManager The scene manager.
         * @param hudManager The HUD manager.
         * @param camera The camera.
         */
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

        /**
         * Flags the scene as initialized
         * @param initializedParam
         */
        void setInitialized(bool initializedParam) { initialized = initializedParam; }

        /**
         * @brief Checks if the scene is initialized.
         * @return True if the scene is initialized, false otherwise.
         */
        [[nodiscard]] bool isInitialized() const { return initialized; }
        /**
         * @brief Initializes the scene. Must be implemented by the derived class.
         */
        virtual void init() = 0;
        /**
         * @brief Updates the scene. Must be implemented by the derived class.
         */
        virtual void update() = 0;
        /**
         * @brief Destroys the scene. Must be implemented by the derived class.
         */
        virtual void destroy() = 0;

        /**
         * Gets the camera object of the scene
         * @return The camera object
         */
        EngineCamera& getCamera() { return camera; }

        /**
         * @brief Switches to another scene.
         * @tparam SceneType The type of the scene to switch to.
         */
        template <typename SceneType>
        void switchScene() {
            sceneManager.switchScene(SceneType::getSceneName());
        }

        /**
         * @brief Gets the scene time in milliseconds.
         * @return The scene time in milliseconds.
         */
        TimeMillis getSceneTimeMillis() { return sceneTimer.getCurrentTime(); }
        /**
         * @brief Gets the scene time in seconds.
         * @return The scene time in seconds.
         */
        TimeSecondsUI getSceneTimeSeconds() { return static_cast<TimeSecondsUI>(getSceneTimeMillis() / 1000.0); }

    protected:
        /**
         * @brief Gets the scene entities.
         * @details Only returns the entities that are part of the scene.
         * @return The scene entities.
         */
        [[nodiscard]] std::vector<ECS::EntityID>& getSceneEntities() { return sceneEntities; }

        /**
         * @brief Creates an entity and adds it to the scene.
         * @details Stores the entity ID in the sceneEntities vector.
         * @param entityName The name of the entity.
         * @param metadata The metadata of the entity.
         * @return The created entity.
         */
        ECS::Entity createEntity(const std::string& entityName, const ECS::EntityMetadata& metadata = {}) {
            // TODO: Check if an entity that is an instace shaderes name with another entity that is not an instance
            ECS::Entity entity = entityFactory.createEntity(entityName, metadata);
            sceneEntities.push_back(entity.getID());
            return entityFactory.getEntity(sceneEntities.back());
        }

        /**
         * @brief Creates an entity and adds it to the scene.
         * @details Creates entity with default name and metadata.
         * @details Stores the entity ID in the sceneEntities vector.
         * @return The created entity.
         */
        ECS::Entity createEntity() {
            ECS::Entity entity = entityFactory.createEntity();
            sceneEntities.push_back(entity.getID());
            return entityFactory.getEntity(sceneEntities.back());
        }

        /**
         * @brief Gets an entity by name.
         * @param entityName The name of the entity.
         * @return The entity.
         */
        ECS::Entity getEntity(const std::string& entityName) {
            return entityFactory.getEntity(entityName);
        }

        /**
         * @brief Gets an entity by ID.
         * @param entityID The ID of the entity.
         * @return The entity.
         */
        ECS::Entity getEntity(const ECS::EntityID& entityID) {
            return entityFactory.getEntity(entityID);
        }

        /**
         * @brief Destroys an entity by name.
         * @details This will alert the ECSManager to destroy the entity through the entity object.
         * Also erases the entity from the sceneEntities vector.
         * @param entityName The name of the entity.
         */
        void destroyEntity(const std::string& entityName) {
            auto entity = entityFactory.getEntity(entityName);
            entity.destroy();
            sceneEntities.erase(std::remove(sceneEntities.begin(), sceneEntities.end(), entity.getID()),
                                sceneEntities.end());
        }

        /**
         * @brief Destroys an entity by ID.
         * @details This will alert the ECSManager to destroy the entity through the entity object.
         * Also erases the entity from the sceneEntities vector.
         * @param entityID The ID of the entity.
         */
        void destroyEntity(const ECS::EntityID& entityID) {
            auto entity = entityFactory.getEntity(entityID);
            entity.destroy();
            sceneEntities.erase(std::remove(sceneEntities.begin(), sceneEntities.end(), entityID),
                                sceneEntities.end());
        }

        /**
         * @brief Adds a window to the scene.
         * @tparam WindowType The type of the window to add.
         * @return The ID of the window.
         */
        template <typename WindowType>
        [[nodiscard]] HUD::HUDManager::WindowID addWindow() {
            D_ASSERT_TRUE((std::is_base_of_v<GLESC::InGameWindow, WindowType>),
                          "WindowType must be derived from InGameWindow");
            sceneWindows.push_back(std::make_unique<WindowType>());
            windowReferences.push_back(hudManager.addWindow(*sceneWindows.back()));
            return windowReferences.back();
        }

        /**
         * @brief Gets a window by ID.
         * @tparam WindowType The type of the window to get.
         * @param id The ID of the window.
         * @return The window.
         */
        template <typename WindowType>
        [[nodiscard]] WindowType& getWindow(HUD::HUDManager::WindowID id) {
            return dynamic_cast<WindowType&>(hudManager.getWindow(id));
        }

        /**
         * @brief Removes a window by ID.
         */
        void destroyWindows() {
            for (auto& window : windowReferences) {
                hudManager.removeWindow(window);
            }
            windowReferences.clear();
            sceneWindows.clear();
        }

        /**
         * @brief Destroys all entities in the scene.
         */
        void destroyEntities() {
            for (auto& entity : getSceneEntities()) {
                entityFactory.getEntity(entity).destroy();
            }
            sceneEntities.clear();
        }


        ECS::EntityFactory& entityFactory;
        WindowManager& windowManager;
        Input::InputManager& inputManager;

    private:
        HUD::HUDManager& hudManager;
        std::vector<HUD::HUDManager::WindowID> windowReferences;
        std::vector<std::unique_ptr<GLESC::InGameWindow>> sceneWindows;
        bool initialized = false;
        std::vector<ECS::EntityID> sceneEntities;
        SceneManager& sceneManager;
        SceneID sceneID{};
        Timer sceneTimer;
        EngineCamera& camera;
    }; // class Scene
} // namespace GLESC::Scene
