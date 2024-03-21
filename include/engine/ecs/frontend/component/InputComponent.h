/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <unordered_map>

#include "IComponent.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/input/InputTypes.h"
#include "engine/subsystems/input/InputKeys.h"
#include "engine/subsystems/input/MouseCommand.h"
#include "engine/subsystems/input/debugger/InputDebugger.h"

struct InputComponent : public IComponent {
    /**
     * @brief Vector of pairs, subscribed keys and bool,true if they are pressed
     * @details This vector is used to store the keys that are subscribed to the input system,
     * this it saves memory as each only stores the keys that are subscribed to it.
     */
    std::unordered_map<KeyInput, KeyCommand> subscribedKeys;
    /**
     * @brief A command that is executed when the mouse is moved
     */
    MouseCommand mouseCommand;

    std::string toString() override {
        std::ostringstream ss;

        ss << "Subscribed keys";

        return ss.str();
    }
};
