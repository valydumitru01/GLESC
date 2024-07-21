/******************************************************************************
 * @file   FPSManager.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Class that encapsulates the logic of managing the frames and the loop.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "FpsTypes.h"
#include "engine/core/counter/FPSAverager.h"
#include "SDL2/SDL.h"

namespace GLESC {
    enum FpsRates {
        Fps30 [[maybe_unused]] = 30,
        Fps45 [[maybe_unused]] = 45,
        Fps60 [[maybe_unused]] = 60,
        Fps75 [[maybe_unused]] = 75,
        Fps90 [[maybe_unused]] = 90,
        Fps120 [[maybe_unused]] = 120,
        Fps144 [[maybe_unused]] = 144,
        Fps240 [[maybe_unused]] = 240,
        Fps480 [[maybe_unused]] = 480,
        Fps960 [[maybe_unused]] = 960,
        Unlimitted [[maybe_unused]] = 0
    };

    class FPSManager {
    public:
        explicit FPSManager(FpsRates renderFPS, FpsRates updateFPS = Fps60);

        /**
         * @brief measures the frame, remembering the old frame.
         *
         */
        void startFrame();

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
        [[nodiscard]] bool isUpdateLagged() const;

        /**
         * @brief Reduce the accumulated lag by a constant.
         *  Must be called each time update is called.
         *
         */
        void refreshUpdateLag();

        [[nodiscard]] bool hasSpiralOfDeathBeenReached() const;

        /**
         * @brief Get the constant speed in which our game updates
         *
         * @return Uint32
         */
        [[nodiscard]] UIntMillis getUpdateTimeMillis() const;

        /**
         * @brief Get the time it took to render the frame
         *
         * @return Uint32
         */
        [[nodiscard]] UIntMillis getCurrentRenderTimeMillis() const;

        /**
         * @brief Get the average time it took to render the frame
         *
         * @return Uint32
         */
        [[nodiscard]] FPSFloatingPoint getAverageRenderTimeMillis() const;

        /**
         * @brief Get the average fps of the last 60 frames
         *
         * @return float
         */
        [[nodiscard]] FPSFloatingPoint getRenderFPS() const;

        /**
         * @brief Get the fps of the update
         *
         * @return float
         */
        [[nodiscard]] FPSFloatingPoint getUpdateFPS() const;

        [[nodiscard]] UIntMillis getLag() const { return lag; }

    private:
        void delay() const;
        static constexpr UIntMillis msInASecond{1000};
        /**
         * @brief The max time (milliseconds) can elapse between frames
         *
         */
        const UIntMillis msPerRender;
        /**
         * @brief constant speed (in ms) in which our game updates
         *
         */
        const UIntMillis msPerUpdate;

        /**
         * @brief Time recorded at the beginning of the loop iteration
         *
         */
        UIntMillis current{};
        /**
         * @brief Time recorded at the end of the loop iteration
         *
         */
        UIntMillis previous{};
        /**
         * @brief The actual time it elapses
         *
         */
        UIntMillis elapsed{};
        /**
         * @brief Amount of time game time is behind real time
         *
         */
        UIntMillis lag{};

        /**
         * @brief Threshold to check if the game is stuck in a loop-
         * If the amount of updates is greater than this value, the game is stuck in a loop
         */
        static constexpr int spiralOfDeathLimit = 500;
        /**
         * @brief Counter to check if the game is stuck in a loop
         */
        int updateCounter{};

        static constexpr int averageFpsListSize = 60;
        /**
         * @brief List of the last 60 frames to calculate the average fps
         */
        UIntMillis fpsList[averageFpsListSize]{};
        /**
         * @brief Index of the fpsList
         */
        int fpsListIndex{0};

        /**
         * @brief The averager to calculate the average fps
         */
        FPSAverager renderFpsAverager;
    };
}
