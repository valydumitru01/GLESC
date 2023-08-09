/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "SDL2/SDL.h"

#define MILLIS_IN_A_SECOND 1000.0f
enum FpsRates {
    Fps30 [[maybe_unused]] = 30,
    Fps45 [[maybe_unused]] = 45,
    Fps60 [[maybe_unused]] = 60,
    Fps75 [[maybe_unused]] = 75,
    Fps90 [[maybe_unused]] = 90
};

class Counter {
public:
    explicit Counter(FpsRates maxFPS);
    
    /**
     * @brief measures the frame, remembering the old frame.
     *
     */
    void timeFrame();
    
    /**
     * @brief Get the amount of frame it has passed since the beginning.
     * The value is normalized between 0.0 and 1.0.
     * It is used to interpolate rendering to avoid stutter.
     *
     * @return double between 0.0 - 1.0
     */
    [[nodiscard]] double getTimeOfFrameAfterUpdate() const;
    
    /**
     * @brief Is the game time behind real time?
     *
     * @return true - if accumulated lag is greater than a constant
     * @return false - if accumulated lag is not greater than a constant
     */
    [[nodiscard]] bool isLagged() const;
    
    /**
     * @brief Reduce the accumulated lag by a constant.
     *  Must be called each time update is called.
     *
     */
    void updateLag();


private:
    void delay() const;
    
    /**
     * @brief constant speed (in ms) in which our game updates
     *
     */
    const Uint32 msPerUpdate;
    /**
     * @brief The max time (milliseconds) can elapse between frames
     *
     */
    Uint32 fpsMs;
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
    Uint32 elapsed;
    /**
     * @brief Amount of time game time is behind real time
     *
     */
    Uint32 lag;
};