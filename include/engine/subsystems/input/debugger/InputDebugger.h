/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once
#include "engine/core/asserts/Asserts.h"
#include "engine/subsystems/input/InputKeys.h"

namespace GLESC{
template <typename keyEnum>
std::string keyToString(const keyEnum& key) {
    ASSERT(false, "Key not supported to be converted to string");
}
template<>
inline std::string keyToString<GLESC::KeyState> (const GLESC::KeyState& keyState) {
    switch (keyState) {
        case GLESC::KeyState::PRESSED:return "PRESSED";
        case GLESC::KeyState::RELEASED:return "RELEASED";
    }
}

/**
 * @brief Template specialization for GLESC::Key
 * @param enumToString
 * @return The string representation of the enum
 */
template<>
inline std::string keyToString<GLESC::Key>(const GLESC::Key& key) {
    switch (key) {
        case GLESC::Key::ESCAPE:return "ESCAPE";
        case GLESC::Key::SPACE:return "SPACE";
        case GLESC::Key::LEFT:return "LEFT";
        case GLESC::Key::RIGHT:return "RIGHT";
        case GLESC::Key::UP:return "UP";
        case GLESC::Key::DOWN:return "DOWN";
        case GLESC::Key::W:return "W";
        case GLESC::Key::A:return "A";
        case GLESC::Key::S:return "S";
        case GLESC::Key::D:return "D";
        case GLESC::Key::Q:return "Q";
        case GLESC::Key::E:return "E";
        case GLESC::Key::R:return "R";
        case GLESC::Key::F:return "F";
        case GLESC::Key::T:return "T";
        case GLESC::Key::G:return "G";
        case GLESC::Key::Y:return "Y";
        case GLESC::Key::H:return "H";
        case GLESC::Key::U:return "U";
        case GLESC::Key::J:return "J";
        case GLESC::Key::I:return "I";
        case GLESC::Key::K:return "K";
        case GLESC::Key::O:return "O";
        case GLESC::Key::L:return "L";
        case GLESC::Key::P:return "P";
        case GLESC::Key::Z:return "Z";
        case GLESC::Key::X:return "X";
        case GLESC::Key::C:return "C";
        case GLESC::Key::V:return "V";
        case GLESC::Key::B:return "B";
        case GLESC::Key::N:return "N";
        case GLESC::Key::M:return "M";
        case GLESC::Key::ONE:return "ONE";
        case GLESC::Key::TWO:return "TWO";
        case GLESC::Key::THREE:return "THREE";
        case GLESC::Key::FOUR:return "FOUR";
        case GLESC::Key::FIVE:return "FIVE";
        case GLESC::Key::SIX:return "SIX";
        case GLESC::Key::SEVEN:return "SEVEN";
        case GLESC::Key::EIGHT:return "EIGHT";
        case GLESC::Key::NINE:return "NINE";
        case GLESC::Key::ZERO:return "ZERO";
        case GLESC::Key::F1:return "F1";
        case GLESC::Key::F2:return "F2";
        case GLESC::Key::F3:return "F3";
        case GLESC::Key::F4:return "F4";
        case GLESC::Key::F5:return "F5";
        case GLESC::Key::F6:return "F6";
        case GLESC::Key::F7:return "F7";
        case GLESC::Key::F8:return "F8";
        case GLESC::Key::F9:return "F9";
        case GLESC::Key::F10:return "F10";
        case GLESC::Key::F11:return "F11";
        case GLESC::Key::F12:return "F12";
        case GLESC::Key::F13:return "F13";
        case GLESC::Key::F14:return "F14";
        case GLESC::Key::F15:return "F15";
        case GLESC::Key::F16:return "F16";
        case GLESC::Key::F17:return "F17";
        case GLESC::Key::F18:return "F18";
        case GLESC::Key::F19:return "F19";
        case GLESC::Key::F20:return "F20";
        case GLESC::Key::F21:return "F21";
        case GLESC::Key::F22:return "F22";
        case GLESC::Key::F23:return "F23";
        case GLESC::Key::F24:return "F24";
        case GLESC::Key::NUMLOCK:return "NUMLOCK";
        case GLESC::Key::CAPSLOCK:return "CAPSLOCK";
        case GLESC::Key::SCROLLLOCK:return "SCROLLLOCK";
        case GLESC::Key::RIGHT_SHIFT:return "RIGHT_SHIFT";
        case GLESC::Key::LEFT_SHIFT:return "LEFT_SHIFT";
        case GLESC::Key::RIGHT_CTRL:return "RIGHT_CTRL";
        case GLESC::Key::LEFT_CTRL:return "LEFT_CTRL";
        case GLESC::Key::RIGHT_ALT:return "RIGHT_ALT";
        case GLESC::Key::LEFT_ALT:return "LEFT_ALT";
        case GLESC::Key::RIGHT_GUI:return "RIGHT_GUI";
        case GLESC::Key::LEFT_GUI:return "LEFT_GUI";
        case GLESC::Key::LEFT_BRACKET:return "LEFT_BRACKET";
        case GLESC::Key::RIGHT_BRACKET:return "RIGHT_BRACKET";
        case GLESC::Key::SEMICOLON:return "SEMICOLON";
        case GLESC::Key::COMMA:return "COMMA";
        case GLESC::Key::PERIOD:return "PERIOD";
        case GLESC::Key::QUOTE:return "QUOTE";
        case GLESC::Key::SLASH:return "SLASH";
        case GLESC::Key::BACKSLASH:return "BACKSLASH";
        case GLESC::Key::BACKQUOTE:return "BACKQUOTE";
        case GLESC::Key::MINUS:return "MINUS";
        case GLESC::Key::EQUALS:return "EQUALS";
        case GLESC::Key::RETURN:return "RETURN";
        case GLESC::Key::TAB:return "TAB";
        case GLESC::Key::BACKSPACE:return "BACKSPACE";
        case GLESC::Key::INSERT:return "INSERT";
        case GLESC::Key::DELETE:return "DELETE";
        case GLESC::Key::PAGE_UP:return "PAGE_UP";
        case GLESC::Key::PAGE_DOWN:return "PAGE_DOWN";
        case GLESC::Key::HOME:return "HOME";
        case GLESC::Key::END:return "END";
        case GLESC::Key::PRINT_SCREEN:return "PRINT_SCREEN";
        case GLESC::Key::PAUSE:return "PAUSE";
        case GLESC::Key::CLEAR:return "CLEAR";
        case GLESC::Key::APPLICATION:return "APPLICATION";
        case GLESC::Key::POWER:return "POWER";
        case GLESC::Key::MOUSE_BUTTON_LEFT:return "MOUSE_BUTTON_LEFT";
        case GLESC::Key::MOUSE_BUTTON_MIDDLE: return "MOUSE_BUTTON_MIDDLE";
        case GLESC::Key::MOUSE_BUTTON_RIGHT:return "MOUSE_BUTTON_RIGHT";
    }
}
} // namespace GLESC