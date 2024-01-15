/**************************************************************************************************
 * @file   RenderingMath.h
 * @author Valentin Dumitru
 * @date   10/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/algebra/vector/Vector.h"

class RenderMath {
public:
    /**
     * @brief Creates a view matrix from a transform component of the camera
     * @details uses the lookAt function from glm
     * @param transform component of the camera
     * @return view matrix
     */
    static Mat4D
    calculateViewMatrix(const Vec3D &position, const Vec3D &rotation, const Vec3D &scale);

    /**
     * @brief Creates a projection matrix from a camera component
     * @details uses the perspective function from glm
     * @param camera component
     * @return projection matrix
     */
    static Mat4D
    calculateProjectionMatrix(float fov, float nearPlane, float farPlane,
                              float viewWidth, float viewHeight);

    /**
     * @brief Calculates transform matrix
     * @details Given the position, rotation, and scale, this method
     * calculates the transform matrix
     * @param position The position vector
     * @param rotation The rotation vector
     * @param scale The scale vector
     * @return The model matrix
     */
    static Mat4D
    calculateTransformMatrix(const Vec3D &position, const Vec3D &rotation, const Vec3D &scale);
};