/**************************************************************************************************
 * @file   Counter.h
 * @author Valentin Dumitru
 * @date   2024-04-10
 * @brief  Class to encapsulate the logic of counting.
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

    /**
     * @brief Starts counter from 0.
     */
    void startCounter() {
        count = 0;
    }

    /**
     * @brief Adds a value to the counter.
     * @param value - the value to be added to the counter.
     */
    void addToCounter(float value) {
        count += value;
    }
    /**
     * @brief Returns the current count.
     * @return the current count.
     */
    [[nodiscard]] float getCount() const {
        return count;
    }

private:
    /**
     * @brief The current count.
     */
    float count{0};
}; // class Counter