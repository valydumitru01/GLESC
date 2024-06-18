/******************************************************************************
 * @file   GLESC.h
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
#include "engine/core/counter/FPSManager.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLAPI.h"

// ECS
#include "ecs/frontend/entity/EntityFactory.h"
#include "ecs/frontend/system/System.h"

// Subsystems
#include "engine/subsystems/hud/engine-hud/EngineHUDManager.h"
#include "engine/subsystems/hud/HUDManager.h"
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/subsystems/input/InputManager.h"
#include "engine/subsystems/physics/PhysicsManager.h"
#include "subsystems/physics/CollisionManager.h"

// Game
#include "EngineCamera.h"
#include "game/Game.h"
#include "scene/SceneContainer.h"
#include "scene/SceneManager.h"


namespace GLESC {
    class Engine {
        /**
         * @brief The engine can only be created by the main function,
         * where the game loop is defined
         */
        friend int ::main(int argc, char* argv[]);

    private:
        std::vector<std::unique_ptr<ECS::System>> createSystems();
        void createEngineEntities();

        void registerStats() const;


        /**
         * @brief The constructor is private,
         * the engine can only be created by the main function
         */
        explicit Engine(FPSManager& fpsManager);

        ~Engine();

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
         * @brief If true, the game is running. If false, the game is stopped.
         */
        bool running{true};

        /**
         * @brief Handles the window of the game
         */
        WindowManager windowManager;
        /**
         * @brief Handles the input of the game
         * @details Handles all the inputs of the game, and stores the state of the inputs.
         */
        Input::InputManager inputManager;
        /**
         * @brief Handles the rendering of the game
         * @details Handles all the rendering of the game, provides a high level interface to the graphics API.
         * Can be used to render 2D and 3D graphics, including generating meshes and textures.
         */
        Render::Renderer renderer;

        Physics::PhysicsManager physicsManager;
        Physics::CollisionManager collisionManager;
        HUD::HUDManager hudManager;
        TextureFactory textureFactory;

        FPSManager& fpsManager;

        HUD::EngineHUDManager engineHuds;
        ECS::ECSCoordinator ecs;
        ECS::EntityFactory entityFactory;

        EngineCamera engineCamera;

        std::vector<std::unique_ptr<ECS::System>> updateSystems;

        Scene::SceneManager sceneManager;
        Scene::SceneContainer sceneContainer;
        Game game;
    }; // class Engine
} // namespace GLESC
