
#include "engine/core/counter/FPSManager.h"

FPSManager::FPSManager(FpsRates renderFPS, FpsRates updateFPS)
    : msPerRender(renderFPS == Unlimitted ? 0 : msInASecond / static_cast<Millis>(renderFPS)),
      msPerUpdate(msInASecond / static_cast<Millis>(updateFPS)) {
}

void FPSManager::startFrame() {
    current = static_cast<Millis>(SDL_GetTicks()); // Update the current frame-time
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

FPSManager::Millis FPSManager::getUpdateTimeMillis() const {
    return msPerUpdate;
}

bool FPSManager::hasSpiralOfDeathBeenReached() const {
    return updateCounter > spiralOfDeathLimit;
}


FPSManager::Millis FPSManager::getCurrentRenderTimeMillis() const {
    return elapsed;
}

FPSManager::Millis FPSManager::getAverageRenderTimeMillis() const {
    return fpsAverager.getAverage();
}

float FPSManager::getUpdateFPS() const {
    return msInASecond / getUpdateTimeMillis();
}

float FPSManager::getRenderFPS() const {
    return msInASecond / getAverageRenderTimeMillis();
}


void FPSManager::delay() const {
    if (msPerRender > 0) {
        double dif = msPerRender - elapsed;
        if (dif > 0)
            SDL_Delay(dif); // Cap the Counter, wait until we get to minimum frame time
    }
}

double FPSManager::getTimeOfFrameAfterUpdate() const {
    return static_cast<double>(lag) / static_cast<double>(msPerUpdate);
}
