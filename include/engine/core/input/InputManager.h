#pragma once

#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include "InputTypes.h"
#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager();
    void init();
    void update();
    bool isKeyDown(SDL_Keycode keycode);
    
    MousePosition getMousePosition() { return mousePosition; }
    KeyMap getKeyMap() { return keyMap; }
private:
    MousePosition mousePosition;
    KeyMap keyMap;
};
