#include "core/FPS.h"


FPS::FPS(FpsRates maxFPS) : msPerUpdate(50), fpsMs(MILLIS_IN_A_SECOND / static_cast<double> (maxFPS)),
                            current(0), previous(0), elapsed(0), lag(0) {
}

void FPS::timeFrame() {
    current = SDL_GetTicks(); // Update the current frame-time
    elapsed = current - previous;
    previous = current; // Updates the previous frame-time
    lag += elapsed;     // Accumulate the elapsed time inside lag
    
    delay();
}

bool FPS::isLagged() const {
    //Console::info("Lag:" + std::to_string(lag));
    return lag >= msPerUpdate;
}

void FPS::updateLag() {
    //Console::info("Updating lag: " + std::to_string(lag) + " - " + std::to_string(msPerUpdate) + " = " +
    //              std::to_string(lag - msPerUpdate) + " ms");
    lag -= msPerUpdate;
}

void FPS::delay() const {
    auto dif = static_cast<int32_t>(fpsMs - elapsed);
    //Console::info("Delaying by:" + std::to_string(dif));
    if (dif > 0)
        SDL_Delay(dif); // Cap the FPS, wait until we get to minimum frame time
}

double FPS::getTimeOfFrameAfterUpdate() const {
    return static_cast<double>( lag) / static_cast<double>( msPerUpdate);
}