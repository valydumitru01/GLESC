/**************************************************************************************************
 * @file   TransformTypes.h
 * @author Valentin Dumitru
 * @date   2024-04-02
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Transform {
    /**
     * @brief Position in 3D space
     * @details A position in 3D space represented by a vector of 3 components
     * [0] - x coordinate
     * [1] - y coordinate
     * [2] - z coordinate
     */
    using Position = Vec3F;
    /**
     * @brief The homogenized position in 3D space, the fourth component is the w component
     * @details The homogenized position in 3D space represented by a vector of 4 components
     * The x, y, z and the w component
     * The w component allows positions to be transformed by 4x4 matrices.
     * Without the w component, we wouldn't be able to translate positions at the same time as rotating them and
     * scaling them.
     * To dehomogize positions we divide the x, y, z components by the w component.
     */
    using HomogeneousPosition = Vec4F;
    using PosComp = Position::ValueType;

    /**
     * @brief Rotation in 3D space
     * @details A rotation in 3D space represented by a vector of 3 components
     * [0] - x rotation or pitch
     * [1] - y rotation or yaw
     * [2] - z rotation or roll
     */
    using Rotation = Vec3F;
    using RotComp = Rotation::ValueType;

    /**
     * @brief Scale in 3D space
     * @details A scale in 3D space represented by a vector of 3 components
     * [0] - x scale or width
     * [1] - y scale or height
     * [2] - z scale or depth
     */
    using Scale = Vec3F;
    using ScaleComp = Scale::ValueType;
} // namespace GLESC::Transform
