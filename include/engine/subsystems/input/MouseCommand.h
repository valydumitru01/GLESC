/**************************************************************************************************
 * @file   MouseCommand.h
 * @author Valentin Dumitru
 * @date   2024-03-19
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>
#include "InputTypes.h"

namespace GLESC::Input {
    /**
     * @brief Mouse command executes the command every action with the position as a parameter.
     */
    class MouseCommand {
    public:
        using Action = std::function<void(const MousePosition&)>;

        MouseCommand() = default;

        MouseCommand(Action action);

        void execute(const MousePosition& position);

    private:
        // Default: does nothing
        Action action = [](const MousePosition& position) {};
    };
} // namespace GLESC::Input
