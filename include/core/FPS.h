
#pragma once
#include <SDL2/SDL.h>
#include "Util/Console.h"
#include <cstdlib>
#include <bits/basic_string.h>
class FPS
{
public:
    FPS(short _maxFPS);
    void timeBeginningOfFrame();
    void timeEndOfFrame();
    int getElapsedMS();
    double getElapsed();
    void printFPS();
    void delay();
    double getLag();
    /**
     * @brief My max FPS
     *
     */
    short maxFPS;

private:
    /**
     * @brief speed in which 
     * 
     */
    static double MS_PER_UPDATE;
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
    /**
     * @brief Amount of time game time is behind real time
     * 
     */
    double lag;
};