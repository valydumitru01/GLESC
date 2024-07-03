/**************************************************************************************************
 * @file   EngineCamera.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
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

        /**
         * @brief Prepares the camera entity with its components and it's initial values
         */
        void setupCamera();

        /**
         * @brief Camera friction value is 0.1f, makes the camera move like swimming through air as
         * 0.1 is a relatively big value for a friction
         */
        static constexpr float defaultCameraAirFriction = 0.1f;
        /**
         * @brief The far plane is at 1000 units, far enough to see the whole scene
         */
        static constexpr float defaultFarPlane = 1000.f;
        /**
         * @brief The near plane is at 0.1 units
         */
        static constexpr float defaultNearPlane = 0.1f;
        /**
         * @brief The field of view is 45 degrees
         */
        static constexpr float defaultFov = 45.f;
        /**
         * @brief The camera is not affected by gravity
         */
        static constexpr bool defaultCameraAffectedByGravity = false;

        /**
         * @brief The camera speed is 25 units per second
         */
        float cameraSpeed = 25.f;
        /**
         * @brief The camera sensitivity is 1.0f, is the sensitivity of the mouse movement
         */
        Render::Intensity<float> cameraSensitivity{1.0f};
        /**
         * @brief The camera pitch constraint is 45 degrees
         */
        float cameraPitchConstraint = 45.0f;
        /**
         * @brief The camera entity
         */
        ECS::Entity camera;


        ECS::EntityFactory& entityFactory;
        Input::InputManager& inputManager;
        WindowManager& windowManager;


        bool debugHUDActive = false;
        /**
         * @brief A reference to the engine huds, the camer allows hide or show them with the input
         */
        HUD::EngineHUDManager* engineHuds{};
    }; // class EngineCamera
} // namespace GLESC
