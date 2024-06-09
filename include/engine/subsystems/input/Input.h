/**************************************************************************************************
 * @file   Input.h
 * @author Valentin Dumitru
 * @date   15/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <sstream>
#include <unordered_map>

#include "KeyCommand.h"
#include "MouseCommand.h"
#include "engine/subsystems/input/debugger/InputDebugger.h"

namespace GLESC::Input {
    class Input {
    public:
        [[nodiscard]] std::string toString() const {
            std::ostringstream ss;
            ss << "Subscribed keys";
            for (const auto& [key, command] : subscribedKeys) {
                ss << keyToString(key.key) << " ";
            }
            return ss.str();
        }

        std::vector<EntityStatsManager::Value> getDebuggingValues() {
            std::vector<EntityStatsManager::Value> values;
            EntityStatsManager::Value subscribedKeysValue;
            subscribedKeysValue.name = "Subscribed keys";
            subscribedKeysValue.isString = true;
            std::stringstream ss;
            for (const auto& [key, command] : subscribedKeys) {
                ss << keyToString(key.key) << "\n";
            }
            subscribedKeysValue.stringData = ss.str();
            values.push_back(subscribedKeysValue);
            return values;
        }

        const std::unordered_map<KeyInput, KeyCommand>& getSubscribedKeys() const {
            return subscribedKeys;
        }

        std::unordered_map<KeyInput, KeyCommand>& getSubscribedKeys() {
            return subscribedKeys;
        }

        const MouseCommand& getMouseCommand() const {
            return mouseCommand;
        }

        MouseCommand& getMouseCommand() {
            return mouseCommand;
        }

        void subscribeKey(KeyInput key, KeyCommand command) {
            subscribedKeys[key] = command;
        }

        void unsubscribeKey(KeyInput key) {
            subscribedKeys.erase(key);
        }

        void setMouseCommand(MouseCommand command) {
            mouseCommand = command;
        }

    private:
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
    }; // class Input
} // namespace GLESC::Input
