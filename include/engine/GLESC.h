/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <vector>
#include <memory>
// Configurations for the engine, directives and macros
#include "Config.h"
// Core
#include "engine/core/window/WindowManager.h"
#include "engine/core/counter/Counter.h"
#include "engine/core/low-level-renderer/graphic-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
// ECS
#include "ecs/ECSTypes.h"
// Entity
#include "engine/ecs/frontend/entity/Entity.h"
// Systems
#include "engine/ecs/frontend/system/System.h"
#include "engine/ecs/frontend/system/systems/PhysicsSystem.h"
#include "engine/ecs/frontend/system/systems/RenderSystem.h"
#include "engine/ecs/frontend/system/systems/CameraSystem.h"
#include "engine/ecs/frontend/system/systems/InputSystem.h"

// Subsystems
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/subsystems/input/InputManager.h"
#include "engine/subsystems/physics/PhysicsManager.h"

namespace GLESC {
    class Engine {
        /**
         * @brief The engine can only be created by the main function, where the game loop is defined
         */
        friend int::main();
    
    public:
        void initGame();
        
        void loop();
    
    private:
        /**
         * @brief The constructor is private, the engine can only be created by the main function
         */
        Engine();
        
        /**
         * @brief Processes the logic of the game
         * Is called every frame, must be called at constant intervals of time as it does not use elapsed, more
         * information https://www.gameprogrammingpatterns.com/game-loop.html
         */
        void update();
        
        /**
         * @brief Processes the input of the game
         */
        void processInput();
        
        /**
         * @brief Processes the rendering of the game
         * Can be called at variable intervals of time as it uses elapsed
         * @param timeOfFrame The time of the frame
         */
        void render(double timeOfFrame);
        
        /**
         * @brief Get the Entity object with the given name, the entity must exist.
         * @param name
         * @return
         */
        static inline Entity getEntity(EntityName name);
        
        /**
         * @brief Get the Entity object with the given name, the entity can not exist.
         * @details If the entity does not exist, std::nullopt is returned.
         * @param name The name of the entity
         * @return The entity with the given name or std::nullopt if the entity does not exist
         */
        static inline std::optional<Entity> tryGetEntity(EntityName name);
        
        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name The name of the entity
         * @return The entity with the given name
         */
        static inline Entity createEntity(EntityName name);
        
        
        /**
         * @brief If true, the game is running. If false, the game is stopped.
         */
        bool running = true;
        
        /**
         * @brief This is the graphic interface, it is used as low level interface to the graphics API
         */
        #ifdef GLESC_RENDER_OPENGL
        OpenGLGDI graphicInterface;
        #elif defined(RENDER_VULKAN)
        VulkanGDI graphicInterface;
        #endif
        
        /**
         * @brief Handles the window of the game
         */
        GLESC::WindowManager windowManager;
        /**
         * @brief Handles the input of the game
         * @details Handles all the inputs of the game, and stores the state of the inputs.
         */
        InputManager inputManager;
        /**
         * @brief Handles the rendering of the game
         * @details Handles all the rendering of the game, provides a high level interface to the graphics API.
         * Can be used to render 2D and 3D graphics, including generating meshes and textures.
         */
        GLESC::Renderer renderer;
        
        PhysicsManager physicsManager;
        
        InputSystem inputSystem;
        PhysicsSystem physicsSystem;
        RenderSystem renderSystem;
        CameraSystem cameraSystem;
        
    }; // class Engine
} // namespace GLESC

inline GLESC::Entity GLESC::Engine::createEntity(EntityName name) {
    return Entity(name);
}

inline std::optional<GLESC::Entity> GLESC::Engine::tryGetEntity(EntityName name) {
    if (GLESC::ECS::getECS()->tryGetEntityID(name) == NULL_ENTITY)
        return std::nullopt;
    return Entity(GLESC::ECS::getECS()->tryGetEntityID(name));
}

inline GLESC::Entity GLESC::Engine::getEntity(EntityName name) {
    return Entity(GLESC::ECS::getECS()->getEntityID(name));
}