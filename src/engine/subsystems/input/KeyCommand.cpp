/**************************************************************************************************
 * @file   Command.cpp
 * @author Valentin Dumitru
 * @date   10/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/input/KeyCommand.h"

KeyCommand::KeyCommand(Action action) : action(std::move(action)) {}

void KeyCommand::execute() {
    if (action) {
        action();
    }
}