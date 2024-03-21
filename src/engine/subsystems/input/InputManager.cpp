/******************************************************************************
 * @file   InputManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/input/InputManager.h"

#include <SDL2/SDL.h>
#include <unordered_map>


InputManager::InputManager(HUDManager &hudManagerm): hudManager(hudManager),
    keyMap(), mousePosition({0, 0}) {
}


void InputManager::update(bool &running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        hudManager.processInput(event);
        handleEvent(event);
    }
}

void InputManager::handleEvent(const SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            handleKeyEvent(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION:
            handleMouseEvent(event);
            break;
        default:
            break;
    }
}

void InputManager::handleKeyEvent(const SDL_Event &event) {
    auto keycode = static_cast<GLESC::Key>(event.key.keysym.sym);
    bool pressed = event.type == SDL_KEYDOWN;
    updateKeyState(keycode, pressed);
}

void InputManager::handleMouseEvent(const SDL_Event &event) {
    if (event.type == SDL_MOUSEMOTION) {
        if (SDL_GetRelativeMouseMode() == SDL_TRUE){
            mousePosition.x() = event.motion.xrel;
            mousePosition.y() = event.motion.yrel;
        } else {
            mousePosition.x() = event.motion.x;
            mousePosition.y() = event.motion.y;
        }
    } else {
        auto mouseButton = static_cast<GLESC::Key>(event.button.button);
        bool pressed = event.type == SDL_MOUSEBUTTONDOWN;
        updateKeyState(mouseButton, pressed);
    }
}

bool InputManager::checkKeyAction(const KeyInput &keyInput) {
    auto it = keyMap.find(keyInput.key);
    if (it != keyMap.end()) {
        auto &state = it->second;
        switch (keyInput.action) {
            case GLESC::KeyAction::ONGOING_PRESSED:
                return state.pressed;
            case GLESC::KeyAction::ONCE_PRESSED:
                if (state.justPressed) {
                    state.justPressed = false; // Reset the flag
                    return true;
                }
                break;
            case GLESC::KeyAction::ONCE_RELEASED:
                if (state.justReleased) {
                    state.justReleased = false; // Reset the flag
                    return true;
                }
                break;
        }
    }
    return false;
}
void InputManager::setMouseRelative(bool enabled) {
    if (SDL_SetRelativeMouseMode(static_cast<SDL_bool>(enabled)) != 0) {

        std::string action = enabled ? "enable" : "disable";
        throw EngineException(
                "Unable to " + action + " mouse relative mode: "+ std::string(SDL_GetError())
                );
    }
    // Reset the mouse position, looks like it's not done by SDL
    mousePosition.x() = 0;
    mousePosition.y() = 0;
}

bool InputManager::isMouseRelative() {
    return SDL_GetRelativeMouseMode() == SDL_TRUE;
}

void InputManager::updateKeyState(GLESC::Key key, bool pressed) {
    auto &keyState = keyMap[key];
    if (pressed) {
        if (!keyState.pressed) {
            keyState.justPressed = true;
        } else {
            keyState.justPressed = false;
        }
        keyState.pressed = true;
    } else {
        if (keyState.pressed) {
            keyState.justReleased = true;
        } else {
            keyState.justReleased = false;
        }
        keyState.pressed = false;
        keyState.justPressed = false;
    }
}
