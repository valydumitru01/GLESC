/**************************************************************************************************
 * @file   Timer.h
 * @author Valentin Dumitru
 * @date   2024-04-04
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <SDL2/SDL_stdinc.h>

namespace GLESC {
    using Time = Uint32;

    class Timer {
    public:
        Timer() = default;
        /**
         * @brief Start the timer
         */
        void start();
        /**
         * @brief Get the current time in milliseconds relative to the start time
         * @return Time
         */
        Time getCurrentTime();

    protected:

    private:
        Time startTime{};
    }; // class Timer

    class AbsoluteTimer {
        /**
         * @brief Get the current time in milliseconds since the start of the program
         * @return Time
         */
        static Time getCurrentTime();
    };
} // namespace GLESC
