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
    using Point = Vec3D;
    using Points = std::vector<Point>;
    using Direction = Vec3D;
    using Index = unsigned int;
    using FaceIndices = std::vector<Index>;
}