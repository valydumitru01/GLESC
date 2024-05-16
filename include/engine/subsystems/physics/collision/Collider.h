/**************************************************************************************************
 * @file   Collider.h
 * @author Valentin Dumitru
 * @date   16/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>

#include "engine/core/math/geometry/figures/BoundingVolume.h"

class Collider {
public:
    Collider() = default;
    ~Collider() = default;

    void checkCollision();
private:
    std::function<void()> collisionCallback;
    std::unordered_map<Collider*, std::function<void()>> collisionCallbacksForSpecificColliders;
    GLESC::Math::BoundingVolume boundingVolume;
}; // class Collider
