/**************************************************************************************************
 * @file   MouseCommand.cpp
 * @author Valentin Dumitru
 * @date   2024-03-19
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/input/MouseCommand.h"
using namespace GLESC::Input;
MouseCommand::MouseCommand(Action action) : action(std::move(action)) {}

void MouseCommand::execute(const MousePosition& position) {
    if (action) {
        action(position);
    }
}
