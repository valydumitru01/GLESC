/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/subsystems/transform/Transform.h"

struct TransformComponent : IComponent {
    GLESC::Transform transform;
    
    std::string toString() override {
        return "TransformComponent:\n"
               + transform.toString();
    }
};
