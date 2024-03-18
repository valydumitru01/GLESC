/******************************************************************************
 * @file   main.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/counter/FPSManager.h"
#include "engine/GLESC.h"
#include <SDL2/SDL_main.h>

int main(int argc, char* argv[]) {
#ifndef NDEBUG
    Logger::get().warning("DEBUG MODE IS ON");
#endif
    FPSManager counter(Fps90);
    GLESC::Engine glesc(counter);
    glesc.initGame();
    while (glesc.running) {
        counter.startFrame();

        glesc.processInput();
        while (counter.isUpdateLagged()) // Update executes in constant intervals no matter how much time it takes
        {
            glesc.update();
            counter.refreshUpdateLag();
        }
        //Render execute arbitrarily, depending on how much time update() takes
        glesc.render(counter.getTimeOfFrameAfterUpdate());
    }
    return 0;
}
