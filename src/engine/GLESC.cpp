/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/GLESC.h"
#include "engine/ecs/backend/Coordinator.h"

using namespace GLESC;

Engine::Engine() :
        running(true),
        graphicInterface(),
        windowManager(graphicInterface),
        inputManager(),
        renderer(windowManager, graphicInterface),
        physicsManager(),
        inputSystem(inputManager),
        physicsSystem(physicsManager),
        renderSystem(renderer),
        cameraSystem(renderer) {}


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

