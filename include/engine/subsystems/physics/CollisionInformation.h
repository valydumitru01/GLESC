/**************************************************************************************************
 * @file   CollisionInformation.h
 * @author Valentin Dumitru
 * @date   05/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <vector>

#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Physics {
    class Physics;
    class Collider;
}

struct CollisionInformation {
    std::vector<Vec3F> collisionPenetrationsForAxis;
    bool collided = false;
    std::vector<GLESC::Physics::Collider*> colliders;
    std::vector<GLESC::Physics::Physics*> physicsOfCollided;
};
