/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/frontend/system/System.h"

class MovementSystem : public System{
public:
    MovementSystem();
    ~MovementSystem();
    void update();
private:
};
