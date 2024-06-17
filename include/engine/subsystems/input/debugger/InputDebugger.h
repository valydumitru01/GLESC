/******************************************************************************
 * @file   InputDebugger.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once
#include <string>

#include "engine/core/asserts/Asserts.h"
#include "engine/subsystems/input/InputKeys.h"

namespace GLESC::Input {
    inline std::string keyActionToString(const KeyAction& keyState) {
        switch (keyState) {
        case KeyAction::ONCE_PRESSED: return "ONCE_PRESSED";
        case KeyAction::ONCE_RELEASED: return "ONCE_RELEASED";
        case KeyAction::ONGOING_PRESSED: return "ONGOING_PRESSED";
        case KeyAction::ONGOING_RELEASED: return "ONGOING_RELEASED";
        default: D_ASSERT_TRUE(false, "KeyState not supported to be converted to string");
        }
        return "UNKNOWN_KEY_STATE";
    }

    inline std::string keyToString(const Key& key) {
        switch (key) {
        case Key::ESCAPE: return "ESCAPE";
        case Key::SPACE: return "SPACE";
        case Key::LEFT: return "LEFT";
        case Key::RIGHT: return "RIGHT";
        case Key::UP: return "UP";
        case Key::DOWN: return "DOWN";
        case Key::W: return "W";
        case Key::A: return "A";
        case Key::S: return "S";
        case Key::D: return "D";
        case Key::Q: return "Q";
        case Key::E: return "E";
        case Key::R: return "R";
        case Key::F: return "F";
        case Key::T: return "T";
        case Key::G: return "G";
        case Key::Y: return "y";
        case Key::H: return "H";
        case Key::U: return "U";
        case Key::J: return "J";
        case Key::I: return "I";
        case Key::K: return "K";
        case Key::O: return "O";
        case Key::L: return "L";
        case Key::P: return "P";
        case Key::Z: return "Z";
        case Key::X: return "x";
        case Key::C: return "C";
        case Key::V: return "V";
        case Key::B: return "B";
        case Key::N: return "N";
        case Key::M: return "M";
        case Key::ONE: return "1";
        case Key::TWO: return "2";
        case Key::THREE: return "3";
        case Key::FOUR: return "4";
        case Key::FIVE: return "5";
        case Key::SIX: return "6";
        case Key::SEVEN: return "7";
        case Key::EIGHT: return "8";
        case Key::NINE: return "9";
        case Key::ZERO: return "0";
        case Key::F1: return "F1";
        case Key::F2: return "F2";
        case Key::F3: return "F3";
        case Key::F4: return "F4";
        case Key::F5: return "F5";
        case Key::F6: return "F6";
        case Key::F7: return "F7";
        case Key::F8: return "F8";
        case Key::F9: return "F9";
        case Key::F10: return "F10";
        case Key::F11: return "F11";
        case Key::F12: return "F12";
        case Key::F13: return "F13";
        case Key::F14: return "F14";
        case Key::F15: return "F15";
        case Key::F16: return "F16";
        case Key::F17: return "F17";
        case Key::F18: return "F18";
        case Key::F19: return "F19";
        case Key::F20: return "F20";
        case Key::F21: return "F21";
        case Key::F22: return "F22";
        case Key::F23: return "F23";
        case Key::F24: return "F24";
        case Key::NUMLOCK: return "NUMLOCK";
        case Key::CAPSLOCK: return "CAPSLOCK";
        case Key::SCROLLLOCK: return "SCROLLLOCK";
        case Key::RIGHT_SHIFT: return "RIGHT_SHIFT";
        case Key::LEFT_SHIFT: return "LEFT_SHIFT";
        case Key::RIGHT_CTRL: return "RIGHT_CTRL";
        case Key::LEFT_CTRL: return "LEFT_CTRL";
        case Key::RIGHT_ALT: return "RIGHT_ALT";
        case Key::LEFT_ALT: return "LEFT_ALT";
        case Key::RIGHT_GUI: return "RIGHT_GUI";
        case Key::LEFT_GUI: return "LEFT_GUI";
        case Key::LEFT_BRACKET: return "LEFT_BRACKET";
        case Key::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case Key::SEMICOLON: return "SEMICOLON";
        case Key::COMMA: return "COMMA";
        case Key::PERIOD: return "PERIOD";
        case Key::QUOTE: return "QUOTE";
        case Key::SLASH: return "SLASH";
        case Key::BACKSLASH: return "BACKSLASH";
        case Key::BACKQUOTE: return "BACKQUOTE";
        case Key::MINUS: return "MINUS";
        case Key::EQUALS: return "EQUALS";
        case Key::RETURN: return "RETURN";
        case Key::TAB: return "TAB";
        case Key::BACKSPACE: return "BACKSPACE";
        case Key::INSERT: return "INSERT";
        case Key::PAGE_UP: return "PAGE_UP";
        case Key::PAGE_DOWN: return "PAGE_DOWN";
        case Key::HOME: return "HOME";
        case Key::END: return "END";
        case Key::PRINT_SCREEN: return "PRINT_SCREEN";
        case Key::PAUSE: return "PAUSE";
        case Key::CLEAR: return "CLEAR";
        case Key::APPLICATION: return "APPLICATION";
        case Key::POWER: return "POWER";
        case Key::MOUSE_BUTTON_LEFT: return "MOUSE_LEFT";
        case Key::MOUSE_BUTTON_MIDDLE: return "MOUSE_MIDDLE";
        case Key::MOUSE_BUTTON_RIGHT: return "MOUSE_RIGHT";
        default: return "UNKNOWN_KEY";
        }
    }
} // namespace GLESC
