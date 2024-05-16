/**************************************************************************************************
 * @file   BoundingVolume.h
 * @author Valentin Dumitru
 * @date   13/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Math {
    /**
     * @brief A bounding volume is a geometric shape that encloses a set of points.
     * @details This class updates the bounding cuboid to fit the points it encloses.
     */
    class BoundingVolume {
    public:
        struct AABB {
            Vec3F min;
            Vec3F max;
        };
        BoundingVolume() = default;

        BoundingVolume(const Vec3F& min, const Vec3F& max) {
            buildBoundingVolume(min, max);
        }


        void setVolume(const Vec3F& min, const Vec3F& max) {
            buildBoundingVolume(min, max);
        }

        const AABB& getVolume() const {
            return boundingBox;
        }
        /**
         * @brief Updates the bounding volume to fit the points it encloses.
         * @param data The data to update the bounding volume with
         * @param size The size of the data
         * @param stride The stride (size of each vertex) of the data
         * @param offset The offset (position of the position attribute) of the data
         */
        void updateBoundingBox(const void* data, unsigned int size, unsigned int stride, unsigned int offset) {
            // Initialize bounds
            Vec3F minVec(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
                         std::numeric_limits<float>::max());
            Vec3F maxVec(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(),
                         std::numeric_limits<float>::lowest());

            // Iterate through the vertices to find the bounding box
            for (unsigned int i = 0; i < size; i += stride) {
                float x = *reinterpret_cast<const float*>(reinterpret_cast<const char*>(data) + i + offset);
                float y = *reinterpret_cast<const float*>(reinterpret_cast<const char*>(data) + i + offset + sizeof(
                    float));
                float z = *reinterpret_cast<const float*>(reinterpret_cast<const char*>(data) + i + offset + 2 * sizeof(
                    float));

                minVec.x() = std::min(minVec.x(), x);
                minVec.y() = std::min(minVec.y(), y);
                minVec.z() = std::min(minVec.z(), z);
                maxVec.x() = std::max(maxVec.x(), x);
                maxVec.y() = std::max(maxVec.y(), y);
                maxVec.z() = std::max(maxVec.z(), z);
            }

            // Check if the bounding volume is valid (not empty)
            if (minVec.x() >= maxVec.x() || minVec.y() >= maxVec.y() || minVec.z() >= maxVec.z()) {
                return;
            }

            // Build the bounding volume
            buildBoundingVolume(minVec, maxVec);
        }

        const AABB& getBoundingBox() const {
            return boundingBox;
        }

        void operator=(const BoundingVolume& other) {
            boundingBox = other.boundingBox;
        }

    private:
        void buildBoundingVolume(const Vec3F& minVec, const Vec3F& maxVec) {
            boundingBox.min = minVec;
            boundingBox.max = maxVec;
        }

        AABB boundingBox;
    };
} // namespace GLESC::Math
