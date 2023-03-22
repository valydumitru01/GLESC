#include "core/GLESC.h"

GLESC::GLESC() : running(true), windowTitle("GLESC"), window(windowTitle), renderSystem(RenderSystem(window)) {

}

GLESC::~GLESC() = default;


void GLESC::processInput() {
	inputSystem.update();
}

void GLESC::render(double const timeOfFrame) {

	cameraSystem.update();

	renderSystem.setMvp(cameraSystem.getMvp());
	renderSystem.update(timeOfFrame);
}

void GLESC::update() {
	loop();
	transformSystem.update();
	physicsSystem.update();
}


