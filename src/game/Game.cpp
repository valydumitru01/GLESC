/******************************************************************************
 * @file   Game.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/GLESC.h"
#include "engine/ecs/frontend/entity/Entity.h"

// Components
#include "game/Game.h"

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"


void GLESC::Engine::initGame() {
    // TODO: Create a game class
    ECS::Entity player = createEntity("player");
    ECS::Entity camera = createEntity("camera");
    player.addComponent(RenderComponent())
            .addComponent(TransformComponent())
            .addComponent(PhysicsComponent())
            .addComponent(InputComponent());

    camera.addComponent(CameraComponent())
            .addComponent(TransformComponent())
            .addComponent(InputComponent());

    camera.getComponent<CameraComponent>().viewWidth = static_cast<float>(windowManager.getWindowSize().width);
    camera.getComponent<CameraComponent>().viewHeight = static_cast<float>(windowManager.getWindowSize().height);
    KeyCommand moveForward = KeyCommand([&] {
        ECS::Entity cameraEntity = getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position += cameraEntity.getComponent<
                    TransformComponent>().
                transform.forward();
    });
    KeyCommand moveBackward = KeyCommand([&] {
        ECS::Entity cameraEntity = getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position -= cameraEntity.getComponent<
                    TransformComponent>().
                transform.forward();
    });
    KeyCommand moveLeft = KeyCommand([&] {
        ECS::Entity cameraEntity = getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position -= cameraEntity.getComponent<
                    TransformComponent>().
                transform.right();
    });
    KeyCommand moveRight = KeyCommand([&] {
        ECS::Entity cameraEntity = getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position += cameraEntity.getComponent<
                    TransformComponent>().
                transform.right();
    });

    KeyCommand mouseRelativeMove = KeyCommand([&] {
        inputManager.setMouseRelative(!inputManager.isMouseRelative());
    });

    MouseCommand rotate = MouseCommand([&](const MousePosition &deltaMouse) {
        // We can assume the mouse will be in the center of the screen
        // Rotate will only work if the mouse is in relative mode
        if (!inputManager.isMouseRelative()) return;
        ECS::Entity cameraEntity = getEntity("camera");
        // A threshhold is needed because the mouse orbitates around 1 and -1, because it works in pixels (ints)
        if (std::abs(deltaMouse.getX()) < 2 && std::abs(deltaMouse.getY()) < 2) return;
        cameraEntity.getComponent<TransformComponent>().transform.rotation.y() +=
            static_cast<float>(deltaMouse.getX()) * 0.1f;
        cameraEntity.getComponent<TransformComponent>().transform.rotation.x() +=
            static_cast<float>(deltaMouse.getY()) * 0.1f;

    });

    camera.getComponent<InputComponent>().subscribedKeys = {
        {{Key::W, KeyAction::ONGOING_PRESSED}, moveForward},
        {{Key::S, KeyAction::ONGOING_PRESSED}, moveBackward},
        {{Key::A, KeyAction::ONGOING_PRESSED}, moveLeft},
        {{Key::D, KeyAction::ONGOING_PRESSED}, moveRight},
        {{Key::LEFT_SHIFT, KeyAction::ONCE_PRESSED}, mouseRelativeMove}
    };
    camera.getComponent<InputComponent>().mouseCommand = rotate;

    player.getComponent<RenderComponent>().mesh = MeshFactory::cube(RGBA(1, 0, 0, 1));
    ColorMesh cube = MeshFactory::cube(RGBA(1, 0, 0, 1));
    ColorMesh mesh = player.getComponent<RenderComponent>().mesh;
    player.getComponent<PhysicsComponent>().velocity.z(1);
}


void GLESC::Engine::loop() {
    GLESC::ECS::Entity camera = getEntity("camera");
    camera.getComponent<CameraComponent>().viewWidth = static_cast<float>(windowManager.getWindowSize().width);
    camera.getComponent<CameraComponent>().viewHeight = static_cast<float>(windowManager.getWindowSize().height);
}
