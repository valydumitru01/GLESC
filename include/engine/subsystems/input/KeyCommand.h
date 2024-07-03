/**************************************************************************************************
 * @file   KeyCommand.h
 * @author Valentin Dumitru
 * @date   10/03/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>

namespace GLESC::Input {
    /**
     * @brief Key command that stores the action and executes it when needed.
     */
    class KeyCommand {
    public:
        using Action = std::function<void()>;

        KeyCommand() = default;

        KeyCommand(Action action);

        void execute();

    private:
        Action action = []() {
        };
    };
} // namespace GLESC::Input
