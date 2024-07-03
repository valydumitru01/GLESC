/******************************************************************************
 * @file   Matrix.h
 * @author Valentin Dumitru
 * @date   2023-10-03
 * @brief  * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cmath>
#include <algorithm>
#include <engine/core/asserts/Asserts.h>

#include "engine/core/exceptions/core/math/MathException.h"
#include "engine/core/math/algebra/matrix/MatrixMixedAlgorithms.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "MatrixAlgorithms.h"

namespace GLESC::Math {
    /**
     * @brief Matrix class. Represents a matrix of N rows and M columns.
     * @details This matrix is row-major.
     * @tparam Type The type of the elements in the matrix
     * @tparam N The number of rows in the matrix
     * @tparam M The number of columns in the matrix
     */
    template <typename Type, size_t N, size_t M>
    class Matrix {
        S_ASSERT_TRUE(N > 0 && M > 0, "Matrix must have at least one row and one column.");

    public:
        // =========================================================================================
        // ======================================= Constructors ====================================
        // =========================================================================================
        /**
         * @brief Constructs a matrix with all elements set to zero.
         */
        Matrix() {
            MatrixAlgorithms::setMatrixZero(this->data);
        }
        /**
         * @brief Constructs a matrix with the diagonal elements set to the given value.
         * @param diagonal The value to set the diagonal elements to.
         */
        explicit Matrix(const Type diagonal) {
            MatrixAlgorithms::setMatrixDiagonal(this->data, diagonal);
        }

        /**
         * @brief Constructor array list of elements
         * @details The array list must have N * M elements
         * @param data
         */
        explicit Matrix(const Type (&data)[N][M]) {
            MatrixAlgorithms::setMatrix(this->data, data);
        }

        /**
         * @brief Constructor from a 2D array
         * @param other The 2D array to copy from
         */
        explicit Matrix(const MatrixData<Type, N, M>& other) {
            MatrixAlgorithms::setMatrix(this->data, other);
        }
        /**
         * @brief Constructor from MatrixData
         * @see MatrixData
         * @param other The 2D array to move from
         */
        explicit Matrix(const MatrixData<Type, N, M>&& other) {
            MatrixAlgorithms::setMatrix(this->data, other);
        }
        /**
         * @brief Constructor from another matrix
         * @param other The matrix to copy from
         */
        template <typename OtherType, size_t OtherN, size_t OtherM>
        explicit Matrix(const Matrix<OtherType, OtherN, OtherM>& other) {
            MatrixAlgorithms::resizeMatrix(other.data, this->data);
        }


        /**
         * @brief Copy constructor
         * @param other The matrix to copy from
         */
        Matrix(const Matrix& other) {
            MatrixAlgorithms::copyMatrix(this->data, other.data);
        }

        /**
         * @brief Move constructor
         * @param other The matrix to move from
         */
        Matrix(Matrix&& other) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, std::move(other.data));
        }


        // =========================================================================================
        // ========================================= Operators =====================================
        // =========================================================================================


        // ================================== Assignment Operators =================================

        /**
         * @brief Copy assignment operator.
         * @param other The matrix to copy from.
         * @return Reference to the modified instance.
         */
        template <typename OtherType>
        constexpr Matrix& operator=(const Matrix<OtherType, N, M>& other) noexcept {
            MatrixAlgorithms::copyMatrix(this->data, other.data);
            return *this;
        }
        /**
         * @brief Copy assignment operator for different size matrices.
         * @param other The matrix to copy from. Can be of different size.
         */
        template <typename OtherType, size_t OtherN, size_t OtherM>
        constexpr Matrix& operator=(const Matrix<OtherType, OtherN, OtherM>& other) noexcept {
            MatrixAlgorithms::resizeMatrix(this->data, other.data);
            return *this;
        }
        /**
         * @brief Copy assignment operator for MatrixData of different size.
         * @param other The matrix to copy from. Can be of different size.
         */
        template <typename OtherType, size_t OtherN, size_t OtherM>
        constexpr Matrix& operator=(const MatrixData<OtherType, OtherN, OtherM>&& other) noexcept {
            MatrixAlgorithms::resizeMatrix(this->data, other);
            return *this;
        }

        /**
         * @brief Copy assignment operator
         * @param other The matrix to copy from.
         */
        Matrix& operator=(const Matrix& other) noexcept {
            MatrixAlgorithms::copyMatrix(this->data, other.data);
            return *this;
        }


        constexpr Matrix& operator=(MatrixData<Type, N, M>&& other) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, std::move(other));
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * @param rhs The matrix to move from.
         * @return Reference to the modified instance.
         */
        constexpr Matrix& operator=(Matrix&& rhs) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, std::move(rhs.data));
            return *this;
        }

        /**
         * @brief Assignment operator from a 2D array.
         * @param data 2D array to assign from.
         * @return Reference to the modified instance.
         */
        constexpr Matrix& operator=(Type (&data)[N][M]) {
            MatrixAlgorithms::setMatrix(this->data, data);
            return *this;
        }

        /**
         * @brief In-place element-wise multiplication with another matrix.
         * @param rhs The matrix to multiply with.
         * @return Reference to the modified instance.
         */
        Matrix& operator*=(const Matrix& rhs) {
            S_ASSERT_TRUE(N == M, "Matrix must be square for in-place multiplication");
            MatrixAlgorithms::matrixMatrixMulInPlace(this->data, rhs.data, this->data);
            return *this;
        }

        /**
         * @brief In-place scalar multiplication.
         * @param scalar The scalar to multiply with.
         * @return Reference to the modified instance.
         */
        Matrix& operator*=(Type scalar) {
            MatrixAlgorithms::matrixScalarMul(this->data, scalar, data);
            return *this;
        }

        /**
         * @brief In-place scalar addition.
         * @param rhs The scalar to add.
         * @return Reference to the modified instance.
         */
        Matrix& operator+=(Type rhs) {
            MatrixAlgorithms::matrixScalarAdd(this->data, rhs, data);
            return *this;
        }

        /**
         * @brief In-place element-wise addition with another matrix.
         * @param rhs The matrix to add with.
         * @return Reference to the modified instance.
         */
        Matrix& operator+=(const Matrix& rhs) {
            MatrixAlgorithms::matrixAdd(this->data, rhs.data, data);
            return *this;
        }

        /**
         * @brief In-place element-wise subtraction with another matrix.
         * @param rhs The matrix to subtract with.
         * @return Reference to the modified instance.
         */
        Matrix& operator-=(const Matrix& rhs) {
            MatrixAlgorithms::matrixSub(this->data, rhs.data, data);
            return *this;
        }

        /**
         * @brief In-place scalar subtraction.
         * @param rhs The scalar to subtract.
         * @return Reference to the modified instance.
         */
        Matrix& operator-=(Type rhs) {
            MatrixAlgorithms::matrixScalarSub(this->data, rhs, data);
            return *this;
        }

        /**
         * @brief In-place scalar division.
         * @param scalar The scalar to divide by.
         * @return Reference to the modified instance.
         * @throws MathException if division by zero
         */
        Matrix& operator/=(Type scalar) {
            MatrixAlgorithms::matrixScalarDiv(this->data, scalar, data);
            return *this;
        }

        /**
         * @brief In-place division by another matrix.
         * @param rhs The matrix to divide by.
         * @return Reference to the modified instance.
         * @throws MathException if division by zero
         */
        Matrix& operator/=(const Matrix& rhs) {
            MatrixAlgorithms::matrixMatrixDiv(this->data, rhs.data, this->data);
            return *this;
        }

        // ================================== Arithmetic Operators =================================

        /**
         * @brief Adding two matrices, element-wise.
         * @param rhs The matrix to add
         * @return The result of the addition
         */
        [[nodiscard]] Matrix operator+(const Matrix& rhs) const {
            Matrix result;
            MatrixAlgorithms::matrixAdd(this->data, rhs.data, result.data);
            return result;
        }

        /**
         * @brief Adding a scalar to the matrix
         * @details Adds a scalar to each element of the matrix
         * @param scalar The scalar to add
         * @return The result of the addition
         */
        [[nodiscard]] Matrix operator+(Type scalar) const {
            Matrix result;
            MatrixAlgorithms::matrixScalarAdd(this->data, scalar, result.data);
            return result;
        }

        /**
         * @brief Subtracting two matrices, element-wise.
         * @param rhs The matrix to subtract
         * @return The result of the subtraction
         */
        [[nodiscard]] Matrix operator-(const Matrix& rhs) const {
            Matrix result;
            MatrixAlgorithms::matrixSub(this->data, rhs.data, result.data);
            return result;
        }

        /**
         * @brief Subtracting a scalar from the matrix
         * @details Subtracts a scalar from each element of the matrix
         * @param scalar The scalar to subtract
         * @return The result of the subtraction
         */
        [[nodiscard]] Matrix operator-(Type scalar) const {
            Matrix result;
            MatrixAlgorithms::matrixScalarSub(this->data, scalar, result.data);
            return result;
        }

        /**
         * @brief Negating the matrix
         * @details Negates each element of the matrix
         * @return The negated matrix
         */
        [[nodiscard]] Matrix operator-() const {
            Matrix result;
            MatrixAlgorithms::matrixScalarMul(this->data, Type(-1), result.data);
            return result;
        }

        /**
         * @brief Multiplying Matrix by Matrix
         * @details A matrix NxM multiplied by a matrix MxX results in a matrix N x X
         * For example:
         * | 1 2 3 |   | 7  8  |   | 58  64  |
         * | 4 5 6 | * | 9  10 | = | 139 154 |
         *             | 11 12 |
         * 2x3      *     3x2    =     2x2
         * @tparam X
         * @param other
         * @return
         */
        template <size_t X>
        [[nodiscard]] auto operator*(const Matrix<Type, X, N>& other) const {
            if constexpr (MatrixAlgorithms::columnMajorMatrix) {
                Matrix<Type, X, M> result;
                MatrixAlgorithms::matrixMatrixMulColMaj(this->data, other.data, result.data);
                return result;
            }
            else {
                Matrix<Type, N, X> result;
                MatrixAlgorithms::matrixMatrixMulRowMaj(other.data, this->data, result.data);
                return result;
            }
        }

        /**
         * @brief Multiplying Matrix by Vector
         * @details A matrix NxM multiplied by a vector M results in a vector N
         * For example:
         * | 1 2 3 |   | 7  |   | 58  |
         * | 4 5 6 | * | 9  | = | 139 |
         *             | 11 |
         * 2x3      *     3    =     2
         * @tparam X
         * @param other
         * @return
         */
        [[nodiscard]] Vector<Type, N> operator*(const Vector<Type, M>& other) const {
            Vector<Type, N> resultVector;
            if constexpr (MatrixAlgorithms::columnMajorMatrix) {
                MatrixAlgorithms::matrixVectorMulColMaj(this->data, other.data, resultVector.data);
            }
            else {
                MatrixAlgorithms::matrixVectorMulRowMaj(other.data, this->data, resultVector.data);
            }
            return resultVector;
        }

        /**
         * @brief Multiplying Matrix by scalar
         * @details Multiplies each element of the matrix by the scalar
         * @param scalar The scalar to multiply by
         * @return The result of the multiplication
         */
        [[nodiscard]] Matrix operator*(Type scalar) const {
            Matrix result;
            MatrixAlgorithms::matrixScalarMul(this->data, scalar, result.data);
            return result;
        }


        /**
         * @brief Division of matrix by scalar
         * @details Divides each element of the matrix by the scalar
         * @param scalar The scalar to divide by
         * @return The result of the division
         */
        [[nodiscard]] Matrix operator/(Type scalar) const {
            Matrix result;
            MatrixAlgorithms::matrixScalarDiv(this->data, scalar, result.data);
            return result;
        }


        /**
         * @brief Matrix division by matrix
         * @details The matrix division by matrix is defined as the multiplication of the first
         * matrix by the inverse of the second matrix
         * @param rhs
         * @return
         */
        template <size_t X>
        [[nodiscard]] Matrix operator/(const Matrix<Type, M, X>& rhs) const {
            Matrix result;
            MatrixAlgorithms::matrixMatrixDiv(this->data, rhs.data, result.data);
            return result;
        }

        // =============================================================================================================
        // ============================================== Access Operators =============================================
        // =============================================================================================================

        /**
         * @brief Access operator for the matrix, getters are always const
         * @param index The row index
         * @return The const row at the given index
         */
        [[nodiscard]] const std::array<Type, M>& operator[](size_t index) const {
            return data[index];
        }

        /**
         * @brief Access operator for the matrix
         * @param index The row index
         * @return The row at the given index
         */
        [[nodiscard]] std::array<Type, M>& operator[](size_t index) {
            return data[index];
        }

        /**
         * @brief Access operator for the matrix, getters are always const
         * @param i The row index
         * @param j The column index
         * @return The value at the given row and column
         */
        [[nodiscard]] const Type& get(size_t i, size_t j) const {
            return data[i][j];
        }

        /**
         * @brief Access operator for the matrix, getters are always const
         * @param i The row index
         * @return The const row at the given index
         */
        [[nodiscard]] const MatrixRow<Type, M>& get(size_t i) const {
            return data[i];
        }

        /**
         * @brief Get the number of rows in the matrix
         * @return The number of rows
         */
        [[nodiscard]] static size_t rows() {
            return N;
        }

        /**
         * @brief Get the number of columns in the matrix
         * @return The number of columns
         */
        [[nodiscard]] static size_t cols() {
            return M;
        }

        // =============================================================================================================
        // =========================================== Comparison Operators ============================================
        // =============================================================================================================

        /**
         * @brief Equality operator
         * @param rhs The matrix to compare with
         * @return True if the matrices are equal, false otherwise
         */
        [[nodiscard]] bool operator==(const Matrix& rhs) const {
            for (size_t i = 0; i < N; ++i) {
                for (size_t k = 0; k < M; ++k) {
                    if (!eq(this->data[i][k], rhs.data[i][k])) {
                        return false;
                    }
                }
            }
            return true;
        }

        /**
         * @brief Inequality operator
         * @param rhs The matrix to compare with
         * @return True if the matrices are not equal, false otherwise
         */
        [[nodiscard]] bool operator!=(const Matrix& rhs) const {
            return !(*this == rhs);
        }

        // =============================================================================================================
        // ============================================= Matrix Functions ==============================================
        // =============================================================================================================

        /**
         * @brief Transforms the matrix into a vector
         * @details Only works for matrices with one column
         * @details The matrix must have one column to be converted to a vector
         * @return The vector representation of the matrix
         */
        [[nodiscard]] Vector<Type, N> toVector() const {
            S_ASSERT_EQUAL(M, 1, "Matrix must have one column to be converted to a vector");
            Vector<Type, N> result;
            MatrixMixedAlgorithms::matrixToVector(this->data, result.data);
            return result;
        }

        /**
         * @brief Transposes the matrix
         * @details In a transposed matrix, the rows become columns and the columns become rows
         * @return The transposed matrix
         */
        [[nodiscard]] Matrix<Type, M, N> transpose() const {
            Matrix<Type, M, N> result;
            MatrixAlgorithms::transpose(this->data, result.data);
            return result;
        }

        // TODO: Check if this determinant is more efficient than gaussian elimination
        //   also, don't recalculate, store it
        /**
         * @brief Calculates the determinant of the matrix
         * @details The determinant is a value that can be calculated for square matrices only
         * @return The determinant of the matrix
         */
        [[nodiscard]] Type determinant() const {
            return MatrixAlgorithms::laplaceExpansionDeterminant(this->data);
        }
        /**
         * @brief Calculates the inverse of the matrix
         * @details The inverse of a matrix is a matrix that when multiplied with the original matrix
         * results in the identity M*M^-1 = I
         * @return The inverse of the matrix
         */
        [[nodiscard]] Matrix<Type, N, N> inverse() const {
            Matrix<Type, N, N> inv;
            MatrixAlgorithms::matrixInverse(this->data, inv.data);
            return inv;
        }

        /**
         * @brief Creates a model matrix from the given position, rotation and scale vectors.
         * @details This operation will overwrite the current matrix with the result of the model matrix
         * @tparam PosType The type of the position vector
         * @tparam RotType The type of the rotation vector
         * @tparam ScaleType The type of the scale vector
         * @param position The position vector
         * @param rotationRads The rotation vector
         * @param scale The scale vector
         */
        template <typename PosType, typename RotType, typename ScaleType>
        Matrix& makeModelMatrix(const Vector<PosType, 3>& position,
                             const Vector<RotType, 3>& rotationRads,
                             const Vector<ScaleType, 3>& scale) {
            S_ASSERT_TRUE(N == 4 && M == 4, "Model matrix can only be created for 4x4 matrices");
            MatrixMixedAlgorithms::calculateModelMatrix<Type, PosType, RotType, ScaleType>
                (position.data, rotationRads.data, scale.data, this->data);
            return *this;
        }

        /**
         * @brief Creates a translation matrix from the given position vector.
         * @details This operation will overwrite the current matrix with the result of the translation matrix
         * The translation matrix is a 4x4 matrix with the translation values in the last column
         * @tparam PosType The type of the position vector
         * @param position The position vector
         */
        template  <typename PosType>
        Matrix& makeTranslationMatrix(const Vector<PosType, 3>& position) {
            S_ASSERT_TRUE(N == 4 && M == 4, "Translation matrix can only be created for 4x4 matrices");
            MatrixAlgorithms::getTranslationMatrix<Type, PosType>(position.data, this->data);
            return *this;
        }

        /**
         * @brief Creates a rotation matrix from the given rotation vector.
         * @details This operation will overwrite the current matrix with the result of the rotation matrix
         * The rotation matrix is a 4x4 matrix with the rotation values in the upper left 3x3 matrix
         * @tparam RotType The type of the rotation vector
         * @param rotationRads The rotation vector
         */
        template <typename RotType>
        Matrix& makeRotationMatrix(const Vector<RotType, 3>& rotationRads) {
            S_ASSERT_TRUE(N == 4 && M == 4, "Rotation matrix can only be created for 4x4 matrices");
            MatrixMixedAlgorithms::getRotate3DMatrix<Type, RotType>(rotationRads.data, this->data);
            return *this;
        }

        /**
         * @brief Creates a scale matrix from the given scale vector.
         * @details This operation will overwrite the current matrix with the result of the scale matrix
         * The scale matrix is a 4x4 matrix with the scale values in the diagonal
         * @tparam ScaleType The type of the scale vector
         * @param scale The scale vector
         */
        template <typename ScaleType>
        Matrix& makeScaleMatrix(const Vector<ScaleType, 3>& scale) {
            S_ASSERT_TRUE(N == 4 && M == 4, "Scale matrix can only be created for 4x4 matrices");
            MatrixAlgorithms::getScaleMatrix<Type, ScaleType>(scale.data, this->data);
            return *this;
        }

        /**
         * @brief Creates a normal matrix from the given model-view matrix.
         * @details This operation will overwrite the current matrix with the result of the normal matrix
         * The normal matrix is a 3x3 matrix that is the inverse transpose of the model-view matrix
         * @tparam ModelType The type of the model-view matrix
         * @param MVMat The model-view matrix
         */
        template <typename ModelType>
        Matrix& makeNormalMatrix(const Matrix<ModelType, 4, 4>& MVMat) {
            S_ASSERT_TRUE(N == 3 && M == 3, "Normal matrix can only be created for 4x4 matrices");
            MatrixAlgorithms::calculateNormalMatrix(MVMat.data, this->data);
            return *this;
        }

        /**
         * @brief Creates a view matrix from the given position, rotation and scale vectors.
         * @details This operation will overwrite the current matrix with the result of the view matrix
         * @param eye The position of the camera
         * @param target The target of the camera
         * @param up The up vector of the camera
         */
        Matrix& makeViewMatrixEye(const Vector<Type, 3>& eye,
                               const Vector<Type, 3>& target,
                               const Vector<Type, 3>& up) {
            S_ASSERT_TRUE(N == 4 && M == 4, "View matrix can only be created for 4x4 matrices");
            MatrixMixedAlgorithms::calculateViewMatrixEye(eye.data, target.data, up.data, data);
            return *this;
        }

        /**
         * @brief Creates a view matrix from the given position and rotation vectors.
         * @details This operation will overwrite the current matrix with the result of the view matrix
         * @param position The position of the camera
         * @param rotation The rotation of the camera
         */
        Matrix& makeViewMatrixPosRot(const Vector<Type, 3>& position,
                                  const Vector<Type, 3>& rotation) {
            S_ASSERT_TRUE(N == 4 && M == 4, "View matrix can only be created for 4x4 matrices");
            MatrixMixedAlgorithms::calculateViewMatrixPosRot(position.data, rotation.data, data);
            return *this;
        }

        /**
         * @brief Checks if the matrix is a valid view matrix
         * @details A valid view matrix is a matrix that is ivertible
         * @return True if the matrix is a valid view matrix, false otherwise
         */
        [[nodiscard]] bool isValidViewMatrix() const {
            S_ASSERT_TRUE(N == 4 && M == 4, "View matrix can only be created for 4x4 matrices");
            return MatrixAlgorithms::isValidViewMatrix(this->data);
        }

        /**
         * @brief Creates a projection matrix from the given fov, aspect ratio, near and far planes.
         * @details This operation will overwrite the current matrix with the result of the projection matrix
         * @param fovDegrees The field of view in radians
         * @param nearPlane The near plane
         * @param farPlane The far plane
         * @param viewWidth The width of the view
         * @param viewHeight The height of the view
         */
        Matrix& makeProjectionMatrix(float fovDegrees,
                                  float nearPlane,
                                  float farPlane,
                                  float viewWidth,
                                  float viewHeight) {
            S_ASSERT_TRUE(N == 4 && M == 4, "Projection matrix can only be created for 4x4 matrices");
            MatrixAlgorithms::perspective<Type>(Math::radians(fovDegrees), nearPlane, farPlane, viewWidth, viewHeight,
                                                this->data);
            return *this;
        }

        /**
         * @brief Calculates the rank of the matrix.
         * @details The rank of a matrix is the maximum number of linearly independent rows or
         * columns. This implementation uses Gaussian elimination.
         * @return size_t representing the rank of the matrix.
         */
        [[nodiscard]] size_t rank() {
            return MatrixAlgorithms::gaussianElimination(this->data).rank;
        }

        /**
         * @brief Gets the string representation of the matrix
         * @details The matrix is represented as a string with each row on a new line
         * @return The string representation of the matrix
         */
        [[nodiscard]] std::string toString() const {
            std::string result;
            for (size_t i = 0; i < N; ++i) {
                result += "[";
                for (size_t j = 0; j < M; ++j) {
                    result += std::to_string(this->data[i][j]);
                    if (j != M - 1) {
                        result += ", ";
                    }
                }
                result += "]\n";
            }
            return result;
        }

        // =============================================================================================================
        // ============================================ Iterator =======================================================
        // =============================================================================================================


        /**
         * @brief Iterator class for the matrix
         * @tparam MatrixType The matrix, we use this to allow reusing the iterator for const and non-const matrices
         * @tparam ValueType The type of the elements in the matrix
         */
        template <typename MatrixType,
                  typename MatrixRowType,
                  typename ValueType>
        class MatrixIterator : std::iterator<std::forward_iterator_tag, MatrixRowType> {
            MatrixType* matrix;
            size_t row;
            // Also, we need to assert that the type inside the matrix has the same constness as the matrix itself
            static_assert(std::is_const<MatrixType>::value == std::is_const<ValueType>::value,
                          "Matrix type and ValueType must have the same constness");

        public:
            /**
             * @brief Constructor for the matrix iterator
             * @param m The matrix to iterate over
             * @param initialRow The initial row index
             */
            MatrixIterator(MatrixType* m, size_t initialRow) : matrix(m), row(initialRow) {
            }

            /**
             * @brief Prefix increment
             * @return The iterator after increment
             */
            MatrixIterator& operator++() {
                ++row;
                return *this;
            }

            /**
             * @brief Postfix increment
             * @return The iterator before increment
             */
            MatrixIterator operator++(int) {
                MatrixIterator copy = *this;
                ++(*this);
                return copy;
            }

            /**
             * @brief Dereference operator
             * @return The row at the current index
             */
            MatrixRowType& operator*() const {
                return (*matrix)[row];
            }

            /**
             * @brief Arrow operator
             * @return The row at the current index
             */
            bool operator!=(const MatrixIterator& other) const {
                return row != other.row;
            }
        };
        /**
         * @brief Iterator class for the matrix
         * @tparam MatrixType The matrix, we use this to allow reusing the iterator for const and non-const matrices
         * @tparam ValueType The type of the elements in the matrix
         */
        using Iterator = MatrixIterator<GLESC::Math::Matrix<Type, N, M>, MatrixRow<Type, M>, Type>;
        /**
         * @brief Iterator class for the matrix
         * @tparam MatrixType The matrix, we use this to allow reusing the iterator for const and non-const matrices
         * @tparam ValueType The type of the elements in the matrix
         */
        using ConstIterator = MatrixIterator<const GLESC::Math::Matrix<Type, N, M>, const MatrixRow<Type, M>,
                                             const Type>;

        /**
         * @brief Returns an iterator to the beginning of the matrix
         * @return The iterator to the beginning of the matrix
         */
        Iterator begin() { return Iterator(this, 0); }
        /**
         * @brief Returns an iterator to the end of the matrix
         * @return The iterator to the end of the matrix
         */
        Iterator end() { return Iterator(this, N); }
        /**
         * @brief Returns a const iterator to the beginning of the matrix
         * @return The const iterator to the beginning of the matrix
         */
        ConstIterator begin() const { return ConstIterator(this, 0); }
        /**
         * @brief Returns a const iterator to the end of the matrix
         * @return The const iterator to the end of the matrix
         */
        ConstIterator end() const { return ConstIterator(this, N); }

        /**
         * @brief Matrix data
         * @details Matrix data is stored in a vector of vectors
         * M is the number of columns or the width of the matrix
         * N is the number of rows (or vertices) or the height of the matrix
         */
        MatrixData<Type, N, M> data{};
    }; // class Matrix
} // namespace GLESC::Math
using Mat2 [[maybe_unused]] = GLESC::Math::Matrix<float, 2, 2>;
using Mat3 [[maybe_unused]] = GLESC::Math::Matrix<float, 3, 3>;
using Mat4 [[maybe_unused]] = GLESC::Math::Matrix<float, 4, 4>;
using Mat2D [[maybe_unused]] = GLESC::Math::Matrix<double, 2, 2>;
using Mat3D [[maybe_unused]] = GLESC::Math::Matrix<double, 3, 3>;
using Mat4D [[maybe_unused]] = GLESC::Math::Matrix<double, 4, 4>;
using Mat2I [[maybe_unused]] = GLESC::Math::Matrix<int, 2, 2>;
using Mat3I [[maybe_unused]] = GLESC::Math::Matrix<int, 3, 3>;
using Mat4I [[maybe_unused]] = GLESC::Math::Matrix<int, 4, 4>;
using Mat2UI [[maybe_unused]] = GLESC::Math::Matrix<unsigned int, 2, 2>;
using Mat3UI [[maybe_unused]] = GLESC::Math::Matrix<unsigned int, 3, 3>;
using Mat4UI [[maybe_unused]] = GLESC::Math::Matrix<unsigned int, 4, 4>;
using Mat2L [[maybe_unused]] = GLESC::Math::Matrix<long, 2, 2>;
using Mat3L [[maybe_unused]] = GLESC::Math::Matrix<long, 3, 3>;
using Mat4L [[maybe_unused]] = GLESC::Math::Matrix<long, 4, 4>;
using Mat2UL [[maybe_unused]] = GLESC::Math::Matrix<unsigned long, 2, 2>;
using Mat3UL [[maybe_unused]] = GLESC::Math::Matrix<unsigned long, 3, 3>;
using Mat4UL [[maybe_unused]] = GLESC::Math::Matrix<unsigned long, 4, 4>;
using Mat2F [[maybe_unused]] = GLESC::Math::Matrix<float, 2, 2>;
using Mat3F [[maybe_unused]] = GLESC::Math::Matrix<float, 3, 3>;
using Mat4F [[maybe_unused]] = GLESC::Math::Matrix<float, 4, 4>;
