/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/GLESC.h"
#include "engine/ecs/backend/ECS.h"

using namespace GLESC;

Engine::Engine() :
        windowManager(),
        renderer(windowManager),
        inputSystem(inputManager, ecs),
        physicsSystem(physicsManager, ecs),
        renderSystem(renderer, ecs),
        cameraSystem(renderer, ecs) {}


void Engine::processInput() {
    inputSystem.update();
}

void Engine::render(double const timeOfFrame) {
    renderer.clear();
    cameraSystem.update();
    
    renderSystem.update(timeOfFrame);
    renderer.swapBuffers();
}

void Engine::update() {
    loop();
    physicsSystem.update();
}

