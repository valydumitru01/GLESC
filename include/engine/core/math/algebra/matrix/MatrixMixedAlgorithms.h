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


#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

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


        template<typename Type>
        static void
        rotate2D(const MatrixData<Type, 3, 3> &matrix, const Type dgrs, MatrixData<Type, 3, 3> &resMatrix) {
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
         * The function assumes a specific order of rotations. It is Z, then Y, then X
         * TODO: Be cautious about gimbal lock when using Euler angles.
         *   It's recommended to use quaternions for robustness.
         *
         * @param matrix The input 4x4 matrix that needs to be rotated.
         * @param dgrs A 3D vector containing the rotation angles (in radians) around X, Y, and Z axes
         * respectively.
         * @return A 4x4 matrix which is the result of the input matrix after the rotations.
         */
        template<typename TypeToRotate, typename TypeDgrs, typename TypeRes>
        static void rotate3D(const MatrixData<TypeToRotate, 4, 4> &matrix,
                             const VectorData<TypeDgrs, 3> &dgrs,
                             MatrixData<TypeRes, 4, 4> &resMatrix) {
            VectorData<TypeDgrs, 3> rads = {Math::radians(dgrs[0]), Math::radians(dgrs[1]), Math::radians(dgrs[2])};

            // Rotation matrices for X, Y, Z
            MatrixData<TypeToRotate, 4, 4> rotX = {
                {
                    {1, 0, 0, 0},
                    {0, cos(rads[0]), sin(rads[0]), 0},
                    {0, -sin(rads[0]), cos(rads[0]), 0},
                    {0, 0, 0, 1}
                }
            };

            MatrixData<TypeToRotate, 4, 4> rotY = {
                {
                    {cos(rads[1]), 0, -sin(rads[1]), 0},
                    {0, 1, 0, 0},
                    {sin(rads[1]), 0, cos(rads[1]), 0},
                    {0, 0, 0, 1}
                }
            };

            MatrixData<TypeToRotate, 4, 4> rotZ = {
                {
                    {cos(rads[2]), sin(rads[2]), 0, 0},
                    {-sin(rads[2]), cos(rads[2]), 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
                }
            };

            // Apply rotations in XYZ order
            MatrixData<TypeToRotate, 4, 4> combinedRotation;
            MatrixAlgorithms::setMatrixDiagonal(combinedRotation, TypeToRotate(1.0)); // Initialize with identity

            // Multiply in order: combinedRotation = rotZ * rotY * rotX
            MatrixAlgorithms::matrixMulDot(rotZ, combinedRotation, combinedRotation);
            MatrixAlgorithms::matrixMulDot(rotY, combinedRotation, combinedRotation);
            MatrixAlgorithms::matrixMulDot(rotX, combinedRotation, combinedRotation);

            // Apply the combined rotation to the input matrix
            MatrixAlgorithms::matrixMulDot(matrix, combinedRotation, resMatrix);
        }

        template<typename Type>
        static void lookAt2D(const MatrixData<Type, 3, 3> &matrix,
                             const VectorData<Type, 2> &target,
                             MatrixData<Type, 3, 3> &result) {
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

        template<typename Type>
        static void lookAt3D(const MatrixData<Type, 4, 4> &transformMatrix,
                             const VectorData<Type, 3> &targetPos,
                             const VectorData<Type, 3> &upVector,
                             MatrixData<Type, 4, 4> &resMatrix) {
            VectorData<Type, 3> eye = {transformMatrix[0][3], transformMatrix[1][3], transformMatrix[2][3]};
            MatrixMixedAlgorithms::lookAt3D(eye, targetPos, upVector, resMatrix);
        }

        template<typename TypeMat, typename TypeEye, typename TypeTarget, typename TypeUp>
        static void lookAt3D(const VectorData<TypeEye, 3> &eye,
                             const VectorData<TypeTarget, 3> &target,
                             const VectorData<TypeUp, 3> &up,
                             MatrixData<TypeMat, 4, 4> &resMatrix) {
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
        template<typename ModelType, typename TypePos, typename TypeRot, typename TypeScale>
        static void
        calculateModelMatrix(const VectorData<TypePos, 3> &position,
                             const VectorData<TypeRot, 3> &rotationRads,
                             const VectorData<TypeScale, 3> &scale,
                             MatrixData<ModelType, 4, 4> &model) {
            // Reset the model matrix to an identity matrix
            MatrixAlgorithms::setMatrixZero(model);
            MatrixAlgorithms::setMatrixDiagonal(model, ModelType(1));

            // Finally, apply translation to the model matrix
            MatrixAlgorithms::setTranslate(model, position, model);

            // Then, apply rotation to the model matrix
            MatrixMixedAlgorithms::rotate3D(model, rotationRads, model);

            // First, apply scale to the model matrix
            MatrixAlgorithms::setScale(model, scale, model);
        }


        template<typename TypeRight, typename TypeUp, typename TypeForw, typename TypePos, typename TypeRes>
        static void calculateViewMatrix(const VectorData<TypeRight, 3> &right,
                                        const VectorData<TypeUp, 3> &worldUp,
                                        const VectorData<TypeForw, 3> &forward,
                                        const VectorData<TypePos, 3> &position,
                                        MatrixData<TypeRes, 4, 4> &view) {
            TypeRes dotPosRight = -VectorAlgorithms::dotProduct(position, right);
            TypeRes dotPosUp = -VectorAlgorithms::dotProduct(position, worldUp);
            TypeRes dotPosForward = -VectorAlgorithms::dotProduct(position, forward);

            view = {
                {
                    {right[0], right[1], right[2], dotPosRight},
                    {worldUp[0], worldUp[1], worldUp[2], dotPosUp},
                    {-forward[0], -forward[1], -forward[2], dotPosForward},
                    {TypeRes(0), TypeRes(0), TypeRes(0), TypeRes(1)}
                }
            };
        }
    }; // class MatrixAlgorithms
}; // namespace GLESC::Math
