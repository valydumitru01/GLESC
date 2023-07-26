#include "engine/subsystems/input/InputManager.h"
#include <unordered_map>

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

void InputManager::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
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
    keyMap[keycode] = pressed;
}

void InputManager::handleMouseEvent(const SDL_Event &event) {
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
