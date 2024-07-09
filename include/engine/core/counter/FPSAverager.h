/**************************************************************************************************
 * @file   FPSAverager.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Class to encapsulate the logic of averaging the FPS
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <deque>

#include "FpsTypes.h"

#define AVERAGE_FPS_COUNT 30

class FPSAverager {
public:
    /**
     * @brief Default constructor.
     */
    FPSAverager() = default;
    /**
     * @brief Default destructor.
     */
    ~FPSAverager() = default;
    /**
     * @brief Adds a frame to the FPS averager.
     * @param frameTime - the time it took to render the frame.
     */
    void addFrame(FPSFloatingPoint frameTime) {
        frames.push_back(frameTime);
        if (frames.size() > AVERAGE_FPS_COUNT) {
            frames.pop_front();
        }
    }
    /**
     * @brief Get the average FPS.
     * @return the average FPS.
     */
    [[nodiscard]] FPSFloatingPoint getAverage() const {
        if (frames.empty()) return 0;
        FPSFloatingPoint sum = 0;
        for (auto& frame : frames) {
            sum += frame;
        }
        return sum / static_cast<FPSFloatingPoint>(frames.size());
    }
private:
    std::deque<FPSFloatingPoint> frames;
}; // class FPSAverage
