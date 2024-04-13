/**************************************************************************************************
 * @file   Counter.h
 * @author Valentin Dumitru
 * @date   2024-04-10
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

class Counter {
public:
    /**
     * @brief Default constructor.
     */
    Counter() = default;
    void startFrame() {
        count = 0;
    }
    void addToCounter(float value) {
        count += value;
    }
    [[nodiscard]] float getCount() const {
        return count;
    }

private:
    float count{0};
}; // class Counter