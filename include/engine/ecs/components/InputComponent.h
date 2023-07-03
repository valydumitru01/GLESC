#pragma once

#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include <unordered_map>
#include "Component.h"

class InputComponent : public Component {
public:
    glm::vec <2, Sint32, glm::packed> mousePosition{0, 0};
    std::unordered_map <SDL_Keycode, bool> keyMap;
};

