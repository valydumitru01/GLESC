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

#include "engine/subsystems/renderer/math/RenderMath.h"

/**
 * @brief Creates a view matrix from a transform component of the camera
 * @details uses the lookAt function from glm
 * @param transform component of the camera
 * @return view matrix
 */
Mat4D
RenderMath::calculateViewMatrix(const Vec3D &position, const Vec3D &rotation,
                                const Vec3D &scale) {
    Mat4D model = calculateTransformMatrix(position, rotation, scale);
    return model.inverse();
}

/**
 * @brief Creates a projection matrix from a camera component
 * @details uses the perspective function from glm
 * @param camera component
 * @return projection matrix
 */
Mat4D RenderMath::calculateProjectionMatrix(float fov,
                                            float nearPlane,
                                            float farPlane,
                                            float viewWidth,
                                            float viewHeight) {
    if (viewHeight == 0.0f)
        throw EngineException("Unable to make projection matrix: viewHeight is 0");
    if (viewWidth == 0.0f)
        throw EngineException("Unable to make projection matrix: viewWidth is 0");
    
    float aspectRatio = viewWidth / viewHeight;
    return GLESC::Math::perspective(GLESC::Math::radians(fov), aspectRatio, nearPlane,
                                    farPlane);
}

/**
 * @brief Calculates transform matrix
 * @details Given the position, rotation, and scale, this method
 * calculates the transform matrix
 * @param position The position vector
 * @param rotation The rotation vector
 * @param scale The scale vector
 * @return The model matrix
 */
Mat4D
RenderMath::calculateTransformMatrix(const Vec3D &position, const Vec3D &rotation,
                                     const Vec3D &scale) {
    
    Mat4D model = Mat4D(1.0).translate(position);
    
    model = model.rotate(rotation);
    
    model = model.scale(scale);
    
    return model;
}