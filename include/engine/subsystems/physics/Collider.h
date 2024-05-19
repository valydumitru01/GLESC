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

#include "../../core/math/geometry/figures/BoundingVolume.h"

namespace GLESC::Physics {
    class PhysicsManager;
}

namespace GLESC::Physics {
    class Collider {
        friend class GLESC::Physics::PhysicsManager;

    public:
        Collider() = default;
        ~Collider() = default;

        void setCollisionCallback(std::function<void()> callback) { collisionCallback = callback; }

        void setCollisionCallbackForCollider(const Collider& collider, std::function<void()> callback) {
            collisionCallbacksForSpecificColliders[&collider] = callback;
        }

        bool isSolid() const { return solid; }

        void setBoundingVolume(const Vec3F corner1, const Vec3F corner2) {
            boundingVolume = GLESC::Math::BoundingVolume(corner1, corner2);
        }

        void setBoundingVolume(const GLESC::Math::BoundingVolume& boundingVolume) {
            this->boundingVolume = boundingVolume;
        }

    private:
        std::function<void()> collisionCallback;
        std::unordered_map<const Collider*, std::function<void()>> collisionCallbacksForSpecificColliders;
        GLESC::Math::BoundingVolume boundingVolume;
        bool solid = true;
    }; // class Collider
}
