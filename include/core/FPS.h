
#pragma once
#include <SDL2/SDL.h>
#include "Util/Console.h"
#include <cstdlib>
#include <bits/basic_string.h>
#define MILIS_IN_A_SECOND 1000.0f
enum FPS_rates
{
    fps_30=30,
    fps_45=45,
    fps_60=60,
    fps_75=75,
    fps_90=90
};

class FPS
{
public:
    FPS(FPS_rates const maxFPS);
    /**
     * @brief measures the frame, remembering the old frame.
     * 
     */
    void timeFrame();
    /**
     * @brief Get the elapsed milliseconds 
     * 
     * @return int 
     */
    int getElapsedMS() const;
    /**
     * @brief Get the elapsed seconds
     * 
     * @return double 
     */
    double getElapsed() const;

    void printFPS();
    /**
     * @brief Get the amount of frame it has passed since the beginning. 
     * The value is normalized between 0.0 and 1.0. 
     * It is used to interpolate rendering to avoid stutter.
     * 
     * @return double between 0.0 - 1.0
     */
    double getTimeOfFrameAfterUpdate();
    /**
     * @brief Is the game time behind real time?
     * 
     * @return true - if accumulated lag is greater than a constant
     * @return false - if accumulated lag is not greater than a constant
     */
    bool isLagged();
    /**
     * @brief Reduce the accumulated lag by a constant.
     *  Must be called each time update is called.
     * 
     */
    void updateLag();
    /**
     * @brief My max FPS
     *
     */
    short maxFPS;

private:
    void delay();
    /**
     * @brief constant speed (in ms) in which our game updates
     * 
     */
    const double ms_per_update;
    /**
     * @brief The max time can elapse between frames
     *
     */
    double fps_ms;
    /**
     * @brief Time recorded at the beginning of the loop iteration
     *
     */
    Uint64 current;
    /**
     * @brief Time recorded at the end of the loop iteration
     *
     */
    Uint64 previous;
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