#include "core/GLESC.h"
#include "core/FPS.h"

int SDL_main() {
    GLESC glesc;
    //Console::success("GLESC initialized");
    FPS fps(FpsRates::Fps60);
    Console::init();
    
    glesc.initGame();
    //Console::success("Game initialized");
    int iterations = 0;
    int updates = 0;
    while (glesc.running) {
        fps.timeFrame();
        //Console::info("-----Processing Input " + std::to_string(iterations++) + "-----");
        glesc.processInput();
        while (fps.isLagged()) // Update executes in constant intervals
        {
        //    Console::info("-----Updating " + std::to_string(updates++) + "-----");
            glesc.update();
            fps.updateLag();
        }
        //Console::info("-----Rendering " + std::to_string(iterations) + "-----");
        //Render execute arbitrarily, depending on how much time update() takes
        glesc.render(fps.getTimeOfFrameAfterUpdate());
    }
    return 0;
}