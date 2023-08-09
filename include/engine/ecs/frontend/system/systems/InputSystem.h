/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/input/InputManager.h"

class InputSystem : public System {
public:
    explicit InputSystem(InputManager &inputManager);
    void update();
private:
    InputManager& inputManager;
};
