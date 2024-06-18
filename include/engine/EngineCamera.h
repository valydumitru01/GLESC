/**************************************************************************************************
 * @file   EngineCamera.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "ecs/frontend/entity/EntityFactory.h"
#include "subsystems/input/InputManager.h"
#include "subsystems/renderer/RendererTypes.h"

#include "subsystems/hud/engine-hud/EngineHUDManager.h"

namespace GLESC {
    class Engine;

    class EngineCamera {
        friend class GLESC::Engine;

    public:
        EngineCamera(ECS::EntityFactory& entityFactory, Input::InputManager& inputManager,
                     WindowManager& windowManager) : entityFactory(entityFactory),
                                                     inputManager(inputManager),
                                                     windowManager(windowManager),
                                                     camera(entityFactory.createEntity(
                                                         "camera", {EntityType::Engine})) {
        }


        ~EngineCamera() = default;

        void setEngineHuds(HUD::EngineHUDManager* engineHuds) {
            this->engineHuds = engineHuds;
        }
        ECS::Entity& getEntity() { return camera; }
        void setForce(float speed) { cameraSpeed = speed; }
        void setSensitivity(float sensitivity) { cameraSensitivity.set(sensitivity); }

    private:
        /**
         * @brief Moves the camera downwards
         */
        void moveDown();
        /**
         * @brief Moves the camera upwards
         */
        void moveUp();
        /**
         * @brief Moves the camera to the right
         * @note Camera movement is done with inverse directions, because camera looks at the
         * opposite direction of its forward vector
         */
        void moveRight();
        /**
         * @brief Moves the camera to the left
         * @note Camera movement is done with inverse directions, because camera looks at the
         * opposite direction of its forward vector
         */
        void moveLeft();
        /**
         * @brief Moves the camera backwards
         * @note Camera movement is done with inverse directions, because camera looks at the
         * opposite direction of its forward vector
         */
        void moveBackward();
        /**
         * @brief Moves the camera forwards
         * @note Camera movement is done with inverse directions, because camera looks at the
         * opposite direction of its forward vector
         */
        void moveForward();
        /**
         * @brief Accelerates the camera (increases the speed by a factor of 2)
         */
        void accelerate();
        /**
         * @brief Decelerates the camera (decreases the speed by a factor of 2)
         */
        void decelerate();

        /**
         * @brief Rotates the camera based on the mouse movement
         * @details It adjusts the pitch and yaw of the camera based on the mouse movement
         * The pitch has a constraint of 45 degrees.
         * @param deltaMouse The mouse movement
         */
        void rotate(const MousePosition& deltaMouse);

        void setupCamera();


        static constexpr float defaultCameraAirFriction = 0.1f;
        static constexpr float defaultFarPlane = 1000.f;
        static constexpr float defaultNearPlane = 0.1f;
        static constexpr float defaultFov = 45.f;
        static constexpr bool defaultCameraAffectedByGravity = false;

        float cameraSpeed = 25.f;
        Render::Intensity<float> cameraSensitivity{1.0f};
        float cameraPitchConstraint = 45.0f;

        ECS::Entity camera;


        ECS::EntityFactory& entityFactory;
        Input::InputManager& inputManager;
        WindowManager& windowManager;


        bool debugHUDActive = false;
        HUD::EngineHUDManager* engineHuds{};
    }; // class EngineCamera
} // namespace GLESC
