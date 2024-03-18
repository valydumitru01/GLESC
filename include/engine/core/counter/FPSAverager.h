/**************************************************************************************************
 * @file   FPSAverage.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <deque>

#define AVERAGE_FPS_COUNT 30

class FPSAverager {
public:
    FPSAverager() = default;
    ~FPSAverager() = default;
    void addFrame(long unsigned int frameTime) {
        frames.push_back(frameTime);
        if (frames.size() > AVERAGE_FPS_COUNT) {
            frames.pop_front();
        }
    }
    [[nodiscard]] long unsigned int getAverage() const {
        float sum = 0;
        for (auto& frame : frames) {
            sum += frame;
        }
        return sum / frames.size();
    }
private:
    std::deque<float> frames;
}; // class FPSAverage
