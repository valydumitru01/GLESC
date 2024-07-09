
#include "engine/core/counter/FPSManager.h"

FPSManager::FPSManager(FpsRates renderFPS, FpsRates updateFPS)
    : msPerRender(renderFPS == Unlimitted ? 0 : msInASecond / static_cast<UIntMillis>(renderFPS)),
      msPerUpdate(msInASecond / static_cast<UIntMillis>(updateFPS)) {
}

void FPSManager::startFrame() {
    current = static_cast<UIntMillis>(SDL_GetTicks()); // Update the current frame-time
    elapsed = current - previous;
    previous = current; // Updates the previous frame-time
    lag += elapsed; // Accumulate the elapsed time inside lag
    renderFpsAverager.addFrame(elapsed);
    delay();
}

bool FPSManager::isUpdateLagged() const {
    return lag >= msPerUpdate;
}

void FPSManager::refreshUpdateLag() {
    lag -= msPerUpdate;
    updateCounter++;
}

UIntMillis FPSManager::getUpdateTimeMillis() const {
    return msPerUpdate;
}

bool FPSManager::hasSpiralOfDeathBeenReached() const {
    return updateCounter > spiralOfDeathLimit;
}


UIntMillis FPSManager::getCurrentRenderTimeMillis() const {
    return elapsed;
}

FPSFloatingPoint FPSManager::getAverageRenderTimeMillis() const {
    return renderFpsAverager.getAverage();
}

FPSFloatingPoint FPSManager::getUpdateFPS() const {
    return static_cast<FPSFloatingPoint>(msInASecond / getUpdateTimeMillis());
}

FPSFloatingPoint FPSManager::getRenderFPS() const {
    return msInASecond / getAverageRenderTimeMillis();
}


void FPSManager::delay() const {
    if (msPerRender > 0) {
        UIntMillis dif = msPerRender - elapsed;
        if (dif > 0)
            SDL_Delay(dif); // Cap the Counter, wait until we get to minimum frame time
    }
}

double FPSManager::getTimeOfFrameAfterUpdate() const {
    return static_cast<double>(lag) / static_cast<double>(msPerUpdate);
}
