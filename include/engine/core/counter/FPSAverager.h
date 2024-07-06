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
    void addFrame(float frameTime) {
        frames.push_back(frameTime);
        if (frames.size() > AVERAGE_FPS_COUNT) {
            frames.pop_front();
        }
    }
    [[nodiscard]] float getAverage() const {
        if (frames.empty()) return 0;
        float sum = 0;
        for (auto& frame : frames) {
            sum += frame;
        }
        return sum / static_cast<float>(frames.size());
    }
private:
    std::deque<float> frames;
}; // class FPSAverage
