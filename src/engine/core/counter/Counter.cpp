/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/counter/Counter.h"


Counter::Counter(FpsRates maxFPS) : msPerUpdate(50), fpsMs(MILLIS_IN_A_SECOND / static_cast<double> (maxFPS)),
                            current(0), previous(0), elapsed(0), lag(0) {
}

void Counter::timeFrame() {
    current = SDL_GetTicks(); // Update the current frame-time
    elapsed = current - previous;
    previous = current; // Updates the previous frame-time
    lag += elapsed;     // Accumulate the elapsed time inside lag
    
    delay();
}

bool Counter::isLagged() const {
    return lag >= msPerUpdate;
}

void Counter::updateLag() {
    lag -= msPerUpdate;
}

void Counter::delay() const {
    auto dif = static_cast<int32_t>(fpsMs - elapsed);
    if (dif > 0)
        SDL_Delay(dif); // Cap the Counter, wait until we get to minimum frame time
}

double Counter::getTimeOfFrameAfterUpdate() const {
    return static_cast<double>( lag) / static_cast<double>( msPerUpdate);
}