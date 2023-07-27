#include "engine/GLESC.h"

using namespace GLESC;

Engine::Engine() : running(true), graphicsInterface(), windowManager({graphicsInterface}), inputManager(),
                   renderer({graphicsInterface}), physicsManager(), inputSystem(inputManager) {
    
}


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

void Engine::createEntity(const std::string &name) {
    entities.emplace(std::piecewise_construct, std::forward_as_tuple(name), std::tuple <>());
}


Entity &Engine::getEntity(const std::string &name) {
    return entities[name];
}
