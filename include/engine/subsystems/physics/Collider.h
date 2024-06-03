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

namespace GLESC::Physics {
    class PhysicsManager;
}

namespace GLESC::Physics {
    class Collider {
        friend class GLESC::Physics::PhysicsManager;

    public:
        Collider() = default;
        ~Collider() = default;

        void setCollisionCallback(std::function<void(Collider&)> callback) { collisionCallback = callback; }

        void setCollisionCallbackForCollider(Collider& collider, std::function<void(Collider&)> callback) {
            collisionCallbacksForSpecificColliders[&collider] = callback;
        }

        bool isSolid() const { return solid; }
        void setSolid(bool solid) { this->solid = solid; }

        void destroyEntity() {
            destroyed = true;
        }

        bool isDestroyed() const {
            return destroyed;
        }

        void setBoundingVolume(const GLESC::Math::BoundingVolume& boundingVolume) {
            this->boundingVolume = boundingVolume;
        }


        const Math::BoundingVolume& getBoundingVolume() const {
            return boundingVolume;
        }

        void setIsOnAir(bool isOnAir) {
            this->onAir = isOnAir;
        }

        bool isOnAir() const {
            return onAir;
        }

    private:
        std::function<void(Collider&)> collisionCallback;
        std::unordered_map<Collider*, std::function<void(Collider&)>> collisionCallbacksForSpecificColliders;
        GLESC::Math::BoundingVolume boundingVolume;
        bool solid = true;
        bool onAir = true;
        bool destroyed = false;
    }; // class Collider
}
