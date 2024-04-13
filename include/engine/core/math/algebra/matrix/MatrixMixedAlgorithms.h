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
        template <typename Type, size_t N>
        static void
        matrixToVector(const MatrixData<Type, N, 1>& matrix, VectorData<Type, N>& vector) {
            for (size_t i = 0; i < N; ++i) {
                vector[i] = matrix[i][0];
            }
        }


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
            Type c = Math::cos(dgrs);
            Type s = Math::sin(dgrs);

            MatrixData<Type, 3, 3> rotation =
            {
                {
                    {Type(c), Type(-s), Type(0)},
                    {Type(s), Type(c), Type(0)},
                    {Type(0), Type(0), Type(1)}
                }
            };

            MatrixAlgorithms::matrixMatrixMul(rotation, result, resMatrix);
        }

        /**
         * @brief Rotate a 3D matrix around the X, Y, and Z axis.
         * @details This function applies sequential rotations to the input matrix based on the given angles.
         * The function assumes a specific order of rotations. It is Z, then Y, then X
         * TODO: Be cautious about gimbal lock when using Euler angles.
         *   It's recommended to use quaternions for robustness.
         * @tparam TypeToRotate The data type of the input matrix elements (e.g., float, double).
         * @tparam TypeDgrs The data type of the rotation angles (e.g., float, double).
         * @tparam TypeRes The data type of the result matrix elements (e.g., float, double).
         * @param matrix A 4x4 matrix to rotate.
         * @param angleDegrees A 3D vector containing the rotation angles around the X, Y, and Z axes respectively.
         * @param resMatrix A 4x4 matrix which will contain the result of the rotation.
         */
        template <typename TypeToRotate, typename TypeDgrs, typename TypeRes>
        static void rotate3D(const MatrixData<TypeToRotate, 4, 4>& matrix,
                             TypeDgrs angleDegrees,
                             const VectorData<TypeDgrs, 3>& axisVec,
                             MatrixData<TypeRes, 4, 4>& resMatrix) {
            TypeDgrs angleRadians = Math::radians(angleDegrees);
            TypeToRotate c = Math::cos(angleRadians);
            TypeToRotate s = Math::sin(angleRadians);

            // Normalized axis vector
            VectorData<TypeToRotate, 3> axis;
            VectorAlgorithms::normalize(axisVec, axis);

            VectorData<TypeToRotate, 3> temp;
            VectorAlgorithms::vectorScalarMul(axis, (TypeToRotate(1) - c), temp);

            MatrixData<TypeToRotate, 4, 4> rotate;
            rotate[0][0] = c + temp[0] * axis[0];
            rotate[0][1] = temp[0] * axis[1] + s * axis[2];
            rotate[0][2] = temp[0] * axis[2] - s * axis[1];
            rotate[0][3] = 0;

            rotate[1][0] = temp[1] * axis[0] - s * axis[2];
            rotate[1][1] = c + temp[1] * axis[1];
            rotate[1][2] = temp[1] * axis[2] + s * axis[0];
            rotate[1][3] = 0;

            rotate[2][0] = temp[2] * axis[0] + s * axis[1];
            rotate[2][1] = temp[2] * axis[1] - s * axis[0];
            rotate[2][2] = c + temp[2] * axis[2];
            rotate[2][3] = 0;

            rotate[3][0] = 0;
            rotate[3][1] = 0;
            rotate[3][2] = 0;
            rotate[3][3] = 1;

            // To ensure it can be done in place
            MatrixAlgorithms::matrixMatrixMulInPlace(rotate, matrix, resMatrix);
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

        /**
         * @brief Calculate the view matrix from the eye, target, and up vectors.
         * @details This function calculates the view matrix from the eye, target, and up vectors.
         * The function assumes a specific order of transformations, scale, then rotation, then translation.
         *
         * @tparam TypeMat The data type of the matrix elements (e.g., float, double).
         * @tparam TypeEye The data type of the eye vector elements (e.g., float, double).
         * @tparam TypeTarget The data type of the target vector elements (e.g., float, double).
         * @tparam TypeUp The data type of the up vector elements (e.g., float, double).
         * @param eye A 3D vector containing the position of the camera.
         * @param target A 3D vector containing the position of the target.
         * @param up A 3D vector containing the world's up direction. (usually {0, 1, 0})
         * @param resMatrix A 4x4 matrix which will contain the result of the view matrix.
         */
        template <typename TypeMat, typename TypeEye, typename TypeTarget, typename TypeUp>
        static void lookAt3D(const VectorData<TypeEye, 3>& eye,
                             const VectorData<TypeTarget, 3>& target,
                             const VectorData<TypeUp, 3>& up,
                             MatrixData<TypeMat, 4, 4>& resMatrix) {
            VectorData<TypeMat, 3> f;
            VectorAlgorithms::vectorSub(target, eye, f); // forward = target - eye
            VectorAlgorithms::normalize(f, f);

            VectorData<TypeMat, 3> s; // s = right
            VectorAlgorithms::crossProduct(f, up, s);
            VectorAlgorithms::normalize(s, s);

            VectorData<TypeMat, 3> u; // u = up
            VectorAlgorithms::crossProduct(s, f, u);

            resMatrix = {
                {
                    {s[0], u[0], -f[0], 0},
                    {s[1], u[1], -f[1], 0},
                    {s[2], u[2], -f[2], 0},
                    {
                        -VectorAlgorithms::dotProduct(s, eye),
                        -VectorAlgorithms::dotProduct(u, eye),
                        VectorAlgorithms::dotProduct(f, eye),
                        1
                    }
                }
            };
        }

        /**
         * @brief Calculate the model matrix from the position, rotation, and scale.
         * @details This function calculates the model matrix from the position, rotation, and scale.
         * The function applies the transformations in the following order: scale, rotation, and translation.
         * The function assumes a specific order of transformations, scale, then rotation, then translation.
         * As we're working with row-major matrices, the order of transformations is reversed.
         *
         * @tparam ModelType The data type of the matrix and vector elements (e.g., float, double).
         * @tparam TypePos The data type of the position vector elements (e.g., float, double).
         * @tparam TypeRot The data type of the rotation vector elements (e.g., float, double).
         * @tparam TypeScale The data type of the scale vector elements (e.g., float, double).
         * @param position A 3D vector containing the position of the model.
         * @param rotationDegrees A 3D vector containing the rotation angles (in radians) around X, Y, and Z axes
         * respectively.
         * @param scale A 3D vector containing the scale factors for the model.
         * @param model A 4x4 matrix which will contain the result of the model matrix.
         */
        template <typename ModelType, typename TypePos, typename TypeRot, typename TypeScale>
        static void calculateModelMatrix(const VectorData<TypePos, 3>& position,
                                         const VectorData<TypeRot, 3>& rotationDegrees,
                                         const VectorData<TypeScale, 3>& scale,
                                         MatrixData<ModelType, 4, 4>& model) {
            // Reset the model matrix to an identity matrix
            MatrixAlgorithms::setMatrixZero(model);
            MatrixAlgorithms::setMatrixDiagonal(model, ModelType(1));

            // First, apply translation to the model matrix
            MatrixAlgorithms::setTranslate(model, position, model);

            // Then, apply rotation to the model matrix
            MatrixMixedAlgorithms::rotate3D(model, rotationDegrees[0], {1, 0, 0}, model);
            MatrixMixedAlgorithms::rotate3D(model, rotationDegrees[1], {0, 1, 0}, model);
            MatrixMixedAlgorithms::rotate3D(model, rotationDegrees[2], {0, 0, 1}, model);

            // Finally, apply scale to the model matrix
            MatrixAlgorithms::setScale(model, scale, model);
        }

        template <typename ModelType, typename NormalMatType>
        static void calculateNormalMatrix(const MatrixData<ModelType, 4, 4>& MVMat,
                                          MatrixData<NormalMatType, 3, 3>& normalMat) {
            // Transpose the 4x4 matrix first
            MatrixData<ModelType, 4, 4> transposedMVMat;
            MatrixAlgorithms::transpose(MVMat, transposedMVMat);

            // Now extract the upper-left 3x3 part from the transposed matrix
            MatrixData<ModelType, 3, 3> resizedMVMat;
            MatrixAlgorithms::resizeMatrix(transposedMVMat, resizedMVMat);

            // Calculate the inverse of the 3x3 matrix
            MatrixData<ModelType, 3, 3> inverseMat;
            MatrixAlgorithms::inverse3x3(resizedMVMat, inverseMat);

            // Assign the result to normalMat, no further transpose needed as we already transposed the whole matrix
            normalMat = inverseMat;
        }


        template <typename Type>
        static void calculateViewMatrixEye(const VectorData<Type, 3>& eye,
                                           const VectorData<Type, 3>& target,
                                           const VectorData<Type, 3>& up,
                                           MatrixData<Type, 4, 4>& resMatrix) {
            MatrixMixedAlgorithms::lookAt3D(eye, target, up, resMatrix);
        }

        template <typename TypePos, typename TypeRot, typename TypeRes>
        static void calculateViewMatrixPosRot(const VectorData<TypePos, 3>& position,
                                              const VectorData<TypeRot, 3>& rotationDegrees,
                                              MatrixData<TypeRes, 4, 4>& resMatrix) {
            // Reset the result matrix to identity
            MatrixAlgorithms::setMatrixZero(resMatrix);
            MatrixAlgorithms::setMatrixDiagonal(resMatrix, TypeRes(1));

            VectorData<TypePos, 3> positionNeg;
            VectorAlgorithms::vectorNegate(position, positionNeg);

            // Apply rotation first
            MatrixMixedAlgorithms::rotate3D(resMatrix, rotationDegrees[0], {1, 0, 0}, resMatrix);
            MatrixMixedAlgorithms::rotate3D(resMatrix, rotationDegrees[1], {0, 1, 0}, resMatrix);
            MatrixMixedAlgorithms::rotate3D(resMatrix, rotationDegrees[2], {0, 0, 1}, resMatrix);

            // Then apply translation
            MatrixAlgorithms::setTranslate(resMatrix, position, resMatrix);
        }
    }; // class MatrixAlgorithms
}; // namespace GLESC::Math
