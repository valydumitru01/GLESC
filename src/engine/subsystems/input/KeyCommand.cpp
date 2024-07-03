/**************************************************************************************************
 * @file   KeyCommand.cpp
 * @author Valentin Dumitru
 * @date   10/03/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/input/KeyCommand.h"
using namespace GLESC::Input;

KeyCommand::KeyCommand(Action action) : action(std::move(action)) {}

void KeyCommand::execute() {
    if (action) {
        action();
    }
}