#pragma once
#include <SDL2/SDL.h>
#include "Util/Console.h"
#include <cstdlib>
#include <bits/basic_string.h>
class FPS {
public:
    FPS(short _maxFPS);
    void timeBeginningOfFrame();
    void timeEndOfFrame();
    int getElapsedMS();
    double getElapsed();
    void printFPS();
    void delay();
    /**
     * @brief My max FPS
     * 
     */
    short maxFPS;



private:
    /**
     * @brief The max time can elapse between frames
     * 
     */
    double FPS_MS;
    /**
     * @brief Time recorded at the beginning of the loop iteration
     * 
     */
    Uint64 start;
    /**
     * @brief Time recorded at the end of the loop iteration
     * 
     */
    Uint64 end;
    /**
     * @brief The actual time it elapses
     * 
     */
    double elapsed;
};