#include "engine/GLESC.h"

GLESC::GLESC() : running(true), windowManager(make_shared <WindowManager>("GLESC")),
                 renderer(make_shared <Renderer>(windowManager)), inputSystem(running) {
    
    cameraSystem.setRenderer(renderer);
    renderSystem.setRenderer(renderer);
    // Register all the components
    // Must be done before the systems are created
    // Because the systems need to know what components they are working with
    // TODO: Make this automatic
    inputSystem.init();
    physicsSystem.init();
    renderSystem.init();
    cameraSystem.init();

    
}


void GLESC::processInput() {
    inputSystem.update();
}

void GLESC::render(double const timeOfFrame) {
    
    cameraSystem.update();
    
    renderSystem.update(timeOfFrame);
}

void GLESC::update() {
    loop();
    physicsSystem.update();
}

void GLESC::createEntity(const string &name) {
    entities.emplace(std::piecewise_construct, std::forward_as_tuple(name), std::tuple <>());
}


Entity &GLESC::getEntity(const string &name) {
    return entities[name];
}

