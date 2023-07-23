#pragma once

#include "System.h"
#include "engine/subsystems/input/InputManager.h"

class InputSystem : public System {
public:
    explicit InputSystem(InputManager &inputManager);
    void update();
private:
    InputManager& inputManager;
};
