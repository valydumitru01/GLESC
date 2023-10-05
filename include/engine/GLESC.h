/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <vector>
#include <memory>
// Core
#include "engine/core/window/WindowManager.h"
#include "engine/core/counter/Counter.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLAPI.h"
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
         * @brief The engine can only be created by the main function,
         * where the game loop is defined
         */
        friend int::main(int argc, char* argv[]);
    
    public:
        void initGame();
        
        void loop();
    
    private:
        /**
         * @brief The constructor is private,
         * the engine can only be created by the main function
         */
        Engine();
        
        /**
         * @brief Processes the logic of the game
         * Is called every frame, must be called at
         * constant intervals of time as it does not use elapsed, more
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
        inline Entity getEntity(const EntityName& name);
        
        /**
         * @brief Get the Entity object with the given name, the entity can not exist.
         * @details If the entity does not exist, std::nullopt is returned.
         * @param name The name of the entity
         * @return The entity with the given name or std::nullopt if the entity does not exist
         */
        inline std::optional<Entity> tryGetEntity(const EntityName& name);
        
        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name The name of the entity
         * @return The entity with the given name
         */
        inline Entity createEntity(const EntityName& name);
        
        
        GLESC_RENDER_API graphicInterface{};
        /**
         * @brief If true, the game is running. If false, the game is stopped.
         */
        bool running{true};
        
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
        ECS ecs;
        InputSystem inputSystem;
        PhysicsSystem physicsSystem;
        RenderSystem renderSystem;
        CameraSystem cameraSystem;
        
    }; // class Engine
    inline Entity GLESC::Engine::createEntity(const EntityName& name) {
        return Entity(name, ecs);
    }
    
    inline std::optional<Entity> Engine::tryGetEntity(const EntityName& name) {
        if (ecs.tryGetEntityID(name) == NULL_ENTITY)
            return std::nullopt;
        return Entity(ecs.tryGetEntityID(name), ecs);
    }
    
    inline GLESC::Entity Engine::getEntity(const EntityName& name) {
        return Entity(ecs.getEntityID(name), ecs);
    }
} // namespace GLESC

