/******************************************************************************
 * @file   MatrixMixedAlgorithms.h
 * @author Valentin Dumitru
 * @date   2023-10-31
 * @brief  This is needed to avoid circular dependencies between MatrixMixedAlgorithms and VectorMixedAlgorithms.
 * @see VectorMixedAlgorithms.h for more details on why this is needed.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once


#include "engine/core/asserts/Asserts.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/algebra/matrix/MatrixAlgorithms.h"
#include "engine/core/math/algebra/matrix/MatrixTypes.h"
#include "engine/core/math/algebra/vector/VectorAlgorithms.h"

namespace GLESC::Math {
    class MatrixMixedAlgorithms {
    public:
        // =============================================================================================================
        // ============================================ Matrix operations ==============================================
        // =============================================================================================================


        template <typename Type>
        static void
        rotate2D(const MatrixData<Type, 3, 3>& matrix, const Type dgrs, MatrixData<Type, 3, 3>& resMatrix) {
            MatrixData<Type, 3, 3> result =
            {
                {
                    {matrix[0][0], matrix[0][1], matrix[0][2]},
                    {matrix[1][0], matrix[1][1], matrix[1][2]},
                    {matrix[2][0], matrix[2][1], matrix[2][2]}
                }
            };
            Type c = cos(dgrs);
            Type s = sin(dgrs);

            MatrixData<Type, 3, 3> rotation =
            {
                {
                    {Type(c), Type(-s), Type(0)},
                    {Type(s), Type(c), Type(0)},
                    {Type(0), Type(0), Type(1)}
                }
            };

            MatrixAlgorithms::matrixMulDot(rotation, result, resMatrix);
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
        template <typename TypeToRotate, typename TypeDgrs, typename TypeRes>
        static void rotate3D(const MatrixData<TypeToRotate, 4, 4>& matrix,
                             const VectorData<TypeDgrs, 3>& dgrs,
                             MatrixData<TypeRes, 4, 4>& resMatrix) {
            MatrixData<TypeToRotate, 4, 4> result;
            MatrixAlgorithms::copyMatrix(result, matrix);

            TypeToRotate cx = cos(dgrs[0]); // X component
            TypeToRotate sx = sin(dgrs[0]); // X component
            TypeToRotate cy = cos(dgrs[1]); // Y component
            TypeToRotate sy = sin(dgrs[1]); // Y component
            TypeToRotate cz = cos(dgrs[2]); // Z component
            TypeToRotate sz = sin(dgrs[2]); // Z component


            // Combine the three rotation matrices into a single matrix
            MatrixData<TypeToRotate, 4, 4> rot = {
                {
                    {cy * cz, -cy * sz, sy, TypeToRotate(0)},
                    {sx * sy * cz + cx * sz, -sx * sy * sz + cx * cz, -sx * cy, TypeToRotate(0)},
                    {-cx * sy * cz + sx * sz, cx * sy * sz + sx * cz, cx * cy, TypeToRotate(0)},
                    {TypeToRotate(0), TypeToRotate(0), TypeToRotate(0), TypeToRotate(1)}
                }
            };

            MatrixAlgorithms::matrixMulDot(rot, result, resMatrix);
        }

        template <typename Type>
        static void lookAt2D(const MatrixData<Type, 3, 3>& matrix,
                             const VectorData<Type, 2>& target,
                             MatrixData<Type, 3, 3>& result) {
            VectorData<Type, 2> eye = {matrix[0][2], matrix[1][2]};
            VectorData<Type, 2> direction = {target[0] - eye[0], target[1] - eye[1]};

            if (VectorAlgorithms::eq(eye, target)) {
                // If the eye and target are the same, the result is the identity matrix
                MatrixAlgorithms::copyMatrix(result, matrix);
                return;
            }

            Type angle = -std::atan2(direction[1], direction[0]);

            // Assuming rotate2D accepts matrices as flat arrays
            rotate2D(matrix, angle, result);
        }

        template <typename Type>
        static void lookAt3D(const MatrixData<Type, 4, 4>& transformMatrix,
                             const VectorData<Type, 3>& targetPos,
                             const VectorData<Type, 3>& upVector,
                             MatrixData<Type, 4, 4>& resMatrix) {
            VectorData<Type, 3> eye = {transformMatrix[0][3], transformMatrix[1][3], transformMatrix[2][3]};
            MatrixMixedAlgorithms::lookAt3D(eye, targetPos, upVector, resMatrix);
        }

        template <typename TypeMat, typename TypeEye, typename TypeTarget, typename TypeUp>
        static void lookAt3D(const VectorData<TypeEye, 3>& eye,
                             const VectorData<TypeTarget, 3>& target,
                             const VectorData<TypeUp, 3>& up,
                             MatrixData<TypeMat, 4, 4>& resMatrix) {
            VectorData<TypeMat, 3> forward;
            VectorAlgorithms::vectorSub(target, eye, forward);
            VectorAlgorithms::normalize(forward, forward);

            VectorData<TypeMat, 3> right;
            VectorAlgorithms::crossProduct(forward, up, right);
            VectorAlgorithms::normalize(right, right);

            VectorData<TypeMat, 3> newUp;
            VectorAlgorithms::crossProduct(right, forward, newUp);
            VectorAlgorithms::normalize(newUp, newUp);

            resMatrix = {
                {
                    {right[0], newUp[0], -forward[0], TypeMat(0)},
                    {right[1], newUp[1], -forward[1], TypeMat(0)},
                    {right[2], newUp[2], -forward[2], TypeMat(0)},
                    {
                        -VectorAlgorithms::dotProduct(right, eye),
                        -VectorAlgorithms::dotProduct(newUp, eye),
                        -VectorAlgorithms::dotProduct(forward, eye),
                        TypeMat(1)
                    }
                }
            };
        }

        /**
         * @brief Calculate the model matrix from the position, rotation, and scale.
         * @details This function calculates the model matrix from the position, rotation, and scale.
         * The function applies the transformations in the following order: scale, rotation, and translation.
         * The function assumes a specific order of transformations, scale, then rotation, then translation.
         *
         * @tparam ModelType The data type of the matrix and vector elements (e.g., float, double).
         * @tparam TypePos The data type of the position vector elements (e.g., float, double).
         * @tparam TypeRot The data type of the rotation vector elements (e.g., float, double).
         * @tparam TypeScale The data type of the scale vector elements (e.g., float, double).
         * @param position A 3D vector containing the position of the model.
         * @param rotationRads A 3D vector containing the rotation angles (in radians) around X, Y, and Z axes
         * respectively.
         * @param scale A 3D vector containing the scale factors for the model.
         * @param model A 4x4 matrix which will contain the result of the model matrix.
         */
        template <typename ModelType, typename TypePos, typename TypeRot, typename TypeScale>
        static void
        calculateModelMatrix(const VectorData<TypePos, 3>& position,
                             const VectorData<TypeRot, 3>& rotationRads,
                             const VectorData<TypeScale, 3>& scale, MatrixData<ModelType, 4, 4>& model) {
            // Reset the model matrix to an identity matrix
            MatrixAlgorithms::setMatrixZero(model);
            MatrixAlgorithms::setMatrixDiagonal(model, ModelType(1));

            // First, apply scale to the model matrix
            MatrixAlgorithms::setScale(model, scale, model);

            // Then, apply rotation to the model matrix
            MatrixMixedAlgorithms::rotate3D(model, rotationRads, model);

            // Finally, apply translation to the model matrix
            MatrixAlgorithms::setTranslate(model, position, model);
        }


        template <typename TypeRes, typename TypePos, typename TypeRot>
        static void calculateViewMatrix(const VectorData<TypePos, 3>& position,
                                        const VectorData<TypeRot, 3>& rotation,
                                        MatrixData<TypeRes, 4, 4>& view) {
            // Calculate the rotation matrix for camera's inverse orientation
            MatrixData<TypeRes, 4, 4> rotationMatrix;
            MatrixAlgorithms::setMatrixZero(rotationMatrix);
            MatrixAlgorithms::setMatrixDiagonal(rotationMatrix, TypeRes(1));
            MatrixMixedAlgorithms::rotate3D(rotationMatrix, rotation, rotationMatrix);

            // Calculating the inverse position
            VectorData<TypeRes, 3> inversePosition;
            VectorAlgorithms::vectorNegate(position, inversePosition);

            // Calculate the translation matrix for the inverse position
            MatrixData<TypeRes, 4, 4> translationMatrix;
            MatrixAlgorithms::setMatrixZero(translationMatrix);
            MatrixAlgorithms::setMatrixDiagonal(translationMatrix, TypeRes(1));
            MatrixAlgorithms::setTranslate(translationMatrix, inversePosition, translationMatrix);

            // Combine the rotation and translation matrices
            // Assuming matrixMulDot multiplies matrices correctly.
            MatrixAlgorithms::matrixMulDot(rotationMatrix, translationMatrix, view);
        }
    }; // class MatrixAlgorithms
}; // namespace GLESC::Math
