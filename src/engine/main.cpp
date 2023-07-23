#include "engine/GLESC.h"
#include "engine/core/counter/Counter.h"

int SDL_main() {
    GLESC glesc;
    //Logger::get().success("GLESC initialized");
    Counter counter(FpsRates::Fps60);
    
    glesc.initGame();
    //Logger::get().success("Game initialized");
    int iterations = 0;
    int updates = 0;
    while (glesc.running) {
        counter.timeFrame();
        //Logger::get().info("-----Processing Input " + std::to_string(iterations++) + "-----");
        glesc.processInput();
        while (counter.isLagged()) // Update executes in constant intervals
        {
        //    Logger::get().info("-----Updating " + std::to_string(updates++) + "-----");
            glesc.update();
            counter.updateLag();
        }
        //Logger::get().info("-----Rendering " + std::to_string(iterations) + "-----");
        //Render execute arbitrarily, depending on how much time update() takes
        glesc.render(counter.getTimeOfFrameAfterUpdate());
    }
    return 0;
}