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
        /**
         * @brief The axis-aligned bounding box of the bounding volume.
         * @details AABB is a box aligned with the axes of the coordinate space.
         * It is a very simple shape that can be used to enclose other shapes.
         * It's simpicity makes operations like intersection and containment very fast.
         * @cite https://gdbooks.gitbooks.io/3dcollisions/content/Chapter1/aabb.html
         */
        struct AABB {
            Vec3F min{-1, -1, -1};
            Vec3F max{1, 1, 1};
        };

        /**
         * @brief Construct a new Bounding Volume object.
         * @details The default bounding volume is a unit cube ([-1, -1, -1], [1, 1, 1]).
         */
        BoundingVolume() = default;
        /**
         * @brief Construct a new Bounding Volume object.
         * @param min The minimum point of the bounding volume
         * @param max The maximum point of the bounding volume
         */
        BoundingVolume(const Vec3F& min, const Vec3F& max);

        /**
         * @brief Set the volume of the bounding volume.
         * @param min The minimum point of the bounding volume
         * @param max The maximum point of the bounding volume
         */
        void setVolume(const Vec3F& min, const Vec3F& max);

        /**
         * @brief Get the volume of the bounding volume.
         * @return The volume of the bounding volume
         */
        [[nodiscard]] const AABB& getVolume() const { return boundingBox; }

        /**
         * @brief Updates the bounding volume to fit the points it encloses.
         * @param data The data to update the bounding volume with
         * @param size The size of the data
         * @param stride The stride (size of each vertex) of the data
         * @param offset The offset (position of the position attribute) of the data
         */
        void updateBoundingBox(const void* data, unsigned int size, unsigned int stride,
                               unsigned int offset);

        /**
         * @brief Checks if the bounding volume contains the given point.
         * @param point The point to check
         * @return True if the bounding volume contains the point, false otherwise
         */
        [[nodiscard]] bool hasInside(const Vec3F& point) const;

        /**
         * @brief Get the intersection volume of the bounding volume with another bounding volume.
         * @param other The other bounding volume
         * @return The intersection volume of the bounding volume with the other bounding volume
         */
        [[nodiscard]] float intersectionVolume(const BoundingVolume& other) const;

        /**
         * @brief Checks if the bounding volume intersects with another bounding volume.
         * @param other The other bounding volume
         * @return True if the bounding volume intersects with the other bounding volume, false otherwise
         */
        [[nodiscard]] bool intersects(const BoundingVolume& other) const;

        /**
         * @brief Get the const bounding box of the bounding volume.
         * @return The bounding box of the bounding volume
         */
        [[nodiscard]] const AABB& getBoundingBox() const { return boundingBox; }

        /**
         * @brief Get the bounding box of the bounding volume.
         * @return The bounding box of the bounding volume
         */
        [[nodiscard]] AABB& getBoundingBox() { return boundingBox; }

        /**
         * @brief Get the minimum point of the bounding volume.
         * @return The minimum point of the bounding volume
         */
        [[nodiscard]] const Vec3F& getMin() const { return boundingBox.min; }

        /**
         * @brief Get the maximum point of the bounding volume.
         * @return The maximum point of the bounding volume
         */
        [[nodiscard]] const Vec3F& getMax() const { return boundingBox.max; }

        /**
         * @brief Create a bounding volume from a volume.
         * @param width The width of the volume
         * @param height The height of the volume
         * @param depth The depth of the volume
         * @return The bounding volume created from the volume
         */
        [[nodiscard]] static BoundingVolume createFromVulume(float width, float height, float depth);

    private:
        /**
         * @brief Builds the bounding volume from the minimum and maximum points.
         * @param minVec The minimum point of the bounding volume
         * @param maxVec The maximum point of the bounding volume
         */
        void buildBoundingVolume(const Vec3F& minVec, const Vec3F& maxVec);

        /**
         * @brief The bounding box of the bounding volume.
         */
        AABB boundingBox;
    };
} // namespace GLESC::Math
