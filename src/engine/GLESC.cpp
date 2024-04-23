/******************************************************************************
 * @file   GLESC.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/GLESC.h"
#include "engine/ecs/backend/ECS.h"
// In-Game debug
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/systems/LightSystem.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/input/debugger/InputDebugger.h"

#include "engine/ecs/frontend/system/systems/PhysicsSystem.h"
#include "engine/ecs/frontend/system/systems/RenderSystem.h"
#include "engine/ecs/frontend/system/systems/CameraSystem.h"
#include "engine/ecs/frontend/system/systems/InputSystem.h"
#include "engine/ecs/frontend/system/systems/TransformSystem.h"
#include "engine/ecs/frontend/system/systems/DebugInfoSystem.h"
using namespace GLESC;

Engine::Engine(FPSManager& fpsManager) :
    fpsManager(fpsManager),
    windowManager(),
    renderer(windowManager),
    hudManager(windowManager.getWindow()),
    inputManager(hudManager, windowManager),
    engineHuds(hudManager, renderer, textureFactory),

    ecs(),
    entityFactory(ecs),
    systems(createSystems()),


    engineCamera(createEngineCamera()),

    game(ecs, physicsManager, inputManager, windowManager, entityFactory, engineCamera) {
    this->registerStats();
    game.init();
}


void Engine::processInput() {
    Logger::get().importantInfoBlue("Engine processInput started");
    inputManager.update(running);


    Logger::get().importantInfoBlue("Engine processInput finished");
}

void Engine::render(double const timeOfFrame) {
    Logger::get().importantInfoPurple("Engine render started");
    renderer.clear();

    renderer.renderMeshes(timeOfFrame);
    hudManager.render();

    renderer.swapBuffers();
    Logger::get().importantInfoPurple("Engine render finished");
}

void Engine::update() {
    Logger::get().importantInfoWhite("Engine update started");

    game.update();
    hudManager.update();

    for (auto& system : systems) {
        system->update();
    }

    Console::log("Debug log message");
    Console::warn("Debug warning message");
    Console::error("Debug error message");

    Logger::get().importantInfoWhite("Engine update finished");
}

std::vector<std::unique_ptr<ECS::System>> Engine::createSystems() {
    std::vector<std::unique_ptr<ECS::System>> systems;
    systems.push_back(std::make_unique<ECS::InputSystem>(inputManager, ecs));
    systems.push_back(std::make_unique<ECS::PhysicsSystem>(physicsManager, ecs));
    systems.push_back(std::make_unique<ECS::RenderSystem>(renderer, ecs));
    systems.push_back(std::make_unique<ECS::CameraSystem>(renderer, windowManager, ecs));
    systems.push_back(std::make_unique<ECS::TransformSystem>(ecs));
    systems.push_back(std::make_unique<ECS::LightSystem>(ecs, renderer));
    systems.push_back(std::make_unique<ECS::DebugInfoSystem>(ecs, renderer));
    return systems;
}

#define CAMERA_SPEED 0.3f
#define CAMERA_X_ROTATION_LIMIT 45.0f

ECS::Entity Engine::createEngineCamera() {
    using namespace GLESC::ECS;
    Entity camera = entityFactory.createEntity("camera");

    camera.addComponent(CameraComponent())
          .addComponent(TransformComponent())
          .addComponent(InputComponent());


    camera.getComponent<CameraComponent>().perspective.farPlane = 1000.0f;
    camera.getComponent<CameraComponent>().perspective.nearPlane = 0.1f;
    camera.getComponent<CameraComponent>().sensitivity = 1.5;
    camera.getComponent<CameraComponent>().perspective.fovDegrees = 60.0f;
    camera.getComponent<CameraComponent>().perspective.viewWidth = static_cast<float>(windowManager.getSize().width);
    camera.getComponent<CameraComponent>().perspective.viewHeight = static_cast<float>(windowManager.getSize().height);
    // IMPORTANT! Camera movement needs to be done with inverse directions, because it looks at the
    // opposite direction of the forward vector
    Input::KeyCommand moveForward = Input::KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.addPosition(
            -cameraEntity.getComponent<TransformComponent>().transform.forward() * CAMERA_SPEED);
    });

    Input::KeyCommand moveBackward = Input::KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.addPosition(
            cameraEntity.getComponent<TransformComponent>().transform.forward() * CAMERA_SPEED);
    });

    Input::KeyCommand moveLeft = Input::KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.addPosition(
            cameraEntity.getComponent<TransformComponent>().transform.right() * CAMERA_SPEED);
    });

    Input::KeyCommand moveRight = Input::KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.addPosition(
            -cameraEntity.getComponent<TransformComponent>().transform.right() * CAMERA_SPEED);
    });

    Input::KeyCommand moveUp = Input::KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.addPosition(
            Transform::Transform::worldUp * CAMERA_SPEED);
    });

    Input::KeyCommand moveDown = Input::KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.addPosition(
            -Transform::Transform::worldUp * CAMERA_SPEED);
    });

    Input::MouseCommand rotate = Input::MouseCommand([&](const MousePosition& deltaMouse) {
        if (!inputManager.isMouseRelative()) return;
        Entity cameraEntity = entityFactory.getEntity("camera");

        auto& transformComp = cameraEntity.getComponent<TransformComponent>().transform;
        auto& cameraComp = cameraEntity.getComponent<CameraComponent>();

        // Adjust the target rotation based on mouse input
        // Only rotate if rotation is between -90 and 90 degrees
        float mouseAdditionX = static_cast<float>(deltaMouse.getY()) * cameraComp.sensitivity;
        float nextMouseX = transformComp.getRotation().getX() + mouseAdditionX;
        if (nextMouseX < CAMERA_X_ROTATION_LIMIT &&
            nextMouseX > -CAMERA_X_ROTATION_LIMIT)
            transformComp.addRotation(Transform::Axis::X, mouseAdditionX);
        transformComp.addRotation(Transform::Axis::Y,
                                  static_cast<float>(deltaMouse.getX()) * cameraComp.sensitivity);

        // Ensure we avoid gimbal lock, restrict the X rotation to 90 degrees
    });

    Input::KeyCommand mouseRelativeMove = Input::KeyCommand([&] {
        inputManager.setMouseRelative(!inputManager.isMouseRelative());
    });

    camera.getComponent<InputComponent>().subscribedKeys = {
        {{Input::Key::W, Input::KeyAction::ONGOING_PRESSED}, moveForward},
        {{Input::Key::S, Input::KeyAction::ONGOING_PRESSED}, moveBackward},
        {{Input::Key::A, Input::KeyAction::ONGOING_PRESSED}, moveLeft},
        {{Input::Key::D, Input::KeyAction::ONGOING_PRESSED}, moveRight},
        {{Input::Key::SPACE, Input::KeyAction::ONGOING_PRESSED}, moveUp},
        {{Input::Key::LEFT_SHIFT, Input::KeyAction::ONGOING_PRESSED}, moveDown},
        {{Input::Key::LEFT_CTRL, Input::KeyAction::ONCE_PRESSED}, mouseRelativeMove}
    };
    camera.getComponent<InputComponent>().mouseCommand = rotate;

    return camera;
}


void Engine::registerStats() const {
    StatsManager::registerStatSource("Update FPS", [&]() -> float {
        return fpsManager.getUpdateFPS();
    });
    StatsManager::registerStatSource("Render FPS", [&]() -> float {
        return fpsManager.getRenderFPS();
    });

    StatsManager::registerStatSource("Update frame time", [&]() -> Uint32 {
        return fpsManager.getUpdateTimeMillis();
    });
    StatsManager::registerStatSource("Render frame time", [&]() -> Uint32 {
        return fpsManager.getAverageRenderTimeMillis();
    });
    StatsManager::registerStatSource("Mesh Render Counter", [&]() -> std::string {
        return Stringer::toString(renderer.getMeshRenderCount());
    });
    StatsManager::registerStatSource("Pressed Keys: ", [&]() -> std::string {
        std::string keys = "[";
        for (const auto& key : inputManager.getPressedKeys()) {
            keys += keyToString(key) + ", ";
        }
        // Remove last comma and space
        if (!inputManager.getPressedKeys().empty()) {
            keys.pop_back();
            keys.pop_back();
        }

        keys += "]";
        return keys;
    });

    StatsManager::registerStatSource("Mouse Position: ", [&]() -> std::string {
        return inputManager.getMousePosition().toString();
    });


    StatsManager::registerStatSource("Projection Matrix: ", [&]() -> std::string {
        return renderer.getProjection().toString();
    });

    StatsManager::registerStatSource("View Matrix: ", [&]() -> std::string {
        return renderer.getView().toString();
    });
}
