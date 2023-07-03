#include "core/GLESC.h"
#include "core/FPS.h"

int SDL_main() {
    GLESC glesc;
    //Logger::get().success("GLESC initialized");
    FPS fps(FpsRates::Fps60);
    Logger::get().init();
    
    glesc.initGame();
    //Logger::get().success("Game initialized");
    int iterations = 0;
    int updates = 0;
    while (glesc.running) {
        fps.timeFrame();
        //Logger::get().info("-----Processing Input " + std::to_string(iterations++) + "-----");
        glesc.processInput();
        while (fps.isLagged()) // Update executes in constant intervals
        {
        //    Logger::get().info("-----Updating " + std::to_string(updates++) + "-----");
            glesc.update();
            fps.updateLag();
        }
        //Logger::get().info("-----Rendering " + std::to_string(iterations) + "-----");
        //Render execute arbitrarily, depending on how much time update() takes
        glesc.render(fps.getTimeOfFrameAfterUpdate());
    }
    return 0;
}