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
namespace GLESC {
    class Timer {
    public:
        Timer() = delete;
        static unsigned long long  getCurrentTime();

    protected:

    private:
    }; // class Timer
} // namespace GLESC
