/**************************************************************************************************
 * @file   Timer.cpp
 * @author Valentin Dumitru
 * @date   2024-04-04
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
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