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
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/input/debugger/InputDebugger.h"
using namespace GLESC;

Engine::Engine(FPSManager &fpsManager) :
    fpsManager(fpsManager),
    windowManager(),
    renderer(windowManager),
    hudManager(windowManager.getWindow()),
    inputManager(hudManager),
    engineHuds(hudManager),

    ecs(),
    entityFactory(ecs),
    debugInfoSystem(ecs, renderer),
    inputSystem(inputManager, ecs),
    physicsSystem(physicsManager, ecs),
    renderSystem(renderer, ecs),
    cameraSystem(renderer, windowManager, ecs),
    transformSystem(ecs),
    engineCamera(entityFactory.createEntity("camera")),
    game(ecs, physicsManager, inputManager, windowManager, entityFactory) {
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

    inputSystem.update();
    cameraSystem.update();
    physicsSystem.update();
    renderSystem.update();
    transformSystem.update();
    debugInfoSystem.update();


    Console::log("Debug log message");
    Console::warn("Debug warning message");
    Console::error("Debug error message");

    Logger::get().importantInfoWhite("Engine update finished");
}

ECS::Entity Engine::createCameraEntity() {
    using namespace GLESC::ECS;
    Entity camera = entityFactory.createEntity("camera");
    KeyCommand moveForward = KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position +=
                cameraEntity.getComponent<TransformComponent>().transform.forward();
    });

    KeyCommand moveBackward = KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position -=
                cameraEntity.getComponent<TransformComponent>().transform.forward();
    });

    KeyCommand moveLeft = KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position -=
                cameraEntity.getComponent<TransformComponent>().transform.right();
    });

    KeyCommand moveRight = KeyCommand([&] {
        Entity cameraEntity = entityFactory.getEntity("camera");
        cameraEntity.getComponent<TransformComponent>().transform.position +=
                cameraEntity.getComponent<TransformComponent>().transform.right();
    });

    auto *targetRotationX = new float(0.0f);
    auto *targetRotationY = new float(0.0f);
    MouseCommand rotate = MouseCommand([&](const MousePosition &deltaMouse) {
        if (!inputManager.isMouseRelative()) return;
        Entity cameraEntity = entityFactory.getEntity("camera");

        if (Math::abs(deltaMouse.getX()) < 2 && Math::abs(deltaMouse.getY()) < 2) return;

        // Adjust the target rotation based on mouse input
        *targetRotationX = cameraEntity.getComponent<TransformComponent>().transform.rotation.x() +
                          static_cast<float>(deltaMouse.getY()) * sensitivity;
        *targetRotationY = cameraEntity.getComponent<TransformComponent>().transform.rotation.y() +
                          static_cast<float>(deltaMouse.getX()) * sensitivity;

        // Smoothly interpolate current rotation towards the target rotation
        cameraEntity.getComponent<TransformComponent>().transform.rotation.x() = Math::lerp(
            cameraEntity.getComponent<TransformComponent>().transform.rotation.x(),
            *targetRotationX, 0.1f); // 0.1f is an example smoothing factor

        cameraEntity.getComponent<TransformComponent>().transform.rotation.y() = Math::lerp(
            cameraEntity.getComponent<TransformComponent>().transform.rotation.y(),
            *targetRotationY, 0.1f);
    });
    KeyCommand mouseRelativeMove = KeyCommand([&] {
        inputManager.setMouseRelative(!inputManager.isMouseRelative());
    });

    camera.getComponent<InputComponent>().subscribedKeys = {
        {{Key::W, KeyAction::ONGOING_PRESSED}, moveForward},
        {{Key::S, KeyAction::ONGOING_PRESSED}, moveBackward},
        {{Key::A, KeyAction::ONGOING_PRESSED}, moveLeft},
        {{Key::D, KeyAction::ONGOING_PRESSED}, moveRight},
        {{Key::LEFT_SHIFT, KeyAction::ONCE_PRESSED}, mouseRelativeMove}
    };
    camera.getComponent<InputComponent>().mouseCommand = rotate;
}


void Engine::registerStats() const {
    StatsManager::registerStatSource("Update FPS", [&]() -> float {
        return fpsManager.getUpdateFPS();
    });
    StatsManager::registerStatSource("Update frame time", [&]() -> Uint32 {
        return fpsManager.getUpdateTimeMillis();
    });
    StatsManager::registerStatSource("Render FPS", [&]() -> float {
        return fpsManager.getRenderFPS();
    });
    StatsManager::registerStatSource("Render frame time", [&]() -> Uint32 {
        return fpsManager.getAverageRenderTimeMillis();
    });

    StatsManager::registerStatSource("Pressed Keys: ", [&]() -> std::string {
        std::string keys = "[";
        for (const auto &key : inputManager.getPressedKeys()) {
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

    StatsManager::registerStatSource("Fustum: ", [&]() -> std::string {
        std::stringstream ss;
        for (auto &plane : renderer.getFrustum().getPlanes()) {
            ss << plane.toString() << "\n";
        }
        return ss.str();
    });

    StatsManager::registerStatSource("Projection Matrix: ", [&]() -> std::string {
        return renderer.getProjection().toString();
    });

    StatsManager::registerStatSource("View Matrix: ", [&]() -> std::string {
        return renderer.getView().toString();
    });

    StatsManager::registerStatSource("All model matrices: ", [&]() -> std::string {
        std::string matrices;
        for (auto &entity : ecs.getAllEntities()) {
            matrices += "Entity: " + entity.left + "\n";
            if (ecs.hasComponent<TransformComponent>(entity.right)) {
                Transform transform = ecs.getComponent<TransformComponent>(entity.right).transform;
                Model model;
                model.makeModelMatrix(transform.position, transform.rotation, transform.scale);
                matrices += model.toString() + "\n";
            }
            matrices += "\n";
        }
        return matrices;
    });
}
