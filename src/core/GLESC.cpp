#include "core/GLESC.h"

GLESC::GLESC() : running(true), windowManager(make_shared <WindowManager>("GLESC")),
                 renderSystem(RenderSystem(windowManager)) {
    
}

GLESC::~GLESC() = default;


void GLESC::processInput() {
    inputSystem.update();
}

void GLESC::render(double const timeOfFrame) {
    
    cameraSystem.update();
    
    renderSystem.setView(cameraSystem.getView());
    renderSystem.setProjection(cameraSystem.getProjection());
    
    renderSystem.update(timeOfFrame);
}

void GLESC::update() {
    loop();
    transformSystem.update();
    physicsSystem.update();
}


