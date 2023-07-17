#include "engine/core/input/InputManager.h"



InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::init() {

}

void InputManager::update() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                exit(0);
            }
            case SDL_MOUSEMOTION: {
                mousePosition.x = event.motion.x;
                mousePosition.y = event.motion.y;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                keyMap[event.button.button] = true;
                break;
            }
            case SDL_KEYUP: {
                keyMap[event.button.button] = false;
                break;
            }
            case SDL_KEYDOWN: {
                keyMap[event.key.keysym.sym] = true;
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    exit(0);
                }
                break;
            }
        }
    }
}

bool InputManager::isKeyDown(SDL_Keycode keycode) {
    auto it = keyMap.find(keycode);
    if (it != keyMap.end()) {
        return it->second;
    }
    return false;
}
