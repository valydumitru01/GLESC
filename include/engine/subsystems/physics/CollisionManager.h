/**************************************************************************************************
 * @file   CollisionManager.h
 * @author Valentin Dumitru
 * @date   06/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <vector>
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/math/geometry/figures/BoundingVolume.h"
#include "Collider.h"
#include "Physics.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Physics {
    class CollisionManager {
    public:
        void addCollider(Collider& collider, Physics& physics, Transform::Transform& transform) {
            this->colliders.push_back(&collider);
            this->transformsOfColliders.push_back(&transform);
            this->physicsOfColliders.push_back(&physics);
        }

        void clearColliders() {
            this->colliders.clear();
            this->transformsOfColliders.clear();
            this->physicsOfColliders.clear();
        }

        void checkAndUpdateColliders(Collider& collider,
                             const Transform::Transform& originalTransform,
                             const Transform::Transform& hypNextFrameTransform);



    private:
        static Vec3F getCollisionDepth(const Math::BoundingVolume& nextColliderBVX,
                                                         const Math::BoundingVolume& nextColliderBVY,
                                                         const Math::BoundingVolume& nextColliderBVZ,
                                                         const Math::BoundingVolume& otherBV);

        void updateCollider(Collider& originalCollider,
                            const Transform::Transform& originalTransform,
                            const Math::BoundingVolume& nextColliderBVX,
                            const Math::BoundingVolume& nextColliderBVY,
                            const Math::BoundingVolume& nextColliderBVZ);

        std::vector<Physics*> physicsOfColliders;
        std::vector<Collider*> colliders;
        std::vector<Transform::Transform*> transformsOfColliders;
    }; // class CollisionManager
}
