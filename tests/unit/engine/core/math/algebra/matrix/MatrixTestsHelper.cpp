/**************************************************************************************************
 * @file   MatrixTestsHelper.cpp
 * @author Valentin Dumitru
 * @date   16/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#pragma once
#include <gtest/gtest.h>
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"

template<typename T, size_t N, size_t M>
struct MatrixType {
    using ValueType = T;
    static const size_t Rows = N;
    static const size_t Cols = M;
};


using MyTypes = ::testing::Types<
        MatrixType<float, 2, 2>, MatrixType<double, 2, 2>,
        MatrixType<int, 2, 2>, MatrixType<size_t, 2, 2>,
        MatrixType<float, 3, 3>, MatrixType<double, 3, 3>,
        MatrixType<int, 3, 3>, MatrixType<size_t, 3, 3>,
        MatrixType<float, 4, 4>, MatrixType<double, 4, 4>,
        MatrixType<int, 4, 4>, MatrixType<size_t, 4, 4>,
        MatrixType<float, 5, 5>, MatrixType<double, 5, 5>,
        MatrixType<int, 5, 5>, MatrixType<size_t, 5, 5>,
        MatrixType<double, 10, 10>, MatrixType<float, 10, 10>,
        // Non-square matrices
        MatrixType<float, 2, 3>, MatrixType<double, 2, 3>,
        MatrixType<int, 2, 3>, MatrixType<size_t, 2, 3>,
        MatrixType<float, 3, 2>, MatrixType<double, 3, 2>,
        MatrixType<int, 3, 2>, MatrixType<size_t, 3, 2>,
        MatrixType<float, 4, 3>, MatrixType<double, 4, 3>
>;


/**
 * @brief Generate next value for the matrix
 * @details It will generate numbers for the matrices for the tests. It's important to generate
 * the numbers in a way the matrix is invertible and the determinant is not zero.
 * @tparam MyType
 * @param i
 * @param j
 * @return The next value for the matrix given the row and column
 */
template <class MyType>
inline MyType generateNextValue(size_t i, size_t j) {
    if (i == j) { // Diagonal element
        return MyType(1);
    } else { // Off-diagonal element
        return MyType(i + j + i*j*7 + 7);
    }
}
template <class MyType, size_t N, size_t M>
inline void initializeMatrixWithValues(GLESC::Math::Matrix<MyType, N, M> &matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = generateNextValue<MyType>(i, j);
}

template <class MyType, size_t N, size_t M>
inline void initializeMatrixWithValues(GLESC::Math::MatrixData<MyType, N, M> &matrix) {
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            matrix[i][j] = generateNextValue<MyType>(i, j);
}

template <class MyType, size_t N, size_t M>
inline void initializeMatrixWithDifferentValues(GLESC::Math::Matrix<MyType, N, M> &matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = generateNextValue<MyType>(i + 10, j + 10);
}

#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Rows; \
    constexpr size_t M = TypeParam::Cols; \
    using Mat = GLESC::Math::Matrix<Type, N, M>;