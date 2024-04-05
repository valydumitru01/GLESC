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
unsigned long long  GLESC::Timer::getCurrentTime() {
    return SDL_GetPerformanceCounter();
}