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
    Command moveForward = Command([&] {
        camera.getComponent<TransformComponent>().transform.position += camera.getComponent<TransformComponent>().
                                                                               transform.forward();
    });
    Command moveBackward = Command([&] {
        camera.getComponent<TransformComponent>().transform.position -= camera.getComponent<TransformComponent>().
                                                                               transform.forward();
    });
    Command moveLeft = Command([&] {
        camera.getComponent<TransformComponent>().transform.position -= camera.getComponent<TransformComponent>().
                                                                               transform.right();
    });
    Command moveRight = Command([&] {
        camera.getComponent<TransformComponent>().transform.position += camera.getComponent<TransformComponent>().
                                                                               transform.right();
    });

    camera.getComponent<InputComponent>().subscribedKeys = {
        {Key::W, moveForward},
    };
    // TODO: The issue lies here, we cannot copy faces because faces store a reference to the vertices
    player.getComponent<RenderComponent>().mesh = MeshFactory::cube(RGBA(1, 0, 0, 1));
    ColorMesh cube = MeshFactory::cube(RGBA(1, 0, 0, 1));
    ColorMesh mesh = player.getComponent<RenderComponent>().mesh;
    player.getComponent<PhysicsComponent>().velocity.z(1);
}


void GLESC::Engine::loop() {
    GLESC::ECS::Entity player = getEntity("player");
    GLESC::ECS::Entity camera = getEntity("camera");

    camera.getComponent<CameraComponent>().viewWidth = static_cast<float>(windowManager.getWindowSize().width);
    camera.getComponent<CameraComponent>().viewHeight = static_cast<float>(windowManager.getWindowSize().height);

    if (inputManager.isKeyPressed(Key::LEFT_SHIFT)) {
        windowManager.setMouseRelative(false);
    }
    else {
        windowManager.setMouseRelative(true);
    }

    if (inputManager.isKeyPressed(Key::W)) {
        player.getComponent<PhysicsComponent>().velocity.z(1);
    }
    else if (inputManager.isKeyPressed(Key::S)) {
        player.getComponent<PhysicsComponent>().velocity.z(-1);
    }
    else {
        player.getComponent<PhysicsComponent>().velocity.z(0);
    }

    if (inputManager.isKeyPressed(Key::A)) {
        player.getComponent<TransformComponent>().transform.rotation += Vec3F(0, 0.1, 0);
    }
    else if (inputManager.isKeyPressed(Key::D)) {
        player.getComponent<TransformComponent>().transform.rotation -= Vec3F(0, 0.1, 0);
    }
}
