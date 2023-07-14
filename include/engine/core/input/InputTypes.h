#pragma once
#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include <unordered_map>

using MousePosition = glm::vec<2, Sint32, glm::packed>;

using KeyMap = std::unordered_map<SDL_Keycode, bool>;