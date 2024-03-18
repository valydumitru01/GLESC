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


InputManager::InputManager(HUDManager& hudManager) : hudManager(hudManager), mousePosition({0, 0}) {}


void InputManager::update(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        hudManager.processInput(event);
        handleEvent(event);
    }
}

void InputManager::handleEvent(const SDL_Event& event) {
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

void InputManager::handleKeyEvent(const SDL_Event& event) {
    auto keycode = static_cast<GLESC::Key>(event.key.keysym.sym);
    bool pressed = event.type == SDL_KEYDOWN;
    keyMap[keycode] = pressed;
}

void InputManager::handleMouseEvent(const SDL_Event& event) {
    auto mouseButton = static_cast<GLESC::Key>(event.button.button);
    bool pressed = event.type == SDL_MOUSEBUTTONDOWN;
    keyMap[mouseButton] = pressed;
    mousePosition.x = event.motion.x;
    mousePosition.y = event.motion.y;
}

bool InputManager::isKeyPressed(GLESC::Key keycode) {
    auto it = keyMap.find(keycode);
    if (it != keyMap.end()) {
        return it->second;
    }
    return false;
}
