#include "engine/EngineCamera.h"

#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"

using namespace GLESC;

void EngineCamera::moveBackward() {
    camera.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
        camera.getComponent<ECS::TransformComponent>().transform.forward(), cameraSpeed);
}

void EngineCamera::moveForward() {
    camera.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
        camera.getComponent<ECS::TransformComponent>().transform.forward(), -cameraSpeed);
}

void EngineCamera::moveLeft() {
    camera.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
        camera.getComponent<ECS::TransformComponent>().transform.right(), cameraSpeed);
}

void EngineCamera::moveRight() {
    camera.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
        -camera.getComponent<ECS::TransformComponent>().transform.right(), cameraSpeed);
}

void EngineCamera::moveUp() {
    camera.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
        Transform::Transform::worldUp, cameraSpeed);
}

void EngineCamera::moveDown() {
    camera.getComponent<ECS::PhysicsComponent>().physics.addDirectionalForce(
        -Transform::Transform::worldUp, cameraSpeed);
}

void EngineCamera::accelerate() {
    cameraSpeed *= 2;
}

void EngineCamera::decelerate() {
    cameraSpeed /= 2;
}


void EngineCamera::rotate(const MousePosition& deltaMouse) {
    if (!inputManager.isMouseRelative()) return;


    auto& transformComp = camera.getComponent<ECS::TransformComponent>().transform;
    float cameraSensitivityValue = cameraSensitivity.get();

    // Adjust the pitch based on mouse Y movement (up/down)
    float mouseAdditionPitch = -deltaMouse.getY() * cameraSensitivityValue;
    float nextMousePitch = transformComp.getRotation().getX() + mouseAdditionPitch;

    // Only apply pitch rotation if it is within the constraints
    if (nextMousePitch < cameraPitchConstraint &&
        nextMousePitch > -cameraPitchConstraint) {
        transformComp.setRotation(Transform::RotationAxis::Pitch, nextMousePitch);
    }

    // Adjust the yaw based on mouse X movement (left/right)
    float mouseAdditionYaw = -deltaMouse.getX() * cameraSensitivityValue;
    transformComp.addRotation(Transform::RotationAxis::Yaw, mouseAdditionYaw);
}


void EngineCamera::setupCamera() {
    camera.addComponent<ECS::CameraComponent>()
          .addComponent<ECS::TransformComponent>()
          .addComponent<ECS::InputComponent>()
          .addComponent<ECS::PhysicsComponent>();
    camera.getComponent<ECS::PhysicsComponent>().physics.setAirFriction(defaultCameraAirFriction);
    camera.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(defaultCameraAffectedByGravity);
    camera.getComponent<ECS::CameraComponent>().perspective.setFarPlane(defaultFarPlane);
    camera.getComponent<ECS::CameraComponent>().perspective.setNearPlane(defaultNearPlane);
    camera.getComponent<ECS::CameraComponent>().perspective.setFovDegrees(defaultFov);
    camera.getComponent<ECS::CameraComponent>().perspective.setViewWidth(
        static_cast<float>(windowManager.getSize().width));
    camera.getComponent<ECS::CameraComponent>().perspective.
           setViewHeight(static_cast<float>(windowManager.getSize().height));

    Input::KeyCommand moveForwardCommand = Input::KeyCommand([&] { moveForward(); });
    Input::KeyCommand moveBackwardCommand = Input::KeyCommand([&] { moveBackward(); });
    Input::KeyCommand moveLeftCommand = Input::KeyCommand([&] { moveLeft(); });
    Input::KeyCommand moveRightCommand = Input::KeyCommand([&] { moveRight(); });
    Input::KeyCommand moveUpCommand = Input::KeyCommand([&] { moveUp(); });
    Input::KeyCommand moveDownCommand = Input::KeyCommand([&] { moveDown(); });
    Input::KeyCommand accelerateCommand = Input::KeyCommand([&] { accelerate(); });
    Input::KeyCommand decelerateCommand = Input::KeyCommand([&] { decelerate(); });
    Input::MouseCommand rotateCommand =
        Input::MouseCommand([&](const MousePosition& deltaMouse) { rotate(deltaMouse); });


    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::W, Input::KeyAction::ONGOING_PRESSED}, moveForwardCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::S, Input::KeyAction::ONGOING_PRESSED}, moveBackwardCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::A, Input::KeyAction::ONGOING_PRESSED}, moveLeftCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::D, Input::KeyAction::ONGOING_PRESSED}, moveRightCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::SPACE, Input::KeyAction::ONGOING_PRESSED}, moveUpCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_SHIFT, Input::KeyAction::ONGOING_PRESSED}, moveDownCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_ALT, Input::KeyAction::ONCE_PRESSED}, accelerateCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_ALT, Input::KeyAction::ONCE_RELEASED}, decelerateCommand);
    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::ONE, Input::KeyAction::ONCE_PRESSED}, {
            [&] {
                inputManager.setMouseRelative(!inputManager.isMouseRelative());
            }
        });
    Input::KeyCommand toggleDebug = Input::KeyCommand([&] {
        D_ASSERT_NOT_NULLPTR(engineHuds, "Engine HUDs must not be null");
        debugHUDActive = !debugHUDActive;
        engineHuds->toggle();

        inputManager.setMouseRelative(debugHUDActive);
    });

    camera.getComponent<ECS::InputComponent>().input.subscribeKey(
        {Input::Key::LEFT_CTRL, Input::KeyAction::ONCE_PRESSED}, toggleDebug);
    camera.getComponent<ECS::InputComponent>().input.setMouseCommand(rotateCommand);
}
