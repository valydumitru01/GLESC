/**************************************************************************************************
 * @file   InputTypes.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once
#include <unordered_map>
#include "InputKeys.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/hash/Hasher.h"

using MousePosition = Vec2F;

namespace GLESC::Input {
    /**
     * @brief This is a struct that encapsulates the key and its action for subscribing to the input system.
     * @details The key stores the key and the action its action (pressed once, released, held, etc.)
     *
     */
    struct KeyInput {
        KeyInput() = default;

        bool operator==(const KeyInput& other) const {
            return key == other.key && action == other.action;
        }

        Key key;
        KeyAction action;
    };
} // namespace GLESC::Input

template <>
struct std::hash<GLESC::Input::KeyInput> {
    size_t operator()(const GLESC::Input::KeyInput& keyInput) const noexcept {
        size_t seed = 0;
        GLESC::Hasher::hashCombine(seed, static_cast<size_t>(keyInput.key));
        GLESC::Hasher::hashCombine(seed, static_cast<size_t>(keyInput.action));
        return seed;
    }
};

/**
 * @brief This is a helper struct that ensures that the key is pressed, released, or held.
 */
struct InputState {
    bool pressed = false;
    bool justPressed = false;
    bool justReleased = false;
};

using KeyMap = std::unordered_map<GLESC::Input::Key, InputState>;
