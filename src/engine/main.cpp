
#include "engine/core/counter/FPSManager.h"
#include "engine/GLESC.h"
#include <SDL2/SDL_main.h>

int main(int argc, char* argv[]) {
#ifndef NDEBUG_GLESC
    Logger::get().warning("DEBUG MODE IS ON");
#endif
    GLESC::FPSManager fps(GLESC::Unlimitted);
    GLESC::Engine glesc(fps);

    while (glesc.running) {
        fps.startFrame();

        glesc.processInput(fps.getTimeOfFrameAfterUpdate());

        while (fps.isUpdateLagged()) // Update executes in constant intervals no matter how much time it takes
        {
            glesc.update();
            fps.refreshUpdateLag();

            // Break if we get in spiral of death
            if(fps.hasSpiralOfDeathBeenReached()) break;
        }
        //Render executes arbitrarily
        glesc.render(fps.getTimeOfFrameAfterUpdate());
    }
    return 0;
}
