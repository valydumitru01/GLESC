/******************************************************************************
 * @file   FPSManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/counter/FPSManager.h"

#include "engine/core/math/Math.h"


FPSManager::FPSManager(FpsRates maxFPS)
    : fpsMs(maxFPS == FpsUnlimited ? 0 : msInASecond / static_cast<Uint32>(maxFPS)),
      msPerUpdate(msInASecond / 60) {
}

void FPSManager::startFrame() {
    current = SDL_GetTicks(); // Update the current frame-time
    elapsed = current - previous;
    previous = current; // Updates the previous frame-time
    lag += elapsed; // Accumulate the elapsed time inside lag
    fpsAverager.addFrame(elapsed);
    delay();
}

bool FPSManager::isUpdateLagged() const {
    return lag >= msPerUpdate;
}

void FPSManager::refreshUpdateLag() {
    lag -= msPerUpdate;
    updateCounter++;
}

Uint32 FPSManager::getUpdateTimeMillis() const {
    return msPerUpdate;
}

bool FPSManager::hasSpiralOfDeathBeenReached() const{
    return updateCounter > spiralOfDeathLimit;
}


Uint32 FPSManager::getCurrentRenderTimeMillis() const {
    return elapsed;
}

Uint32 FPSManager::getAverageRenderTimeMillis() const {
    return fpsAverager.getAverage();
}

float FPSManager::getUpdateFPS() const {
    return 1000.0f / static_cast<float>(getUpdateTimeMillis());
}

float FPSManager::getRenderFPS() const {
    return 1000.0f / static_cast<float>(getAverageRenderTimeMillis());
}


void FPSManager::delay() const {
    if (fpsMs > 0) {
        auto dif = static_cast<int32_t>(fpsMs - elapsed);
        if (dif > 0)
            SDL_Delay(dif); // Cap the Counter, wait until we get to minimum frame time
    }
}

double FPSManager::getTimeOfFrameAfterUpdate() const {
    return static_cast<double>(lag) / static_cast<double>(msPerUpdate);
}
