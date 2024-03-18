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
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
using namespace GLESC;

Engine::Engine(FPSManager& fpsManager) :
    fpsManager(fpsManager),
    windowManager(),
    renderer(windowManager),
    hudManager(windowManager.getWindow()),
    inputManager(hudManager),
    engineHuds(hudManager),

    ecs(),
    inputSystem(inputManager, ecs),
    physicsSystem(physicsManager, ecs),
    renderSystem(renderer, ecs),
    cameraSystem(renderer, ecs) {

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



}


void Engine::processInput() {
    Logger::get().importantInfoBlue("Engine processInput started");
    inputManager.update(running);
    inputSystem.update();



    Logger::get().importantInfoBlue("Engine processInput finished");
}

void Engine::render(double const timeOfFrame) {
    Logger::get().importantInfoPurple("Engine update started");
    renderer.clear();

    renderer.renderMeshes(timeOfFrame);
    hudManager.render();

    renderer.swapBuffers();
    Logger::get().importantInfoPurple("Engine update finished");
}

void Engine::update() {
    Logger::get().importantInfoWhite("Engine update started");

    loop();
    hudManager.update();
    cameraSystem.update();
    physicsSystem.update();
    renderSystem.update();


    Console::log("Debug log message");
    Console::warn("Debug warning message");
    Console::error("Debug error message");

    Logger::get().importantInfoWhite("Engine update finished");
}
