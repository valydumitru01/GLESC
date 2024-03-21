/**************************************************************************************************
 * @file   KeyCommand.h
 * @author Valentin Dumitru
 * @date   10/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>

class KeyCommand {
public:
    using Action = std::function<void()>;

    KeyCommand() = default;

    KeyCommand(Action action);

    void execute();

private:
    Action action = []() {};
};
