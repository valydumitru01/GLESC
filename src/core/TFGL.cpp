#include "core/TFGL.h"

TFGL::TFGL() : fps(FPS_rates::fps_60), running(true) {


}

TFGL::~TFGL() {
}

void TFGL::loop() {
    Console::init();

    while (running) {
        fps.timeFrame();

        processInput();
        while (fps.isLagged()) // Update executes in constant intervals
        {
            update();
            fps.updateLag();
        }
        render(fps.getTimeOfFrameAfterUpdate()); //Render execute arbitrarily, depending on how much time update() takes
    }
}

void TFGL::processInput() {

}

void TFGL::render(double const timeOfFrame) {


}

void TFGL::update() {
    Entity entity;

}


