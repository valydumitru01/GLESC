/**************************************************************************************************
 * @file   MatrixAlgorithms.h
 * @author Valentin Dumitru
 * @date   23/01/2024
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <map>
#include <tuple>
#include <vector>
#include "engine/core/asserts/Asserts.h"
#include "engine/core/exceptions/core/math/MathException.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/algebra/matrix/MatrixTypes.h"
#include "engine/core/math/algebra/vector/VectorTypes.h"

namespace GLESC::Math {
    class MatrixAlgorithms {
    public:
        // =============================================================================================================
        // ========================================= Matrix data movement ==============================================
        // =============================================================================================================
        /**
         * @brief Resizes a matrix.
         * @details Resizes a matrix to a new size. The new matrix will have the same values as the original matrix.
         * But the new matrix will have the new size. If the new size is smaller than the original matrix, the values
         * will be truncated. If the new size is larger than the original matrix, the new values will be set to zero.
         * @tparam Type1 The data type of the matrix elements (e.g., float, double).
         * @tparam N1 The number of rows of the original matrix.
         * @tparam M1 The number of columns of the original matrix.
         * @tparam Type2 The data type of the new matrix elements (e.g., float, double).
         * @tparam N2 The number of rows of the new matrix.
         * @tparam M2 The number of columns of the new matrix.
         * @param matrix The original matrix.
         * @param result The new matrix.
         */
        template <typename Type1, size_t N1, size_t M1, typename Type2, size_t N2, size_t M2>
        static void resizeMatrix(const MatrixData<Type1, N1, M1>& matrix, MatrixData<Type2, N2, M2>& result) {
            for (size_t i = 0; i < N2; ++i) {
                for (size_t j = 0; j < M2; ++j) {
                    // Check if current indices are within the bounds of the original matrix
                    if (i < N1 && j < M1) {
                        // Safe to copy from the original matrix
                        result[i][j] = static_cast<Type2>(matrix[i][j]);
                    }
                    else {
                        // Outside the bounds of the original matrix, fill with zeroes
                        result[i][j] = static_cast<Type2>(0);
                    }
                }
            }
        }

        template <typename Type, size_t N, size_t M>
        static void swapRows(MatrixData<Type, N, M>& matrix, size_t row1, size_t row2) {
            for (size_t i = 0; i < M; ++i) {
                std::swap(matrix[row1][i], matrix[row2][i]);
            }
        }

        // =============================================================================================================
        // =================================================== Matrix Init =============================================
        // =============================================================================================================

        template <typename Type, size_t N, size_t M>
        static void setMatrixZero(MatrixData<Type, N, M>& matrixObjective) {
            MatrixAlgorithms::fillMatrix(matrixObjective, Type(0));
        }

        template <typename Type, size_t N, size_t M>
        static void fillMatrix(MatrixData<Type, N, M>& matrixObjective, const Type& value) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    matrixObjective[i][j] = value;
        }

        template <typename Type, size_t N, size_t M>
        static void setMatrixDiagonal(MatrixData<Type, N, M>& matrixObjective, const Type& value) {
            S_ASSERT_TRUE(N == M, "Matrix must be square.");
            for (size_t i = 0; i < N; ++i)
                matrixObjective[i][i] = value;
        }

        /**
         * @brief Sets the values of a matrix using a raw array.
         * @details Copies the values from the raw array into the matrix.
         * Works something like this:
         *      leftMat = rightMat;
         * @tparam Type1 The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows in the matrix.
         * @tparam M The number of columns in the matrix.
         * @param leftMat The matrix to be set.
         * @param rightMat The raw array containing the values to be copied into the matrix.
         */
        template <typename Type1, typename Type2, size_t N, size_t M>
        static void setMatrix(MatrixData<Type1, N, M>& leftMat, const MatrixData<Type2, N, M>& rightMat) {
            MatrixAlgorithms::copyMatrix(leftMat, rightMat);
        }

        template <typename Type, size_t N, size_t M>
        static void setMatrix(MatrixData<Type, N, M>& matrixObjective, const Type (&values)[N][M]) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    matrixObjective[i][j] = values[i][j];
        }

        template <typename Type1, typename Type2, size_t N, size_t M>
        static void copyMatrix(MatrixData<Type1, N, M>& matrixObjective,
                               const MatrixData<Type2, N, M>& matrixToCopy) {
            S_ASSERT_TRUE(std::is_copy_assignable_v<Type2>, "Type1 must be copy assignable.");
            S_ASSERT_TRUE((std::is_convertible_v<Type2, Type1>), "Type1 must be convertible from Type2.");

            // If the types are the same and the matrices are the same, do nothing
            if constexpr (std::is_same_v<Type1, Type2>) {
                if (&matrixObjective == &matrixToCopy)
                    return;
            }

            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    matrixObjective[i][j] = static_cast<Type1>(matrixToCopy[i][j]);
        }

        /**
         * @brief Moves the data from one matrix to another.
         * This function moves the data from the source matrix to the destination matrix.
         * If the source and destination matrices are the same, the function does nothing.
         *
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows in the matrix.
         * @tparam M The number of columns in the matrix.
         * @param matrixObjective The destination matrix where the data will be moved to.
         * @param matrixToMove The source matrix from which the data will be moved.
         */
        template <typename Type, size_t N, size_t M>
        static void moveMatrix(MatrixData<Type, N, M>& matrixObjective, MatrixData<Type, N, M>&& matrixToMove) {
            if (&matrixObjective == &matrixToMove)
                return;

            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    matrixObjective[i][j] = std::move(matrixToMove[i][j]);
        }

        /**
         * @brief Sets the values of a matrix using a rvalue raw array.
         * This function moves the data from the raw array to the matrix data.
         *
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows in the matrix.
         * @tparam M The number of columns in the matrix.
         * @param matrixObjective The matrix to be set.
         * @param values The rvalue raw array containing the values to be moved into the matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void setMatrix(MatrixData<Type, N, M>& matrixObjective, const Type (&&values)[N][M]) {
            if (&matrixObjective == &values)
                return;
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    matrixObjective[i][j] = std::move(values[i][j]);
        }


        // =============================================================================================================
        // ============================================ Arithmetic operations ==========================================
        // =============================================================================================================
        /**
         * @brief Adds two matrices.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrices.
         * @tparam M The number of columns of the matrices.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void matrixAdd(const MatrixData<Type, N, M>& matrix1,
                              const MatrixData<Type, N, M>& matrix2,
                              MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = matrix1[i][j] + matrix2[i][j];
        }

        /**
         * @brief Adds a scalar to a matrix.
         * @details Adds a scalar to each element of a matrix.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         * @param scalar The scalar.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void
        matrixScalarAdd(const MatrixData<Type, N, M>& matrix, const Type& scalar, MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = matrix[i][j] + scalar;
        }

        /**
         * @brief Multiplies two matrices.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrices.
         * @tparam M The number of columns of the matrices.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void matrixHadamardMul(const MatrixData<Type, N, M>& matrix1,
                                      const MatrixData<Type, N, M>& matrix2,
                                      MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = matrix1[i][j] * matrix2[i][j];
        }

        /**
         * @brief Multiplies a matrix by a scalar.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         * @param scalar The scalar.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void
        matrixScalarMul(const MatrixData<Type, N, M>& matrix, const Type& scalar, MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = matrix[i][j] * scalar;
        }

        /**
         * @brief Subtracts two matrices.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrices.
         * @tparam M The number of columns of the matrices.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void matrixSub(const MatrixData<Type, N, M>& matrix1,
                              const MatrixData<Type, N, M>& matrix2,
                              MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = matrix1[i][j] - matrix2[i][j];
        }


        /**
         * @brief Subtracts a scalar from a matrix.
         * @details Subtracts a scalar from each element of a matrix.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         * @param scalar The scalar.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void
        matrixScalarSub(const MatrixData<Type, N, M>& matrix, const Type& scalar, MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = matrix[i][j] - scalar;
        }

        /**
         * @brief Negates a matrix.
         * @details Negates each element of a matrix.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         * @return Negated matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void matrixNegate(const MatrixData<Type, N, M>& matrix, MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[i][j] = -matrix[i][j];
        }


        /**
         * @brief Divides two matrices. Hadamard division.
         * @details Divides all elements of the first matrix by the corresponding elements of the second matrix.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrices.
         * @tparam M The number of columns of the matrices.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void matrixHadamardDiv(const MatrixData<Type, N, M>& matrix1,
                                      const MatrixData<Type, N, M>& matrix2,
                                      MatrixData<Type, N, M>& result) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j) {
                    if (matrix2[i][j] == 0)
                        throw MathException("Division by zero is not allowed.");
                    result[i][j] = matrix1[i][j] / matrix2[i][j];
                }
        }

        /**
         * @brief Divides a matrix by a scalar.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         * @param scalar The scalar.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void
        matrixScalarDiv(const MatrixData<Type, N, M>& matrix, const Type& scalar, MatrixData<Type, N, M>& result) {
            if (scalar == 0)
                throw MathException("Division by zero is not allowed.");
            matrixScalarMul(matrix, Type(1) / scalar, result);
        }



        /**
         * @brief Dot product matrix multiplication. Uses Kahan summation algorithm.
         * @tparam Type The data type of the matrix and vector elements (e.g., float, double).
         * @tparam N The number of rows of the first matrix.
         * @tparam M The number of columns of the first matrix.
         * @tparam X The number of columns of the second matrix.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M, size_t X>
        static void matrixMatrixMul(const MatrixData<Type, N, M>& matrix1,
                             const MatrixData<Type, M, X>& matrix2,
                             MatrixData<Type, N, X>& result) {
            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < X; ++j) {
                    Type sum = static_cast<Type>(0);
                    Type c = static_cast<Type>(0); // A running compensation for lost low-order bits.
                    for (size_t k = 0; k < M; ++k) {
                        Type product = matrix1[i][k] * matrix2[k][j];
                        Type y = product - c;
                        Type t = sum + y;
                        c = (t - sum) - y;
                        sum = t;
                    }
                    result[i][j] = sum;
                }
            }
        }

        template <typename Type, size_t N, size_t M, size_t X>
        static void matrixMatrixMulNaive(const MatrixData<Type, N, M>& matrix1,
                                         const MatrixData<Type, M, X>& matrix2,
                                         MatrixData<Type, N, X>& result) {
            D_ASSERT_NOT_EQUAL(&matrix1, &result, "Cannot multiply matrix in place. Use matrixMatrixMulNaiveInPlace.");
            D_ASSERT_NOT_EQUAL(&matrix2, &result, "Cannot multiply matrix in place. Use matrixMatrixMulNaiveInPlace.");

            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < X; ++j) {
                    Type sum = 0;
                    for (size_t k = 0; k < M; ++k) {
                        sum += matrix1[i][k] * matrix2[k][j];
                    }
                    result[i][j] = sum;
                }
            }
        }


        /**
         * @brief Dot product matrix multiplication in place.
         * @details An in place method is needed because the normal matrix multiplication doesn't allow it without
         * making any copy. So this method is provieded but does make copy of the result.
         * @note Only makes sense for square matrices.
         * @tparam Type The data type of the matrix and vector elements (e.g., float, double).
         * @tparam N The number of rows of the first matrix.
         * @tparam M The number of columns of the first matrix.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void matrixMatrixMulInPlace(const MatrixData<Type, N, M>& matrix1,
                                           const MatrixData<Type, M, M>& matrix2,
                                           MatrixData<Type, N, M>& result) {
            MatrixData<Type, N, M> temp(result);
            matrixMatrixMul(matrix1, matrix2, temp);
            copyMatrix(result, temp);
        }

        template <typename Type, size_t N, size_t M>
        static void matrixMatrixMulNaiveInPlace(const MatrixData<Type, N, M>& matrix1,
                                                const MatrixData<Type, M, M>& matrix2,
                                                MatrixData<Type, N, M>& result) {
            MatrixData<Type, N, M> temp(result);
            matrixMatrixMulNaive(matrix1, matrix2, temp);
            copyMatrix(result, temp);
        }

        /**
         * @brief Matrix division.
         * @details Computes the inverse of the second matrix and multiplies it with the first matrix.
         * @tparam Type The data type of the matrix and vector elements (e.g., float, double).
         * @tparam N The number of rows of the first matrix.
         * @tparam M The number of columns of the first matrix.
         * @tparam X The number of columns of the second matrix.
         * @param matrix1 The first matrix.
         * @param matrix2 The second matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M, size_t X>
        static void matrixMatrixDiv(const MatrixData<Type, N, M>& matrix1,
                                    const MatrixData<Type, M, X>& matrix2,
                                    MatrixData<Type, N, X>& result) {
            Type det = MatrixAlgorithms::laplaceExpansionDeterminant(matrix2);
            if (Math::eq(det, 0))
                throw MathException("Matrix is not invertible.");
            MatrixData<Type, M, X> inverse;
            MatrixAlgorithms::matrixInverse(matrix2, inverse);
            MatrixData<Type, N, X> resultTemp;
            MatrixAlgorithms::matrixMatrixMul(matrix1, inverse, resultTemp);
            result = resultTemp;
        }

        /**
         * @brief Transposes a matrix.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N, size_t M>
        static void transpose(const MatrixData<Type, N, M>& matrix, MatrixData<Type, M, N>& result) {
            if constexpr (M == N)
                D_ASSERT_FALSE(&matrix == &result, "Cannot transpose matrix in place.");
            for (size_t i = 0; i < N; ++i)
                for (size_t j = 0; j < M; ++j)
                    result[j][i] = matrix[i][j]; // j,i becomes i,j, the numbers are mirrored
        }

        /**
         * @brief Transposes a matrix in place
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @tparam M The number of columns of the matrix.
         * @param matrix The matrix.
         */
        template <typename Type, size_t N>
        static void transposeInPlace(MatrixData<Type, N, N>& matrix) {
            for (size_t i = 0; i < N; ++i)
                for (size_t j = i + 1; j < N; ++j)
                    std::swap(matrix[i][j], matrix[j][i]);
        }

        /**
         * @brief Applies the translation to a model matrix.
         * @details The translation matrix is applied taking into account the matrix is in row major order.
         * @tparam TypeMat The data type of the matrix elements (e.g., float, double).
         * @tparam TypePos The data type of the translation vector elements (e.g., float, double).
         * @param translation The translation vector.
         * @param result The result matrix.
         */
        template <typename TypeMat, typename TypePos>
        static void getTranslationMatrix(const VectorData<TypePos, 3>& translation,
                                         MatrixData<TypeMat, 4, 4>& result) {
            // Create the translation matrix
            MatrixAlgorithms::setMatrixZero(result);
            MatrixAlgorithms::setMatrixDiagonal(result, TypeMat(1));

            result[3][0] = translation[0];
            result[3][1] = translation[1];
            result[3][2] = translation[2];
        }

        template <typename Type1, typename Type2, size_t N>
        static void getScaleMatrix(const VectorData<Type2, N - 1>& scale,
                                   MatrixData<Type1, N, N>& result) {
            static_assert(N == 3 || N == 4, "Scaling only makes sense for 3x3 and 4x4 matrices.");

            // Create the scale matrix
            MatrixAlgorithms::setMatrixZero(result);

            // Set the scale components on the matrix's diagonal
            for (size_t i = 0; i < N - 1; ++i) {
                result[i][i] = scale[i];
            }

            result[N - 1][N - 1] = Type1(1);
        }


        template <typename ModelType, typename NormalMatType>
        static void calculateNormalMatrix(const MatrixData<ModelType, 4, 4>& MVMat,
                                          MatrixData<NormalMatType, 3, 3>& normalMat) {
            // Calculate the inverse of the 3x3 matrix
            MatrixData<ModelType, 4, 4> inverseMat;
            MatrixAlgorithms::inverse4x4(MVMat, inverseMat);

            MatrixData<ModelType, 4, 4> transposedMVMat;
            MatrixAlgorithms::transpose(inverseMat, transposedMVMat);

            // Now extract the upper-left 3x3 part from the transposed matrix
            MatrixData<ModelType, 3, 3> resizedMVMat;
            MatrixAlgorithms::resizeMatrix(transposedMVMat, resizedMVMat);


            // Assign the result to normalMat, no further transpose needed as we already transposed the whole matrix
            normalMat = resizedMVMat;
        }

        template <typename Type>
        static bool isValidViewMatrix(const MatrixData<Type, 4, 4>& viewMatrix) {
            // The view matrix is valid if it is invertible
            return MatrixAlgorithms::isInvertible(viewMatrix);
        }

        template <typename Type, size_t N>
        static void
        inverse2x2(const MatrixData<Type, N, N>& matrix, MatrixData<Type, N, N>& result) {
            Type determinant;
            MatrixAlgorithms::determinant2x2(matrix, determinant);
            D_ASSERT_TRUE(MatrixAlgorithms::isInvertible(matrix), "Matrix is not invertible.");
            D_ASSERT_FALSE(&matrix == &result, "Cannot invert matrix in place.");
            result[0][0] = matrix[1][1] / determinant;
            result[0][1] = -matrix[0][1] / determinant;
            result[1][0] = -matrix[1][0] / determinant;
            result[1][1] = matrix[0][0] / determinant;
        }

        /**
         * @brief Calculates the perspective projection matrix.
         * @details Calculates the perspective projection matrix given the field of view, aspect ratio, near and far
         * planes. The fov must be in radians, on the contrary the result will be incorrect.
         * @cite https://www.songho.ca/opengl/gl_projectionmatrix.html
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @param fovRad The field of view in radians.
         * @param nearPlane The near plane.
         * @param farPlane The far plane.
         * @param viewWidth The width of the view.
         * @param viewHeight The height of the view.
         * @param result The result matrix.
         */
        template <typename Type>
        static void perspective(float fovRad,
                                float nearPlane,
                                float farPlane,
                                float viewWidth,
                                float viewHeight,
                                MatrixData<Type, 4, 4>& result) {
            S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic.");
            D_ASSERT_TRUE(farPlane > nearPlane, "Far must be greater than near.");
            D_ASSERT_TRUE(nearPlane > 0, "Near must be greater than 0.");
            D_ASSERT_TRUE(viewWidth > 0, "View width must be greater than 0.");
            D_ASSERT_TRUE(viewHeight > 0, "View height must be greater than 0.");
            D_ASSERT_TRUE(fovRad > 0, "Field of view must be greater than 0.");
            /*
            Type aspect = viewWidth / viewHeight;

            Type tangent = Math::tan(fovRad / Type(2));
            Type right = nearPlane * tangent;
            Type top = right / aspect;

            MatrixAlgorithms::setMatrixZero(result);
            result[0][0] = nearPlane / right;
            result[1][1] = nearPlane / top;
            result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            result[2][3] = -Type(1);
            result[3][2] = -(Type(2) * farPlane * nearPlane) / (farPlane - nearPlane);
            // result[3][3] = 0; // Already set to 0*/
            MatrixAlgorithms::setMatrixZero(result);
            Type const tanHalfFovy = Math::tan(fovRad / static_cast<Type>(2));
            Type aspect = viewWidth / viewHeight;
            result[0][0] = static_cast<Type>(1) / (aspect * tanHalfFovy);
            result[1][1] = static_cast<Type>(1) / (tanHalfFovy);
            result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            result[2][3] = -static_cast<Type>(1);
            result[3][2] = -(static_cast<Type>(2) * farPlane * nearPlane) / (farPlane - nearPlane);
        }

        /**
         * @brief Calculates the perspective projection matrix.
         * @details Calculates the perspective projection matrix given the field of view, aspect ratio, near and far
         * planes. The fov must be in degrees, on the contrary the result will be incorrect.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @param fovDegrees The field of view in degrees.
         * @param nearPlane The near plane.
         * @param farPlane The far plane.
         * @param viewWidth The width of the view.
         * @param viewHeight The height of the view.
         * @param projection The result matrix.
         */
        template <typename Type>
        static void
        calculateProjectionMatrix(float fovDegrees,
                                  float nearPlane,
                                  float farPlane,
                                  float viewWidth,
                                  float viewHeight,
                                  MatrixData<Type, 4, 4>& projection) {
            MatrixAlgorithms::perspective(radians(fovDegrees), nearPlane, farPlane, viewWidth, viewHeight, projection);
        }

        template <typename Type, size_t N>
        static void
        inverse3x3(const MatrixData<Type, N, N>& matrix, MatrixData<Type, N, N>& result) {
            Type determinant;
            MatrixAlgorithms::determinant3x3(matrix, determinant);
            D_ASSERT_TRUE(MatrixAlgorithms::isInvertible(matrix), "Matrix is not invertible.");
            D_ASSERT_FALSE(&matrix == &result, "Cannot invert matrix in place.");
            result[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) / determinant;
            result[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / determinant;
            result[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / determinant;
            result[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / determinant;
            result[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / determinant;
            result[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) / determinant;
            result[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) / determinant;
            result[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) / determinant;
            result[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / determinant;
        }

        /**
         * @brief Inverts a 4x4 matrix.
         * @details Calcutes the inverse matrix of the left parameter and stores it in the result
         * Can't be done in place, matrix and result must reference different objects.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @tparam N The number of rows of the matrix.
         * @param matrix The matrix.
         * @param result The result matrix.
         */
        template <typename Type, size_t N>
        static void
        inverse4x4(const MatrixData<Type, N, N>& matrix, MatrixData<Type, N, N>& result) {
            Type determinant;
            MatrixAlgorithms::determinant4x4(matrix, determinant);
            D_ASSERT_TRUE(MatrixAlgorithms::isInvertible(matrix), "Matrix is not invertible.");
            D_ASSERT_FALSE(&matrix == &result, "Cannot invert matrix in place.");
            Type A2323 = matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2];
            Type A1323 = matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1];
            Type A1223 = matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1];
            Type A0323 = matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0];
            Type A0223 = matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0];
            Type A0123 = matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0];
            Type A2313 = matrix[1][2] * matrix[3][3] - matrix[1][3] * matrix[3][2];
            Type A1313 = matrix[1][1] * matrix[3][3] - matrix[1][3] * matrix[3][1];
            Type A1213 = matrix[1][1] * matrix[3][2] - matrix[1][2] * matrix[3][1];
            Type A2312 = matrix[1][2] * matrix[2][3] - matrix[1][3] * matrix[2][2];
            Type A1312 = matrix[1][1] * matrix[2][3] - matrix[1][3] * matrix[2][1];
            Type A1212 = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
            Type A0313 = matrix[1][0] * matrix[3][3] - matrix[1][3] * matrix[3][0];
            Type A0213 = matrix[1][0] * matrix[3][2] - matrix[1][2] * matrix[3][0];
            Type A0312 = matrix[1][0] * matrix[2][3] - matrix[1][3] * matrix[2][0];
            Type A0212 = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0];
            Type A0113 = matrix[1][0] * matrix[3][1] - matrix[1][1] * matrix[3][0];
            Type A0112 = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];

            Type invDet = 1.0 / determinant;

            result[0][0] = invDet * (matrix[1][1] * A2323 - matrix[1][2] * A1323 + matrix[1][3] * A1223);
            result[0][1] = invDet * -(matrix[0][1] * A2323 - matrix[0][2] * A1323 + matrix[0][3] * A1223);
            result[0][2] = invDet * (matrix[0][1] * A2313 - matrix[0][2] * A1313 + matrix[0][3] * A1213);
            result[0][3] = invDet * -(matrix[0][1] * A2312 - matrix[0][2] * A1312 + matrix[0][3] * A1212);
            result[1][0] = invDet * -(matrix[1][0] * A2323 - matrix[1][2] * A0323 + matrix[1][3] * A0223);
            result[1][1] = invDet * (matrix[0][0] * A2323 - matrix[0][2] * A0323 + matrix[0][3] * A0223);
            result[1][2] = invDet * -(matrix[0][0] * A2313 - matrix[0][2] * A0313 + matrix[0][3] * A0213);
            result[1][3] = invDet * (matrix[0][0] * A2312 - matrix[0][2] * A0312 + matrix[0][3] * A0212);
            result[2][0] = invDet * (matrix[1][0] * A1323 - matrix[1][1] * A0323 + matrix[1][3] * A0123);
            result[2][1] = invDet * -(matrix[0][0] * A1323 - matrix[0][1] * A0323 + matrix[0][3] * A0123);
            result[2][2] = invDet * (matrix[0][0] * A1313 - matrix[0][1] * A0313 + matrix[0][3] * A0113);
            result[2][3] = invDet * -(matrix[0][0] * A1312 - matrix[0][1] * A0312 + matrix[0][3] * A0112);
            result[3][0] = invDet * -(matrix[1][0] * A1223 - matrix[1][1] * A0223 + matrix[1][2] * A0123);
            result[3][1] = invDet * (matrix[0][0] * A1223 - matrix[0][1] * A0223 + matrix[0][2] * A0123);
            result[3][2] = invDet * -(matrix[0][0] * A1213 - matrix[0][1] * A0213 + matrix[0][2] * A0113);
            result[3][3] = invDet * (matrix[0][0] * A1212 - matrix[0][1] * A0212 + matrix[0][2] * A0112);
        }

        template <typename Type, size_t N, typename = std::enable_if_t<N == 2 || N == 3 || N == 4>>
        static void
        matrixInverse(const MatrixData<Type, N, N>& matrix, MatrixData<Type, N, N>& result) {
            if constexpr (N == 2) {
                MatrixAlgorithms::inverse2x2(matrix, result);
            }
            else if constexpr (N == 3) {
                MatrixAlgorithms::inverse3x3(matrix, result);
            }
            else if constexpr (N == 4) {
                MatrixAlgorithms::inverse4x4(matrix, result);
            }
            else {
                // TODO: Implement general inverse
                //result = MatrixAlgorithms::gaussianElimination(matrix).inverse;
            }
        }

        template <typename Type, size_t N>
        static bool isInvertible(const MatrixData<Type, N, N>& matrix) {
            Type determinant = MatrixAlgorithms::laplaceExpansionDeterminant(matrix);
            return !Math::eq(determinant, 0);
        }


        template <typename Type>
        static void determinant2x2(const MatrixData<Type, 2, 2>& matrix, Type& result) {
            result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        /**
         * @brief Computes the determinant of a matrix 3x3.
         * @details Computes the determinant of a matrix using Laplace expansion.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @param matrix The matrix.
         * @param result The result determinant.
         */
        template <typename Type>
        static void determinant3x3(const MatrixData<Type, 3, 3>& matrix, Type& result) {
            result = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        }

        /**
         * @brief Computes the determinant of a matrix 4x4.
         * @details Computes the determinant of a matrix using Laplace expansion.
         * @tparam Type The data type of the matrix elements (e.g., float, double).
         * @param matrix The matrix.
         * @param result The result determinant.
         */
        template <typename Type>
        static void determinant4x4(const MatrixData<Type, 4, 4>& matrix, Type& result) {
            result = matrix[0][0] * (matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) -
                matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) +
                matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]));

            result -= matrix[0][1] * (matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) -
                matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]));

            result += matrix[0][2] * (matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) -
                matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));

            result -= matrix[0][3] * (matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]) -
                matrix[1][1] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]) +
                matrix[1][2] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));
        }


        template <typename Type, size_t N, size_t M>
        struct GaussianEliminationData {
            GaussianEliminationData(const MatrixData<Type, N, M>& inverse, unsigned int rank, Type determinant) :
                inverse(inverse), rank(rank), determinant(determinant) {
            }

            MatrixData<Type, N, M> inverse;
            unsigned int rank;
            Type determinant;
        };

        /**
         * @brief Performs Gaussian elimination on a matrix. @TODO: Make this work (doesn't work for some reason)
         * @tparam Type
         * @tparam N
         * @tparam M
         * @param matrix
         * @return
         */
        template <typename Type, size_t N, size_t M>
        static GaussianEliminationData<Type, N, M>
        gaussianElimination(const MatrixData<Type, N, M>& matrix) {
            MatrixData<Type, N, M * 2> augmentedMatrix;
            MatrixData<Type, N, M> identityMatrix;
            MatrixData<Type, N, M> inverseResult;

            // Initialize identity matrix
            MatrixAlgorithms::setMatrixDiagonal(identityMatrix, Type(1));


            // Augment the original matrix with identity matrix
            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < M; ++j) {
                    augmentedMatrix[i][j] = matrix[i][j];
                    augmentedMatrix[i][N + j] = identityMatrix[i][j];
                }
            }

            // Perform Gaussian elimination on the augmented matrix
            auto result = gaussianEliminationAlgorithm(augmentedMatrix);

            // Extract the inverse matrix from the augmented matrix
            for (size_t i = 0; i < N; i++) {
                for (size_t j = 0; j < M; j++) {
                    inverseResult[i][j] = augmentedMatrix[i][j + M];
                }
            }

            // Extract the rank of the matrix
            // Rank is the number of non-zero rows in the matrix
            unsigned int rank = 0;
            for (size_t i = 0; i < N; ++i) {
                bool isZeroRow = true;
                for (size_t j = 0; j < N; ++j) {
                    if (augmentedMatrix[i][j] != 0) {
                        isZeroRow = false;
                        break;
                    }
                }
                if (!isZeroRow)
                    ++rank;
            }

            // Extract the determinant of the matrix
            // Determinant is the product of diagonal entries of the matrix
            // Also, the result must be multiplied by -1 if the number of row swaps is odd
            Type determinant = Type(1);
            for (size_t i = 0; i < N; ++i) {
                determinant *= augmentedMatrix[i][i];
            }

            bool isRowSwapOdd = result.rowSwaps.size() % 2 == 1;
            determinant *= isRowSwapOdd ? Type(-1) : Type(1);

            GaussianEliminationData<Type, N, M> extractedData(inverseResult, rank, determinant);
            return extractedData;
        }


        template <class Type, size_t N>
        static Type laplaceExpansionDeterminant(const MatrixData<Type, N, N>& matrix) {
            if constexpr (N == 1) {
                return matrix[0][0];
            }
            else if constexpr (N == 2) {
                Type det;
                MatrixAlgorithms::determinant2x2(matrix, det);
                return det;
            }
            else if constexpr (N == 3) {
                Type det;
                MatrixAlgorithms::determinant3x3(matrix, det);
                return det;
            }
            else if constexpr (N == 4) {
                Type det;
                MatrixAlgorithms::determinant4x4(matrix, det);
                return det;
            }
            else {
                Type result = Type();
                Type sign = 1;

                for (size_t j = 0; j < N; ++j) {
                    result += sign * matrix[0][j] * cofactor(matrix, Type(0), j);
                    sign = -sign; // Alternate sign for cofactor expansion
                }
                return result;
            }
        }

    private:
        template <typename Type, size_t N, size_t M>
        struct GaussianEliminationTrackedResult {
            MatrixData<Type, N, M> resultMatrix;
            std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> rowSwaps;
            std::vector<std::tuple<size_t, size_t, Type>> rowMultipleAdditions;
            std::vector<std::pair<size_t, Type>> rowMultiplications;
        };

        template <typename Type, size_t N, size_t M>
        static GaussianEliminationTrackedResult<Type, N, M>
        gaussianEliminationAlgorithm(const MatrixData<Type, N, M>& inputMatrix) {
            GaussianEliminationTrackedResult<Type, N, M> trackedResult;

            // Copy input matrix to result matrix
            copyMatrix(trackedResult.resultMatrix, inputMatrix);

            // Perform Gaussian elimination with partial pivoting
            for (size_t i = 0; i < std::min(N, M); ++i) {
                // Search for maximum in this column
                size_t maxRow = i;
                Type maxElem = std::fabs(trackedResult.resultMatrix[i][i]);
                for (size_t k = i + 1; k < N; ++k) {
                    Type absValue = std::fabs(trackedResult.resultMatrix[k][i]);
                    if (absValue > maxElem) {
                        maxElem = absValue;
                        maxRow = k;
                    }
                }

                // Check for zero pivot value (potential singularity)
                if (maxElem == Type(0)) {
                    throw std::runtime_error("Singular matrix, no unique solution exists.");
                }

                // Swap maximum row with current row (column by column)
                if (i != maxRow) {
                    swapRows(trackedResult.resultMatrix, i, maxRow);
                    trackedResult.rowSwaps[{i, maxRow}] = {maxRow, i};
                }


                // Make all rows below this one 0 in current column
                for (size_t k = i + 1; k < N; ++k) {
                    Type c = -trackedResult.resultMatrix[k][i] / trackedResult.resultMatrix[i][i];
                    for (size_t j = i; j < M; ++j) {
                        if (i == j) {
                            trackedResult.resultMatrix[k][j] = 0;
                        }
                        else {
                            trackedResult.resultMatrix[k][j] += c * trackedResult.resultMatrix[i][j];
                        }
                    }
                    trackedResult.rowMultipleAdditions.push_back({k, i, c});
                }
            }

            // Back-substitution (if the system is square and N == M)
            if (N == M) {
                for (size_t i = N; i-- > 0;) {
                    Type sum = trackedResult.resultMatrix[i][N];
                    for (size_t j = i + 1; j < N; ++j) {
                        sum -= trackedResult.resultMatrix[i][j] * trackedResult.resultMatrix[j][N];
                    }
                    trackedResult.resultMatrix[i][N] = sum / trackedResult.resultMatrix[i][i];
                    trackedResult.rowMultiplications.push_back({i, 1 / trackedResult.resultMatrix[i][i]});
                }
            }

            return trackedResult;
        }

        template <class Type, size_t N>
        static inline Type cofactor(const MatrixData<Type, N, N>& matrix, size_t row, size_t col) {
            MatrixData<Type, N - 1, N - 1> subMatrix;

            size_t subI = 0;
            for (size_t i = 0; i < N; ++i) {
                if (i == row)
                    continue;

                size_t subJ = 0;
                for (size_t j = 0; j < N; ++j) {
                    if (j == col)
                        continue;

                    subMatrix[subI][subJ] = matrix[i][j];
                    subJ++;
                }
                subI++;
            }

            return laplaceExpansionDeterminant(subMatrix);
        }
    }; // class MatrixBasicAlgorithms
} // namespace GLESC::Math
