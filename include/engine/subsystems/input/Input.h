/**************************************************************************************************
 * @file   Input.h
 * @author Valentin Dumitru
 * @date   15/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <unordered_map>

#include "KeyCommand.h"
#include "MouseCommand.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::Input {
    /**
     * @brief Class that stores the input from the user
     * @details This is a entity component that stores all the input subscriptions to keys and the mouse movement.
     * @details The benefits of this class is that we can store directly the commands with their functions that will be
     * executed when the input condition is met.
     */
    class Input {
    public:
        [[nodiscard]] std::string toString() const;

#ifndef NDEBUG_GLESC
        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues();
#endif
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

        void subscribeKey(const KeyInput& key, const KeyCommand& command) {
            subscribedKeys[key] = command;
        }

        void unsubscribeKey(const KeyInput& key) {
            subscribedKeys.erase(key);
        }

        void setMouseCommand(const MouseCommand& command) {
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
