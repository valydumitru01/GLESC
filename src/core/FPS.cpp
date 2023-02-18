#include "core/FPS.h"


FPS::FPS(FPS_rates maxFPS) : elapsed(0),
                             maxFPS(maxFPS),
                             fps_ms(MILIS_IN_A_SECOND / (double)maxFPS),
                             lag(0),
                             previous(0),
                             current(0),
                             ms_per_update(50)
{
}

void FPS::timeFrame()
{
    current = SDL_GetPerformanceCounter(); // Update the current frametime
    elapsed = current - previous;
    previous = current; // Update the prevous frametime
    lag += elapsed;     // Accumulate the elapsed time inside lag

    delay();
}

bool FPS::isLagged()
{
    return lag >= ms_per_update;
}
void FPS::updateLag()
{
    lag -= ms_per_update;
}
void FPS::delay()
{
    double dif = fps_ms - elapsed;
    if (dif > 0)
        SDL_Delay(dif); // Cap the FPS, wait until we get to minimum frame time
}

void FPS::printFPS()
{
    std::string fps_str("Current FPS: ");
    Console::info(fps_str + std::to_string(1.0f / elapsed));
}

double FPS::getElapsed() const
{
    return elapsed;
}

double FPS::getTimeOfFrameAfterUpdate()
{
    return lag / ms_per_update;
}