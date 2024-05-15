/**************************************************************************************************
 * @file   PhysicsTypes.h
 * @author Valentin Dumitru
 * @date   2024-03-25
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Physics {
    using Mass = float;
    using Velocity = Vec3F;
    using Force = Vec3F;
    using Acceleration = Vec3F;

    using AngularVelocity = Vec3F;
    using AngularForce = Vec3F;
    using AngularAcceleration = Vec3F;

    using ForwardVelocity = float;
    using ForwardForce = float;
    using ForwardAcceleration = float;
} // namespace Physics
