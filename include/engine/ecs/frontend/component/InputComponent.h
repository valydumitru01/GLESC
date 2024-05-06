/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <unordered_map>

#include "../../backend/component/IComponent.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/input/InputTypes.h"
#include "engine/subsystems/input/MouseCommand.h"
#include "engine/subsystems/input/debugger/InputDebugger.h"

namespace GLESC::ECS {
    struct InputComponent : IComponent {
        /**
         * @brief Vector of pairs, subscribed keys and bool,true if they are pressed
         * @details This vector is used to store the keys that are subscribed to the input system,
         * this it saves memory as each only stores the keys that are subscribed to it.
         */
        std::unordered_map<Input::KeyInput, Input::KeyCommand> subscribedKeys;
        /**
         * @brief A command that is executed when the mouse is moved
         */
        Input::MouseCommand mouseCommand;

        std::string toString() const override {
            std::ostringstream ss;
            ss << "Subscribed keys";
            for (const auto& [key, command] : subscribedKeys) {
                ss << Input::keyToString(key.key) << " ";
            }
            return ss.str();
        }

        std::string getName() const override {
            return "InputComponent";
        }

        void setDebuggingValues() override {
            EntityStatsManager::Value subscribedKeysValue;
            subscribedKeysValue.name = "Subscribed keys";
            subscribedKeysValue.isString = true;
            std::stringstream ss;
            for (const auto& [key, command] : subscribedKeys) {
                ss << Input::keyToString(key.key) << " ";
            }
            subscribedKeysValue.stringData = ss.str();
            values.push_back(subscribedKeysValue);
        }
    };
} // namespace GLESC::ECS
