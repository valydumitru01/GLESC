/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/GLESC.h"
#include "engine/ecs/backend/ECS.h"

using namespace GLESC;

Engine::Engine() :
        windowManager(graphicInterface),
        renderer(windowManager, graphicInterface),
        inputSystem(inputManager, ecs),
        physicsSystem(physicsManager, ecs),
        renderSystem(renderer, ecs),
        cameraSystem(renderer, ecs) {}


void Engine::processInput() {
    inputSystem.update();
}

void Engine::render(double const timeOfFrame) {
    renderer.start();
    cameraSystem.update();
    
    renderSystem.update(timeOfFrame);
    renderer.end();
}

void Engine::update() {
    loop();
    physicsSystem.update();
}

