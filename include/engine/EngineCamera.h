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
#define CAMERA_SPEED 0.3f
#define CAMERA_X_ROTATION_LIMIT 45.0f
#define CAMERA_SENSITIVITY 1.f
#include "ecs/frontend/component/CameraComponent.h"
#include "ecs/frontend/component/InputComponent.h"
#include "ecs/frontend/component/TransformComponent.h"
#include "ecs/frontend/entity/EntityFactory.h"
#include "subsystems/input/InputManager.h"

namespace GLESC {
    class EngineCamera {
    public:
        EngineCamera(ECS::EntityFactory& entityFactory, Input::InputManager& inputManager,
                     WindowManager& windowManager) : entityFactory(entityFactory),
                                                     inputManager(inputManager),
                                                     windowManager(windowManager),
                                                     cameraSpeed(CAMERA_SPEED),
                                                     cameraSensitivity(CAMERA_SENSITIVITY),
                                                     cameraPitchConstraint(CAMERA_X_ROTATION_LIMIT),
                                                     camera(entityFactory.createEntity("camera")) {
        }

        void setupCamera() {
            camera.addComponent<ECS::CameraComponent>()
                  .addComponent<ECS::TransformComponent>()
                  .addComponent<ECS::InputComponent>();


            camera.getComponent<ECS::CameraComponent>().perspective.setFarPlane(1000.0f);
            camera.getComponent<ECS::CameraComponent>().perspective.setNearPlane(0.1f);
            camera.getComponent<ECS::CameraComponent>().perspective.setFovDegrees(60.0f);
            camera.getComponent<ECS::CameraComponent>().perspective.setViewWidth(
                static_cast<float>(windowManager.getSize().width));
            camera.getComponent<ECS::CameraComponent>().perspective.
                   setViewHeight(static_cast<float>(windowManager.getSize().height));
            // IMPORTANT! Camera movement needs to be done with inverse directions, because it looks at the
            // opposite direction of the forward vector
            Input::KeyCommand moveForward = Input::KeyCommand([&] {
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");
                cameraEntity.getComponent<ECS::TransformComponent>().transform.addPosition(
                    -cameraEntity.getComponent<ECS::TransformComponent>().transform.forward() * cameraSpeed);
            });

            Input::KeyCommand moveBackward = Input::KeyCommand([&] {
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");
                cameraEntity.getComponent<ECS::TransformComponent>().transform.addPosition(
                    cameraEntity.getComponent<ECS::TransformComponent>().transform.forward() * cameraSpeed);
            });

            Input::KeyCommand moveLeft = Input::KeyCommand([&] {
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");
                cameraEntity.getComponent<ECS::TransformComponent>().transform.addPosition(
                    cameraEntity.getComponent<ECS::TransformComponent>().transform.right() * cameraSpeed);
            });

            Input::KeyCommand moveRight = Input::KeyCommand([&] {
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");
                cameraEntity.getComponent<ECS::TransformComponent>().transform.addPosition(
                    -cameraEntity.getComponent<ECS::TransformComponent>().transform.right() * cameraSpeed);
            });

            Input::KeyCommand moveUp = Input::KeyCommand([&] {
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");
                cameraEntity.getComponent<ECS::TransformComponent>().transform.addPosition(
                    Transform::Transform::worldUp * cameraSpeed);
            });

            Input::KeyCommand moveDown = Input::KeyCommand([&] {
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");
                cameraEntity.getComponent<ECS::TransformComponent>().transform.addPosition(
                    -Transform::Transform::worldUp * cameraSpeed);
            });

            Input::KeyCommand accelerate = Input::KeyCommand([&] {
                cameraSpeed *= 2;
            });

            Input::KeyCommand decelerate = Input::KeyCommand([&] {
                cameraSpeed /= 2;
            });

            Input::MouseCommand rotate = Input::MouseCommand([&](const MousePosition& deltaMouse) {
                if (!inputManager.isMouseRelative()) return;
                ECS::Entity cameraEntity = entityFactory.getEntity("camera");

                auto& transformComp = cameraEntity.getComponent<ECS::TransformComponent>().transform;
                float cameraSensitivityValue = cameraSensitivity.get();

                // Adjust the pitch based on mouse Y movement (up/down)
                float mouseAdditionPitch = deltaMouse.getY() * cameraSensitivityValue;
                float nextMousePitch = transformComp.getRotation().getX() + mouseAdditionPitch;

                // Only apply pitch rotation if it is within the constraints
                if (nextMousePitch < cameraPitchConstraint && nextMousePitch > -cameraPitchConstraint) {
                    transformComp.setRotation(Transform::RotationAxis::Pitch, nextMousePitch);
                }

                // Adjust the yaw based on mouse X movement (left/right)
                float mouseAdditionYaw = -deltaMouse.getX() * cameraSensitivityValue;
                transformComp.addRotation(Transform::RotationAxis::Yaw, mouseAdditionYaw);
            });

            Input::KeyCommand mouseRelativeMove = Input::KeyCommand([&] {
                inputManager.setMouseRelative(!inputManager.isMouseRelative());
            });

            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::W, Input::KeyAction::ONGOING_PRESSED}, moveForward);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::S, Input::KeyAction::ONGOING_PRESSED}, moveBackward);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::A, Input::KeyAction::ONGOING_PRESSED}, moveLeft);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::D, Input::KeyAction::ONGOING_PRESSED}, moveRight);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::SPACE, Input::KeyAction::ONGOING_PRESSED}, moveUp);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::LEFT_SHIFT, Input::KeyAction::ONGOING_PRESSED}, moveDown);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::LEFT_CTRL, Input::KeyAction::ONCE_PRESSED}, mouseRelativeMove);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::LEFT_ALT, Input::KeyAction::ONCE_PRESSED}, accelerate);
            camera.getComponent<ECS::InputComponent>().input.subscribeKey(
                {Input::Key::LEFT_ALT, Input::KeyAction::ONCE_RELEASED}, decelerate);

            camera.getComponent<ECS::InputComponent>().input.setMouseCommand(rotate);
        }

        ~EngineCamera() = default;

        ECS::Entity& getCamera() { return camera; }

    private:
        ECS::EntityFactory& entityFactory;
        Input::InputManager& inputManager;
        WindowManager& windowManager;

        float cameraSpeed;
        Render::Intensity<float> cameraSensitivity;
        float cameraPitchConstraint;
        ECS::Entity camera;
    }; // class EngineCamera
} // namespace GLESC
