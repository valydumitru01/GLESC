/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/counter/Counter.h"
#include "engine/GLESC.h"
#include <SDL2/SDL_main.h>

int main(int argc, char* argv[]) {
    #ifdef DEBUG
    Logger::get().warning("DEBUG MODE IS ON");
    #endif
    GLESC::Engine glesc;
    Counter counter(FpsRates::Fps60);
    
    glesc.initGame();
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