#include "engine/core/counter/Counter.h"
#include "engine/GLESC.h"
#include <SDL2/SDL_main.h>

int main() {
    Engine glesc;
    Counter counter(FpsRates::Fps60);
    
    glesc.initGame();
    int iterations = 0;
    int updates = 0;
    while (glesc.running) {
        counter.timeFrame();
        glesc.processInput();
        while (counter.isLagged()) // Update executes in constant intervals
        {
            glesc.update();
            counter.updateLag();
        }
        //Render execute arbitrarily, depending on how much time update() takes
        glesc.render(counter.getTimeOfFrameAfterUpdate());
    }
    return 0;
}