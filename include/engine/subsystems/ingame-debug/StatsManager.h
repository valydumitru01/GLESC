/**************************************************************************************************
 * @file   StatsManager.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/asserts/Asserts.h"
#include <functional>
#include <map>
#include <string>

#include "engine/core/debugger/Stringer.h"

namespace GLESC {
    /**
     * @brief Class to manage the stats of the game.
     * @details This class allows registering stat sources such as FPS, memory usage, etc.
     */
    class StatsManager {
    public:
        // Register a stat source with any return type
        template <typename Func>
        static void registerStatSource(const std::string& name, Func callback) {
            S_ASSERT_TRUE(std::is_invocable_v<Func>, "Callback must be invocable");

            sources[name] = [callback]() -> std::string {
                return Stringer::toString(callback());
            };
        }

        static std::unordered_map<std::string, std::string> getStats();

    private:
        static std::map<std::string, std::function<std::string()>> sources;
    };
}