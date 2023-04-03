#include "core/FPS.h"


FPS::FPS(FpsRates maxFPS) : msPerUpdate(50), fpsMs(MILLIS_IN_A_SECOND / static_cast<double> (maxFPS)),
                            current(0), previous(0), elapsed(0), lag(0) {
}

void FPS::timeFrame() {
    current = SDL_GetPerformanceCounter(); // Update the current frame-time
    elapsed = current - previous;
    previous = current; // Updates the previous frame-time
    lag += elapsed;     // Accumulate the elapsed time inside lag
    
    delay();
}

bool FPS::isLagged() const {
    return lag >= msPerUpdate;
}

void FPS::updateLag() {
    lag -= msPerUpdate;
}

void FPS::delay() const {
    std::uint32_t dif = fpsMs - elapsed;
    if (dif > 0)
        SDL_Delay(dif); // Cap the FPS, wait until we get to minimum frame time
}

double FPS::getTimeOfFrameAfterUpdate() const {
    return static_cast<double>( lag) / static_cast<double>( msPerUpdate);
}