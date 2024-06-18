/**************************************************************************************************
 * @file   TransformTypes.h
 * @author Valentin Dumitru
 * @date   2024-04-02
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Transform {

    using Position = Vec3F;
    using HomogeneousPosition = Vec4F;
    using PosComp = Position::ValueType;

    using Rotation = Vec3F;
    using RotComp = Rotation::ValueType;

    using Scale = Vec3F;
    using ScaleComp = Scale::ValueType;
} // namespace GLESC::Transform
