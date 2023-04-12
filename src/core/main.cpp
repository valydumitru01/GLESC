#include "core/GLESC.h"
#include "core/FPS.h"

int SDL_main() {
    GLESC glesc;
    Console::success("GLESC initialized");
    glesc.init();
    Console::success("Game initialized");
    FPS fps(FpsRates::Fps60);
    Console::init();
    while (glesc.running) {
        fps.timeFrame();
        
        glesc.processInput();
        while (fps.isLagged()) // Update executes in constant intervals
        {
            glesc.update();
            fps.updateLag();
        }
        
        //Render execute arbitrarily, depending on how much time update() takes
        glesc.render(fps.getTimeOfFrameAfterUpdate());
    }
    return 0;
}