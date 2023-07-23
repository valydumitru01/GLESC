#pragma once
#include <SDL2/SDL.h>
#include "InputTypes.h"
// TODO: Create key enum class
class InputManager {
public:
    InputManager();
    ~InputManager();
    void init();
    void update();
    bool isKeyPressed(SDL_Keycode keycode);
    
    MousePosition getMousePosition(){return mousePosition;};
private:
    MousePosition mousePosition;
    KeyMap keyMap;
};
