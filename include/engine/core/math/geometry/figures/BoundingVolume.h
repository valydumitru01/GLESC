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
            Vec3F min{-1, -1, -1};
            Vec3F max{1, 1, 1};
        };

        BoundingVolume() = default;

        BoundingVolume(const Vec3F& min, const Vec3F& max) {
            buildBoundingVolume(min, max);
        }


        void setVolume(const Vec3F& min, const Vec3F& max) {
            buildBoundingVolume(min, max);
        }

        [[nodiscard]] const AABB& getVolume() const {
            return boundingBox;
        }

        /**
         * @brief Updates the bounding volume to fit the points it encloses.
         * @param data The data to update the bounding volume with
         * @param size The size of the data
         * @param stride The stride (size of each vertex) of the data
         * @param offset The offset (position of the position attribute) of the data
         */
        void updateBoundingBox(const void* data, const unsigned int size, const unsigned int stride,
                               const unsigned int offset) {
            // Initialize bounds
            Vec3F minVec(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
                         std::numeric_limits<float>::max());
            Vec3F maxVec(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(),
                         std::numeric_limits<float>::lowest());

            // Iterate through the vertices to find the bounding box
            for (unsigned int i = 0; i < size; i += stride) {
                float x = *reinterpret_cast<const float*>(static_cast<const char*>(data) + i + offset);
                float y = *reinterpret_cast<const float*>(static_cast<const char*>(data) + i + offset + sizeof(
                    float));
                float z = *reinterpret_cast<const float*>(static_cast<const char*>(data) + i + offset + 2 * sizeof(
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

        [[nodiscard]] bool hasInside(const Vec3F& point) const {
            return point.getX() >= boundingBox.min.getX() && point.getX() <= boundingBox.max.getX() &&
                point.getY() >= boundingBox.min.getY() && point.getY() <= boundingBox.max.getY() &&
                point.getZ() >= boundingBox.min.getZ() && point.getZ() <= boundingBox.max.getZ();
        }

        [[nodiscard]] float intersectionVolume(const BoundingVolume& other) const {
            float depthX = 0, depthY = 0, depthZ = 0;

            // Check X axis
            if (boundingBox.max.getX() > other.boundingBox.min.getX() &&
                boundingBox.min.getX() < other.boundingBox.max.getX()) {
                depthX = std::min(boundingBox.max.getX(), other.boundingBox.max.getX()) -
                    std::max(boundingBox.min.getX(), other.boundingBox.min.getX());
            }

            // Check Y axis
            if (boundingBox.max.getY() > other.boundingBox.min.getY() &&
                boundingBox.min.getY() < other.boundingBox.max.getY()) {
                depthY = std::min(boundingBox.max.getY(), other.boundingBox.max.getY()) -
                    std::max(boundingBox.min.getY(), other.boundingBox.min.getY());
            }

            // Check Z axis
            if (boundingBox.max.getZ() > other.boundingBox.min.getZ() &&
                boundingBox.min.getZ() < other.boundingBox.max.getZ()) {
                depthZ = std::min(boundingBox.max.getZ(), other.boundingBox.max.getZ()) -
                    std::max(boundingBox.min.getZ(), other.boundingBox.min.getZ());
            }

            // If no overlap in any axis, return 0
            if (depthX <= 0 || depthY <= 0 || depthZ <= 0) {
                return 0.0f;
            }

            // Return the volume of the intersection
            return depthX * depthY * depthZ;
        }


        [[nodiscard]] bool intersects(const BoundingVolume& other) const {
            if (boundingBox.min.getX() >= other.boundingBox.max.getX() ||
                boundingBox.max.getX() <= other.boundingBox.min.getX())
                return false;
            if (boundingBox.min.getY() >= other.boundingBox.max.getY() ||
                boundingBox.max.getY() <= other.boundingBox.min.getY())
                return false;
            if (boundingBox.min.getZ() >= other.boundingBox.max.getZ() ||
                boundingBox.max.getZ() <= other.boundingBox.min.getZ())
                return false;
            return true;
        }


        [[nodiscard]] const AABB& getBoundingBox() const {
            return boundingBox;
        }

        [[nodiscard]] AABB& getBoundingBox() {
            return boundingBox;
        }

        [[nodiscard]] const Vec3F& getMin() const {
            return boundingBox.min;
        }

        [[nodiscard]] const Vec3F& getMax() const {
            return boundingBox.max;
        }

        static BoundingVolume createFromVulume(float width, float height, float depth) {
            D_ASSERT_GREATER(width, 0, "Width must be greater than 0");
            D_ASSERT_GREATER(height, 0, "Height must be greater than 0");
            D_ASSERT_GREATER(depth, 0, "Depth must be greater than 0");
            return {Vec3F(-width / 2, -height / 2, -depth / 2), Vec3F(width / 2, height / 2, depth / 2)};
        }

    private:
        void buildBoundingVolume(const Vec3F& minVec, const Vec3F& maxVec) {
            boundingBox.min = minVec;
            boundingBox.max = maxVec;
        }

        AABB boundingBox;
    };
} // namespace GLESC::Math
