#include "core/GLESC.h"

GLESC::GLESC() : running(true), windowManager(make_shared <WindowManager>("GLESC")),
                                          renderer(make_shared <Renderer>(windowManager)) {
    // Register all the components
    // Must be done before the systems are created
    // Because the systems need to know what components they are working with
    // TODO: Make this automatic
    cameraSystem.setRenderer(renderer);
    renderSystem.setRenderer(renderer);
    
    inputSystem.init();
    transformSystem.init();
    physicsSystem.init();
    renderSystem.init();
    cameraSystem.init();
    
}

GLESC::~GLESC() = default;


void GLESC::processInput() {
    inputSystem.update();
}

void GLESC::render(double const timeOfFrame) {
    
    cameraSystem.update();
    
    renderSystem.update(timeOfFrame);
}

void GLESC::update() {
    loop();
    transformSystem.update();
    physicsSystem.update();
}


