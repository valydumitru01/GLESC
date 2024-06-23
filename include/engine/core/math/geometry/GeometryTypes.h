/**************************************************************************************************
 * @file   GeometryTypes.h
 * @author Valentin Dumitru
 * @date   12/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Math{
    /**
     * @brief Alias for the volume type
     */
    using Volume = float;
    /**
     * @brief Alias for the point type, points are 3D vectors
     */
    using Point = Vec3F;
    /**
     * @brief Alias for the points type, a collection of points
     */
    using Points = std::vector<Point>;
    /**
     * @brief Alias for the direction type, directions are 3D vectors
     */
    using Direction = Vec3F;
    /**
     * @brief Alias for the distance type
     */
    using Distance = float;
    /**
     * @brief Alias for any index type, no need for signed indices
     */
    using Index = unsigned int;
    /**
     * @brief Alias for the face indices type, a face is defined by 3 indices
     */
    using FaceIndices = std::array<Index, 3>;
    /**
     * @brief Alias for the quad indices type, a quad is defined by 4 indices
     */
    using QuadIndices = std::array<Index, 4>;
}