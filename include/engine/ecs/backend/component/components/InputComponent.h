/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <unordered_map>

#include "engine/ecs/backend/component/Component.h"
#include "engine/subsystems/input/InputTypes.h"
#include "engine/subsystems/input/InputKeys.h"
#include "engine/core/debugger/Debugger.h"

struct InputComponent : public Component {
    /**
     * @brief Vector of pairs, subscribed keys and bool,true if they are pressed
     * @details This vector is used to store the keys that are subscribed to the input system,
     * this it saves memory as each only stores the keys that are subscribed to it.
     */
    std::unordered_map<GLESC::Key, bool> subscribedKeys;
    /**
     * @brief The mouse position is always stored and updated, no need for subscription
     * @details This is the mouse position, it is always updated and stored, no need for subscription.
     * This is because the position is not a lot of data and it is almost always used.
     */
    MousePosition mousePosition;
    
    [[nodiscard]] std::string toString() const override {
        std::string subscribedKeysString;
        for (auto &[key, value] : subscribedKeys) {
            subscribedKeysString += enumToString(key)
                    + std::string(" - pressed:")
                    + std::to_string(value)
                    + std::string(", ");
        }
        return "InputComponent:"
               + std::string("\n\tsubscribedKeys: ")
               + subscribedKeysString
               + std::string("\n\tMousePosition: ")
               + std::to_string(mousePosition.x)
               + std::string(", ")
               + std::to_string(mousePosition.y);
    }
};

