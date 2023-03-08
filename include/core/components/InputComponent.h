#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class InputComponent: public Component
{
public:
    glm::vec2 mousePosition{ 0.f, 0.f };
    std::unordered_map<int, bool> keyMap;
};

