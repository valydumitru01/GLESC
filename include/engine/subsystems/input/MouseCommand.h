/**************************************************************************************************
 * @file   MouseCommand.h
 * @author Valentin Dumitru
 * @date   2024-03-19
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>
#include "InputTypes.h"

namespace GLESC::Input {
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
