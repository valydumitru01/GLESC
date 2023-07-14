#pragma once

#include "engine/ecs/systems/System.h"

class MovementSystem : public System{
public:
    MovementSystem();
    ~MovementSystem();
    void update();
private:
};
