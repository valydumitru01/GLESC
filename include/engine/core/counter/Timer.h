/**************************************************************************************************
 * @file   Timer.h
 * @author Valentin Dumitru
 * @date   2024-04-04
 * @brief  Classes to encapsulate the logic of measuring real time.
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <SDL2/SDL_stdinc.h>

namespace GLESC {
    using TimeMillis = Uint32;
    using TimeSeconds = float;

    /**
     * @brief Class to encapsulate the logic of measuring real time.
     */
    class Timer {
    public:
        Timer() = default;
        /**
         * @brief Start the timer to zero.
         */
        void start();
        /**
         * @brief Get the current time in milliseconds relative to the start time
         * @return Time - the current time in milliseconds
         */
        TimeMillis getCurrentTime();

    private:
        TimeMillis startTime{};
    }; // class Timer
    /**
     * @brief Class to encapsulate the logic of measuring absolute time since the start of the program.
     */
    class AbsoluteTimer {
        /**
         * @brief Get the current time in milliseconds since the start of the program
         * @return Time
         */
        static TimeMillis getCurrentTime();
    };
} // namespace GLESC
