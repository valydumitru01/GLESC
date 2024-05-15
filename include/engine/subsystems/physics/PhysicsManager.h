/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "Physics.h"
#include "PhysicsTypes.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Physics {
    class PhysicsManager {
    public:
        void updatePhysics(Physics& physics, Transform::Transform& transform);

    private:
        Acceleration gravity{0.f, -8.91f, 0.f};
    };
} // namespace GLESC
