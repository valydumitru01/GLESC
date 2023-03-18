#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "core/systems/input/KeyAction.h"
#include <SDL.h>
class InputComponent: public Component
{
public:
    glm::vec<2, Sint32,glm::packed> mousePosition{ 0, 0 };
    std::unordered_map<SDL_Keycode, bool> keyMap;

};

