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
#include "ecs/ECSContainer.h"
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
        friend int ::main();
    
    
    protected:
        Engine();
    
    private:
        /**
         * @brief Is called every frame, must be called at constant intervals of time as it does not use elapsed, more
         * information https://www.gameprogrammingpatterns.com/game-loop.html
         */
        void update();
        
        /**
         * @brief The input of the game
         */
        void processInput();
        
        /**
         * @brief The rendering of the game
         * @param timeOfFrame The time of the frame
         */
        void render(double timeOfFrame);
    
        inline Entity getEntity(EntityName name) {
            return Entity(GLESC::ECS::getECS()->getEntityID(name));
        }
    
        inline Entity createEntity(EntityName name) {
            return Entity(name);
        }
        
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
    
    public:
        void initGame();
        void loop();
    }; // class Engine
} // namespace GLESC