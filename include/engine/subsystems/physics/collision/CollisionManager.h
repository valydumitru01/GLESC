/**************************************************************************************************
 * @file   CollisionManager.h
 * @author Valentin Dumitru
 * @date   16/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "Collider.h"
#include "engine/core/math/geometry/figures/BoundingVolume.h"

class CollisionManager {

public:
    void checkCollision(const Collider& collider) {

    }
private:
    std::vector<Collider*> colliders;
}; // class CollisionManager
