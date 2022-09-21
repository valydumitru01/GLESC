#include "FPS.h"

FPS::FPS(short _maxFPS)
{
    elapsed = 0;                      // Initialised at 0, first frame is immobilized
    maxFPS = _maxFPS;                 // Initialize max fps at 60
    FPS_MS = 1000.0 / (double)maxFPS; // The max milliseconds of the frame is the division between 1000 (ms in a second) and the max fps
}
void FPS::timeBeginningOfFrame()
{
    start = SDL_GetPerformanceCounter(); // Time of the beginning of the loop
}
void FPS::timeEndOfFrame()
{
    if (FPS_MS - elapsed > 0)
        SDL_Delay(FPS_MS - elapsed);   // Cap the FPS, wait until we get to minimum frame time
    end = SDL_GetPerformanceCounter(); // Time of the end of the loop

    elapsed = (end - start) / (double)SDL_GetPerformanceFrequency(); // Calculate elapsed: time of the end of the iteration - time of the start of the iteration
}
void FPS::printFPS(){
    std::string fps_str("Current FPS: ");
    Console::info(fps_str + std::to_string(1.0f / elapsed));
}
double FPS::getElapsed(){
    return elapsed;
}