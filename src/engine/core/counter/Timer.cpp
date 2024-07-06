#include "engine/core/counter/Timer.h"
#include <SDL2/SDL.h>

void GLESC::Timer::start() {
    startTime = SDL_GetTicks();
}

GLESC::TimeMillis  GLESC::Timer::getCurrentTime() {
    return SDL_GetTicks() - startTime;
}

GLESC::TimeMillis GLESC::AbsoluteTimer::getCurrentTime() {
    return SDL_GetTicks();
}