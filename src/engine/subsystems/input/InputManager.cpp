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

#include "engine/subsystems/ingame-debug/StatsManager.h"
using namespace GLESC::Input;

InputManager::InputManager(HUDManager& hudManagerm, WindowManager& windowManager): hudManager(hudManager),
    windowManager(windowManager) {
}

void InputManager::handleWindowEvent(const SDL_Event& event) {
    switch (event.window.event) {
    case SDL_WINDOWEVENT_RESIZED:
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        // Update the internal size in the window manager.
        windowManager.setSize(event.window.data1, event.window.data2);
        break;

    default:
        break;
    }
}

void InputManager::update(bool& running) {
    SDL_Point sdlMousePos = {0, 0};
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        hudManager.processInput(event);
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_WINDOWEVENT:
            handleWindowEvent(event);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            handleKeyEvent(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION:
            handleMouseEvent(event);
            if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
                sdlMousePos = {event.motion.xrel, event.motion.yrel};
            }
            break;
        default:
            break;
        }
    }
    // When no input is given to the mouse, send a 0,0 movement to the buffer and lerp the mouse position
    if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
        addToBuffer(sdlMousePos.x, sdlMousePos.y);
        lerpMousePos(mousePos, getAvgMousePos());
    }
}


void InputManager::handleKeyEvent(const SDL_Event& event) {
    auto keycode = static_cast<Key>(event.key.keysym.sym);
    bool pressed = event.type == SDL_KEYDOWN;
    updateKeyState(keycode, pressed);
}

void InputManager::handleMouseEvent(const SDL_Event& event) {
    // Handle mouse button events
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        auto mouseButton = static_cast<Key>(event.button.button);
        bool pressed = event.type == SDL_MOUSEBUTTONDOWN;
        updateKeyState(mouseButton, pressed);
    }
    if (SDL_GetRelativeMouseMode() == SDL_FALSE) {
        if (event.type == SDL_MOUSEMOTION) {
            mousePos.x() = static_cast<float>(event.motion.x);
            mousePos.y() = static_cast<float>(event.motion.y);
        }
    }
}

void InputManager::addToBuffer(int posDx, int posDy) {
    if (deltaBuffer.size() >= bufferSize) {
        deltaBuffer.pop_front();
    }
    deltaBuffer.emplace_back(static_cast<float>(posDx) * 0.1f, static_cast<float>(posDy) * 0.1f);
}

void InputManager::updateKeyState(Key key, bool pressed) {
    auto& keyState = keyMap[key];
    if (pressed) {
        if (!keyState.pressed) {
            keyState.justPressed = true;
        }
        else {
            keyState.justPressed = false;
        }
        keyState.pressed = true;
    }
    else {
        if (keyState.pressed) {
            keyState.justReleased = true;
        }
        else {
            keyState.justReleased = false;
        }
        keyState.pressed = false;
        keyState.justPressed = false;
    }
}

std::vector<Key> InputManager::getPressedKeys() const {
    std::vector<Key> pressedKeys;
    for (const auto& [key, state] : keyMap) {
        if (state.pressed) {
            pressedKeys.push_back(key);
        }
    }
    return pressedKeys;
}

MousePosition InputManager::getAvgMousePos() const {
    float sumX = 0, sumY = 0;
    for (const auto& delta : deltaBuffer) {
        sumX += delta.getX();
        sumY += delta.getY();
    }
    if (!deltaBuffer.empty()) {
        float avgX = sumX / static_cast<float>(deltaBuffer.size());
        float avgY = sumY / static_cast<float>(deltaBuffer.size());

        return MousePosition{
            avgX,
            avgY
        };
    }
    return MousePosition{0, 0};
}

void InputManager::lerpMousePos(MousePosition& oldMousePos, const MousePosition& targetMousePos) const {
    oldMousePos = targetMousePos;
    //oldMousePos.setX(Math::lerp(oldMousePos.getX(), targetMousePos.getX(), mouseSmoothFactor));
    //oldMousePos.setY(Math::lerp(oldMousePos.getY(), targetMousePos.getY(), mouseSmoothFactor));
}


bool InputManager::checkKeyAction(const KeyInput& keyInput) {
    auto it = keyMap.find(keyInput.key);
    if (it != keyMap.end()) {
        auto& state = it->second;
        switch (keyInput.action) {
        case KeyAction::ONGOING_PRESSED:
            return state.pressed;
        case KeyAction::ONCE_PRESSED:
            if (state.justPressed) {
                state.justPressed = false; // Reset the flag
                return true;
            }
            break;
        case KeyAction::ONCE_RELEASED:
            if (state.justReleased) {
                state.justReleased = false; // Reset the flag
                return true;
            }
            break;
        default:
            break;
        }
    }
    return false;
}

void InputManager::setMouseRelative(bool enabled) {
    if (SDL_SetRelativeMouseMode(static_cast<SDL_bool>(enabled)) != 0) {
        std::string action = enabled ? "enable" : "disable";
        throw EngineException(
            "Unable to " + action + " mouse relative mode: " + std::string(SDL_GetError())
        );
    }
    // Reset the mouse position, looks like it's not done by SDL
    mousePos.x() = 0;
    mousePos.y() = 0;
}

bool InputManager::isMouseRelative() {
    return SDL_GetRelativeMouseMode() == SDL_TRUE;
}
