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
#include "engine/ecs/frontend/component/FogComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/SunComponent.h"
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
#include "engine/ecs/frontend/system/systems/FogSystem.h"
#include "engine/ecs/frontend/system/systems/SunSystem.h"
#include "engine/scene/Scene.h"
using namespace GLESC;

Engine::Engine(FPSManager& fpsManager) :
    fpsManager(fpsManager),
    windowManager(),
    renderer(windowManager),
    hudManager(windowManager.getWindow()),
    inputManager(hudManager, windowManager),
#ifndef NDEBUG_GLESC
    engineHuds(hudManager, renderer, textureFactory),
#endif
    ecs(),
    entityFactory(ecs),
    updateSystems(createUpdateSystems()),
    renderSystems(createRenderSystems()),
    engineCamera(entityFactory, inputManager, windowManager),
    sceneManager(entityFactory, windowManager),
    sceneContainer(windowManager, entityFactory, inputManager, sceneManager, engineCamera),
    game(windowManager, entityFactory, sceneManager, sceneContainer) {
    engineCamera.setupCamera();
    this->registerStats();
    createEngineEntities();
    game.init();
}


void Engine::processInput() {
    Logger::get().importantInfoBlue("Engine processInput started");
    inputManager.update(running);
    Logger::get().importantInfoBlue("Engine processInput finished");
}

void Engine::render(double const timeOfFrame) {
    Logger::get().importantInfoPurple("Engine render started");
    //renderer.removeMarkedMeshes();
    for (auto& system : renderSystems) {
        system->update();
    }
    renderer.start(timeOfFrame);
    hudManager.update();
    renderer.render(timeOfFrame);
    hudManager.render();
    renderer.swapBuffers();
    Logger::get().importantInfoPurple("Engine render finished");
}

void Engine::update() {
    Logger::get().importantInfoWhite("Engine update started");

    game.update();
    for (ECS::EntityID id : ecs.getEntitiesToBeDestroyed()) {
        EntityListManager::entityRemoved(ecs.getEntityName(id));
        if (ecs.hasComponent<ECS::RenderComponent>(id) && ecs.hasComponent<ECS::TransformComponent>(id)) {
            renderer.remove(ecs.getComponent<ECS::RenderComponent>(id).getMesh(),
                            ecs.getComponent<ECS::TransformComponent>(id).transform);
        }
    }
    ecs.destroyEntities();

    //#pragma omp parallel for \
    //    shared(renderer, windowManager, ecs, updateSystems) \
    //    schedule(static, 1)
    for (auto& system : updateSystems) {
        system->update();
    }
    for (const auto& [name,id] : ecs.getAllEntities()) {
        if (ecs.isEntityInstanced(name))
            if ((engineCamera.getEntity().getComponent<ECS::TransformComponent>().transform.getPosition().distance(
                ecs.getComponent<ECS::TransformComponent>(id).transform.getPosition()) > 1000.0f)) {
                ecs.markForDestruction(id);
            }
        if (ecs.hasComponent<ECS::PhysicsComponent>(id)) {
            auto& physics = ecs.getComponent<ECS::PhysicsComponent>(id);
            if (physics.collider.isDestroyed()) {
                ecs.markForDestruction(id);
            }
        }
    }
    Console::log("Debug log message");
    Console::warn("Debug warning message");
    Console::error("Debug error message");

    Logger::get().importantInfoWhite("Engine update finished");
}

std::vector<std::unique_ptr<ECS::System>> Engine::createRenderSystems() {
    std::vector<std::unique_ptr<ECS::System>> systems;
    systems.push_back(std::make_unique<ECS::RenderSystem>(renderer, ecs));
    return systems;
}

std::vector<std::unique_ptr<ECS::System>> Engine::createUpdateSystems() {
    std::vector<std::unique_ptr<ECS::System>> systems;
    systems.push_back(std::make_unique<ECS::PhysicsSystem>(physicsManager, ecs));
    systems.push_back(std::make_unique<ECS::InputSystem>(inputManager, ecs));
    systems.push_back(std::make_unique<ECS::CameraSystem>(renderer, windowManager, ecs));
    systems.push_back(std::make_unique<ECS::TransformSystem>(ecs));
    systems.push_back(std::make_unique<ECS::LightSystem>(ecs, renderer));
    systems.push_back(std::make_unique<ECS::DebugInfoSystem>(ecs, renderer));
    systems.push_back(std::make_unique<ECS::SunSystem>(ecs, renderer));
    systems.push_back(std::make_unique<ECS::FogSystem>(renderer, ecs));
    return systems;
}

void Engine::createEngineEntities() {
    ECS::Entity sun = entityFactory.createEntity("sun", {EntityType::Engine})
                                   .addComponent<ECS::TransformComponent>()
                                   .addComponent<ECS::SunComponent>();
    sun.getComponent<ECS::TransformComponent>().transform.setPosition(
        Transform::Position(0, 10, 0));
    sun.getComponent<ECS::SunComponent>().sun.setDirection({-0.4, -1, -0.4});
    sun.getComponent<ECS::SunComponent>().sun.setIntensity(0.7);
    sun.getComponent<ECS::SunComponent>().sun.setColor({255, 255, 150});
    sun.getComponent<ECS::SunComponent>().globalAmbienLight.setIntensity(0.3);
    sun.getComponent<ECS::SunComponent>().globalAmbienLight.setColor({255, 255, 150});


    ECS::Entity fog = entityFactory.createEntity("fog", {EntityType::Engine})
                                   .addComponent<ECS::TransformComponent>()
                                   .addComponent<ECS::FogComponent>();
    fog.getComponent<ECS::TransformComponent>().transform.setPosition({1, 0, 0});
    fog.getComponent<ECS::FogComponent>().fog.setDensity(1);
    fog.getComponent<ECS::FogComponent>().fog.setColor({255, 255, 255});
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
