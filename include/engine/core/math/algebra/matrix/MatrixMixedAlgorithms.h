/******************************************************************************
 * @file   MatrixAlgorithm.h
 * @author Valentin Dumitru
 * @date   2023-10-31
 * @brief  This is needed to avoid circular dependencies between MatrixMixedAlgorithms and VectorMixedAlgorithms.
 * @see VectorMixedAlgorithms.h for more details on why this is needed.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <engine/core/math/algebra/vector/VectorMixedAlgorithms.h>
#include "engine/core/asserts/Asserts.h"
#include "engine/core/exceptions/core/math/MathException.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/algebra/matrix/MatrixTypes.h"
#include "engine/core/math/algebra/vector/VectorAlgorithms.h"
#include "MatrixAlgorithms.h"

namespace GLESC::Math {
    class MatrixMixedAlgorithms {
    public:
        
        
        // =============================================================================================================
        // ============================================ Matrix operations ==============================================
        // =============================================================================================================
        
        
        
        
        
        
        
        
        template<typename Type>
        static inline void
        rotate2D(const MatrixData<Type, 3, 3> &matrix, const Type dgrs, MatrixData<Type, 3, 3> &resMatrix) {
            MatrixData<Type, 3, 3> result =
                    {{{matrix[0][0], matrix[0][1], matrix[0][2]},
                      {matrix[1][0], matrix[1][1], matrix[1][2]},
                      {matrix[2][0], matrix[2][1], matrix[2][2]}}};
            Type c = cos(dgrs);
            Type s = sin(dgrs);
            
            MatrixData<Type, 3, 3> rotation =
                    {{{Type(c), Type(-s), Type(0)},
                      {Type(s), Type(c), Type(0)},
                      {Type(0), Type(0), Type(1)}}};
            
            MatrixAlgorithms::matrixMul(rotation, result, resMatrix);
        }
        
        /**
         * @brief Rotate a 3D matrix around the X, Y, and Z axis.
         * @details This function applies sequential rotations to the input matrix based on the given angles.
         * The function assumes a specific order of rotations. It seems to be Z, then Y, then X
         * TODO: Be cautious about gimbal lock when using Euler angles.
         *   It's recommended to use quaternions for robustness.
         *
         * @tparam Type The data type of the matrix and vector elements (e.g., float, double).
         * @param matrix The input 4x4 matrix that needs to be rotated.
         * @param dgrs A 3D vector containing the rotation angles (in radians) around X, Y, and Z axes
         * respectively.
         * @return A 4x4 matrix which is the result of the input matrix after the rotations.
         */
        template<typename Type>
        static inline void rotate3D(const MatrixData<Type, 4, 4> &matrix,
                                    const VectorData<Type, 3> &dgrs,
                                    MatrixData<Type, 4, 4> &resMatrix) {
            MatrixData<Type, 4, 4> result;
            MatrixAlgorithms::copyMatrix(result, matrix);
            
            Type cx = cos(dgrs[0]); // X component
            Type sx = sin(dgrs[0]); // X component
            Type cy = cos(dgrs[1]); // Y component
            Type sy = sin(dgrs[1]); // Y component
            Type cz = cos(dgrs[2]); // Z component
            Type sz = sin(dgrs[2]); // Z component
            
            
            // Combine the three rotation matrices into a single matrix
            MatrixData<Type, 4, 4> rot = {{{cy * cz, -cy * sz, sy, Type(0)},
                                           {sx * sy * cz + cx * sz, -sx * sy * sz + cx * cz, -sx * cy, Type(0)},
                                           {-cx * sy * cz + sx * sz, cx * sy * sz + sx * cz, cx * cy, Type(0)},
                                           {Type(0), Type(0), Type(0), Type(1)}}};
            
            MatrixAlgorithms::matrixMul(rot, result, resMatrix);
        }
        
        template<typename Type>
        static inline void lookAt2D(const MatrixData<Type, 3, 3> &matrix,
                                    const VectorData<Type, 2> &target,
                                    MatrixData<Type, 3, 3> &result) {
            VectorData<Type, 2> eye = {matrix[0][2], matrix[1][2]};
            VectorData<Type, 2> direction = {target[0] - eye[0], target[1] - eye[1]};
            
            if (eye[0] == target[0] && eye[1] == target[1]) {
                // If the eye and target are the same, the result is the identity matrix
                MatrixAlgorithms::copyMatrix(result, matrix);
                return;
            }
            
            Type angle = -std::atan2(direction[1], direction[0]);
            
            // Assuming rotate2D accepts matrices as flat arrays
            rotate2D(matrix, angle, result);
        }
        
        template<typename Type>
        static inline void lookAt3D(const MatrixData<Type, 4, 4> &matrix,
                                    const VectorData<Type, 3> &target,
                                    const VectorData<Type, 3> &up,
                                    MatrixData<Type, 4, 4> &resMatrix) {
            VectorData<Type, 3> eye({matrix[0][3], matrix[1][3], matrix[2][3]});
            VectorData<Type, 3> zAxis;
            VectorAlgorithms::vectorSub(eye, target, zAxis);
            VectorAlgorithms::normalize(zAxis, zAxis);
            VectorData<Type, 3> xAxis;
            VectorAlgorithms::crossProduct(up, zAxis, xAxis);
            VectorAlgorithms::normalize(xAxis, xAxis);
            VectorData<Type, 3> yAxis;
            VectorAlgorithms::crossProduct(zAxis, xAxis, yAxis);
            VectorAlgorithms::normalize(yAxis, yAxis);
            
            // Rotation matrix using the new basis vectors (inverted change of basis matrix)
            MatrixData<Type, 4, 4> lookRotation = {{{xAxis[0], yAxis[0], zAxis[0], 0},
                                                    {xAxis[1], yAxis[1], zAxis[1], 0},
                                                    {xAxis[2], yAxis[2], zAxis[2], 0},
                                                    {0, 0, 0, 1}}};
            
            // Translation matrix to move the camera to the origin
            MatrixData<Type, 4, 4> translation = {{{1, 0, 0, -eye[0]},
                                                   {0, 1, 0, -eye[1]},
                                                   {0, 0, 1, -eye[2]},
                                                   {0, 0, 0, 1}}};
            
            // First translate to the origin, then apply the rotation
            MatrixAlgorithms::matrixMul(lookRotation, translation, resMatrix);
            MatrixAlgorithms::matrixMul(resMatrix, matrix, resMatrix);
            
        }
        
    }; // class MatrixAlgorithms
}; // namespace GLESC::Math
    
