/**************************************************************************************************
 * @file   MatrixAlgorithmsTests.cpp
 * @author Valentin Dumitru
 * @date   16/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include <gtest/gtest.h>
#include <type_traits>
#include <iostream>
// Set glm to be row major
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_ROW_MAJOR
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>

#include "unit/engine/core/math/algebra/matrix/MatrixTestsHelper.cpp"
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"
#ifdef MATH_ALGEBRA_UNIT_TESTING
template <class Type>
class MatrixAlgorithmsTests : public testing::Test {
protected:
    MatrixAlgorithmsTests() = default;

    void SetUp() override { initializeMatrixWithValues(this->matrix); }

    void TearDown() override {
    }

    GLESC::Math::MatrixData<typename Type::ValueType, Type::Rows, Type::Cols> matrix{};
};

using MatrixAlgorithmsTypes = ::testing::Types<
    MatrixType<float, 2, 2>, MatrixType<double, 2, 2>, MatrixType<int, 2, 2>, MatrixType<size_t, 2, 2>,
    MatrixType<float, 3, 3>, MatrixType<double, 3, 3>, MatrixType<int, 3, 3>, MatrixType<size_t, 3, 3>,
    MatrixType<float, 4, 4>, MatrixType<double, 4, 4>, MatrixType<int, 4, 4>, MatrixType<size_t, 4, 4>,
    MatrixType<float, 5, 5>, MatrixType<double, 5, 5>, MatrixType<int, 5, 5>, MatrixType<size_t, 5, 5>,
    MatrixType<float, 10, 10>, MatrixType<double, 10, 10>,
    // Non-square matrices
    MatrixType<float, 2, 3>, MatrixType<double, 2, 3>, MatrixType<int, 2, 3>, MatrixType<size_t, 2, 3>,
    MatrixType<float, 3, 2>, MatrixType<double, 3, 2>, MatrixType<int, 3, 2>, MatrixType<size_t, 3, 2>,
    MatrixType<float, 4, 3>, MatrixType<double, 4, 3>
>;


TYPED_TEST_SUITE(MatrixAlgorithmsTests, MatrixAlgorithmsTypes);

TYPED_TEST(MatrixAlgorithmsTests, InitAlgorithm) {
    PREPARE_TEST();
    std::cout << "Testing matrix initialization for type " << typeid(Type).name() << "\n";

    TEST_SECTION("Testing matrix zero initialization")
    {
        // ------------ Zero initialization ------------
        GLESC::Math::MatrixData<Type, N, M> actualZeroMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrixZero(actualZeroMatrix);
        GLESC::Math::MatrixData<Type, N, M> expectedZeroMatrix = {};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                expectedZeroMatrix[i][j] = Type(0);
            }
        }
        EXPECT_EQ_MAT(actualZeroMatrix, expectedZeroMatrix);
    }
    TEST_SECTION("Testing matrix diagonal initialization")
    {
        // ------------ Diagonal initialization ------------
        if constexpr (N == M) {
            auto diagonal = Type(123123);
            GLESC::Math::MatrixData<Type, N, M> actualDiagonalMatrix = {};
            GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(actualDiagonalMatrix, this->matrix);
            GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(actualDiagonalMatrix, diagonal);

            GLESC::Math::MatrixData<Type, N, M> expectedDiagonalMatrix = {};
            GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(expectedDiagonalMatrix, this->matrix);
            for (size_t i = 0; i < N; ++i) {
                expectedDiagonalMatrix[i][i] = diagonal;
            }
            EXPECT_EQ_MAT(actualDiagonalMatrix, expectedDiagonalMatrix);
        }
    }
    TEST_SECTION("Testing matrix array initialization")
    {
        // ------------ Array initialization ------------
        GLESC::Math::MatrixData<Type, N, M> actualArrayMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(actualArrayMatrix, this->matrix);
        GLESC::Math::MatrixData<Type, N, M> expectedArrayMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(expectedArrayMatrix, this->matrix);
        EXPECT_EQ_MAT(actualArrayMatrix, expectedArrayMatrix);
    }
    TEST_SECTION("Testing matrix copy initialization")
    {
        // ------------ Copy initialization ------------
        GLESC::Math::MatrixData<Type, N, M> copy = {};
        GLESC::Math::MatrixAlgorithms::copyMatrix(copy, this->matrix);
        EXPECT_EQ_MAT(this->matrix, copy);
    }
    TEST_SECTION("Testing matrix move initialization")
    {
        // ------------ Move initialization ------------
        GLESC::Math::MatrixData<Type, N, M> matrixToMove;
        GLESC::Math::MatrixAlgorithms::copyMatrix(matrixToMove, this->matrix);

        GLESC::Math::MatrixData<Type, N, M> matrixToMoveTo = {};
        GLESC::Math::MatrixAlgorithms::moveMatrix(matrixToMoveTo, std::move(matrixToMove));
        // Note: The matrixToMove is left in an unspecified state after the move.
        // So we can only check the matrixObjective for the expected values.
        EXPECT_EQ_MAT(this->matrix, matrixToMoveTo);
    }
}

TYPED_TEST(MatrixAlgorithmsTests, ResizeMatrix) {
    PREPARE_TEST();
    std::cout << "Testing matrix resizing for type " << typeid(Type).name() << std::endl;

    // Reduce matrix size by 1
    TEST_SECTION("Reducing matrix size by 1")
    {
        if constexpr (N > 1 && M > 1) {
            GLESC::Math::MatrixData<Type, N - 1, M - 1> actualReducedMatrix = {};
            // No need to manually set to zero; resizeMatrix should handle this.
            GLESC::Math::MatrixAlgorithms::resizeMatrix(this->matrix, actualReducedMatrix);

            GLESC::Math::MatrixData<Type, N - 1, M - 1> expectedReducedMatrix = {};
            // Populate expectedReducedMatrix with the corresponding elements from the original matrix.
            for (size_t i = 0; i < N - 1; ++i) {
                for (size_t j = 0; j < M - 1; ++j) {
                    expectedReducedMatrix[i][j] = this->matrix[i][j];
                }
            }
            EXPECT_EQ_MAT(actualReducedMatrix, expectedReducedMatrix);
        }
    }

    // Increase matrix size by 1
    TEST_SECTION("Increasing matrix size by 1")
    {
        GLESC::Math::MatrixData<Type, N + 1, M + 1> actualIncreasedMatrix = {};
        GLESC::Math::MatrixAlgorithms::resizeMatrix(this->matrix, actualIncreasedMatrix);

        GLESC::Math::MatrixData<Type, N + 1, M + 1> expectedIncreasedMatrix = {};
        // Fill expected increased matrix with zeroes.
        for (size_t i = 0; i < N + 1; ++i) {
            for (size_t j = 0; j < M + 1; ++j) {
                expectedIncreasedMatrix[i][j] = Type(0);
            }
        }

        // Manually set expectedIncreasedMatrix's new row and column to zeroes.
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                expectedIncreasedMatrix[i][j] = this->matrix[i][j];
            }
        }


        EXPECT_EQ_MAT(actualIncreasedMatrix, expectedIncreasedMatrix);
    }
}

TYPED_TEST(MatrixAlgorithmsTests, SwapRows) {
    PREPARE_TEST();
    std::cout << "Testing matrix row swapping for type " << typeid(Type).name() << "\n";

    if constexpr (N > 1) {
        size_t row1 = 0;
        size_t row2 = 1;
        GLESC::Math::MatrixData<Type, N, M> actualSwappedMatrix = {};
        actualSwappedMatrix = this->matrix;
        // Now perform the operation on the actual matrix
        GLESC::Math::MatrixAlgorithms::swapRows(actualSwappedMatrix, row1, row2);


        // Prepare expected swapped matrix by copying and then swapping the expected rows.
        GLESC::Math::MatrixData<Type, N, M> expectedSwappedMatrix = {};
        expectedSwappedMatrix = this->matrix;
        for (size_t i = 0; i < M; ++i) {
            std::swap(expectedSwappedMatrix[row1][i], expectedSwappedMatrix[row2][i]);
        }

        EXPECT_EQ_MAT(actualSwappedMatrix, expectedSwappedMatrix);
    }
}

TYPED_TEST(MatrixAlgorithmsTests, SetMatrixZero) {
    PREPARE_TEST();
    std::cout << "Testing matrix zero initialization for type " << typeid(Type).name() << "\n";

    // ------------ Zero initialization ------------
    GLESC::Math::MatrixData<Type, N, M> actualZeroMatrix = {};
    GLESC::Math::MatrixAlgorithms::setMatrixZero(actualZeroMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedZeroMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedZeroMatrix[i][j] = Type(0);
        }
    }
    EXPECT_EQ_MAT(actualZeroMatrix, expectedZeroMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, SetMatrixDiagonal) {
    PREPARE_TEST();
    std::cout << "Testing matrix diagonal initialization for type " << typeid(Type).name() << "\n";

    // ------------ Diagonal initialization ------------
    if constexpr (N == M) {
        auto diagonal = Type(123123);
        GLESC::Math::MatrixData<Type, N, M> actualDiagonalMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(actualDiagonalMatrix, this->matrix);
        GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(actualDiagonalMatrix, diagonal);

        GLESC::Math::MatrixData<Type, N, M> expectedDiagonalMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(expectedDiagonalMatrix, this->matrix);
        for (size_t i = 0; i < N; ++i) {
            expectedDiagonalMatrix[i][i] = diagonal;
        }

        EXPECT_EQ_MAT(actualDiagonalMatrix, expectedDiagonalMatrix);
    }
}

TYPED_TEST(MatrixAlgorithmsTests, SetMatrix) {
    PREPARE_TEST();
    std::cout << "Testing matrix array initialization for type " << typeid(Type).name() << "\n";

    // ------------ Array initialization ------------
    GLESC::Math::MatrixData<Type, N, M> actualArrayMatrix = {};
    GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(actualArrayMatrix, this->matrix);
    GLESC::Math::MatrixData<Type, N, M> expectedArrayMatrix = {};
    GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(expectedArrayMatrix, this->matrix);
    EXPECT_EQ_MAT(actualArrayMatrix, expectedArrayMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, CopyMatrix) {
    PREPARE_TEST();
    std::cout << "Testing matrix copy initialization for type " << typeid(Type).name() << "\n";

    // ------------ Copy initialization ------------
    GLESC::Math::MatrixData<Type, N, M> copy = {};
    GLESC::Math::MatrixAlgorithms::copyMatrix(copy, this->matrix);
    EXPECT_EQ_MAT(this->matrix, copy);
}

TYPED_TEST(MatrixAlgorithmsTests, MoveMatrix) {
    PREPARE_TEST();
    std::cout << "Testing matrix move initialization for type " << typeid(Type).name() << "\n";

    // ------------ Move initialization ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToMove;
    GLESC::Math::MatrixAlgorithms::copyMatrix(matrixToMove, this->matrix);

    GLESC::Math::MatrixData<Type, N, M> matrixToMoveTo = {};
    GLESC::Math::MatrixAlgorithms::moveMatrix(matrixToMoveTo, std::move(matrixToMove));
    // Note: The matrixToMove is left in an unspecified state after the move.
    // So we can only check the matrixObjective for the expected values.
    EXPECT_EQ_MAT(this->matrix, matrixToMoveTo);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixAdd) {
    PREPARE_TEST();
    std::cout << "Testing matrix addition for type " << typeid(Type).name() << "\n";

    // ------------ Add matrices ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToAdd = {};
    initializeMatrixWithValues(matrixToAdd);
    GLESC::Math::MatrixData<Type, N, M> actualAddedMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixAdd<Type, N, M>(this->matrix, matrixToAdd, actualAddedMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedAddedMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedAddedMatrix[i][j] = this->matrix[i][j] + matrixToAdd[i][j];
        }
    }
    EXPECT_EQ_MAT(actualAddedMatrix, expectedAddedMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixScalarAdd) {
    PREPARE_TEST();
    std::cout << "Testing matrix scalar addition for type " << typeid(Type).name() << "\n";

    // ------------ Add scalar to matrix ------------
    auto scalar = Type(123);
    GLESC::Math::MatrixData<Type, N, M> actualScalarAddedMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixScalarAdd<Type, N, M>(this->matrix, scalar, actualScalarAddedMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedScalarAddedMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedScalarAddedMatrix[i][j] = this->matrix[i][j] + scalar;
        }
    }
    EXPECT_EQ_MAT(actualScalarAddedMatrix, expectedScalarAddedMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixHadamardMul) {
    PREPARE_TEST();
    std::cout << "Testing matrix Hadamard product for type " << typeid(Type).name() << "\n";

    // ------------ Hadamard product of two matrices ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToMul = {};
    initializeMatrixWithValues(matrixToMul);
    GLESC::Math::MatrixData<Type, N, M> actualHadamardMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixHadamardMul<Type, N, M>(this->matrix, matrixToMul, actualHadamardMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedHadamardMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedHadamardMatrix[i][j] = this->matrix[i][j] * matrixToMul[i][j];
        }
    }
    EXPECT_EQ_MAT(actualHadamardMatrix, expectedHadamardMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixScalarMul) {
    PREPARE_TEST();
    std::cout << "Testing matrix scalar multiplication for type " << typeid(Type).name() << "\n";

    // ------------ Multiply matrix by scalar ------------
    auto scalar = Type(123);
    GLESC::Math::MatrixData<Type, N, M> actualScalarMulMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixScalarMul<Type, N, M>(this->matrix, scalar, actualScalarMulMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedScalarMulMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedScalarMulMatrix[i][j] = this->matrix[i][j] * scalar;
        }
    }
    EXPECT_EQ_MAT(actualScalarMulMatrix, expectedScalarMulMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixSub) {
    PREPARE_TEST();
    std::cout << "Testing matrix subtraction for type " << typeid(Type).name() << "\n";

    // ------------ Subtract matrices ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToSub = {};
    initializeMatrixWithValues(matrixToSub);
    GLESC::Math::MatrixData<Type, N, M> actualSubMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixSub<Type, N, M>(this->matrix, matrixToSub, actualSubMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedSubMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedSubMatrix[i][j] = this->matrix[i][j] - matrixToSub[i][j];
        }
    }
    EXPECT_EQ_MAT(actualSubMatrix, expectedSubMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixScalarSub) {
    PREPARE_TEST();
    std::cout << "Testing matrix scalar subtraction for type " << typeid(Type).name() << "\n";

    // ------------ Subtract scalar from matrix ------------
    auto scalar = Type(123);
    GLESC::Math::MatrixData<Type, N, M> actualScalarSubMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixScalarSub<Type, N, M>(this->matrix, scalar, actualScalarSubMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedScalarSubMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedScalarSubMatrix[i][j] = this->matrix[i][j] - scalar;
        }
    }
    EXPECT_EQ_MAT(actualScalarSubMatrix, expectedScalarSubMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixNegate) {
    PREPARE_TEST();
    std::cout << "Testing matrix negation for type " << typeid(Type).name() << "\n";

    // ------------ Negate matrix ------------
    GLESC::Math::MatrixData<Type, N, M> actualNegatedMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixNegate<Type, N, M>(this->matrix, actualNegatedMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedNegatedMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedNegatedMatrix[i][j] = -this->matrix[i][j];
        }
    }
    EXPECT_EQ_MAT(actualNegatedMatrix, expectedNegatedMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixHadamardDiv) {
    PREPARE_TEST();
    std::cout << "Testing matrix Hadamard division for type " << typeid(Type).name() << "\n";

    // ------------ Hadamard division of two matrices ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToDiv = {};
    GLESC::Math::MatrixAlgorithms::fillMatrix(matrixToDiv, Type(2));
    GLESC::Math::MatrixData<Type, N, M> actualHadamardDivMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixHadamardDiv<Type, N, M>(this->matrix, matrixToDiv, actualHadamardDivMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedHadamardDivMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedHadamardDivMatrix[i][j] = this->matrix[i][j] / matrixToDiv[i][j];
        }
    }
    EXPECT_EQ_MAT(actualHadamardDivMatrix, expectedHadamardDivMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixScalarDiv) {
    PREPARE_TEST();
    std::cout << "Testing matrix scalar division for type " << typeid(Type).name() << "\n";

    // ------------ Divide matrix by scalar ------------
    auto scalar = Type(123);
    GLESC::Math::MatrixData<Type, N, M> actualScalarDivMatrix = {};
    GLESC::Math::MatrixAlgorithms::matrixScalarDiv<Type, N, M>(this->matrix, scalar, actualScalarDivMatrix);
    GLESC::Math::MatrixData<Type, N, M> expectedScalarDivMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedScalarDivMatrix[i][j] = this->matrix[i][j] / scalar;
        }
    }
    EXPECT_EQ_MAT(actualScalarDivMatrix, expectedScalarDivMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixMatrixMul) {
    PREPARE_TEST();
    std::cout << "Testing matrix multiplication for type " << typeid(Type).name() << std::endl;

    constexpr size_t P = 3; // Example, adjust P as needed for the second matrix dimension

    // Initialize first matrix (N x M)
    GLESC::Math::MatrixData<Type, N, M> matrixToMulLeft = this->matrix; // Assuming this->matrix is N x M

    // Initialize second matrix (M x P) with example values
    GLESC::Math::MatrixData<Type, M, P> matrixToMulRight = {};
    // Fill matrixToMulRight with values for testing

    // Result matrix (N x P)
    GLESC::Math::MatrixData<Type, N, P> actualMulMatrix = {};

    // Perform matrix multiplication
    GLESC::Math::MatrixAlgorithms::matrixMatrixMul(matrixToMulLeft, matrixToMulRight, actualMulMatrix);

    // Expected result matrix (N x P)
    GLESC::Math::MatrixData<Type, N, P> expectedMulMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < P; ++j) {
            Type sum = 0;
            for (size_t k = 0; k < M; ++k) {
                sum += matrixToMulLeft[i][k] * matrixToMulRight[k][j];
            }
            expectedMulMatrix[i][j] = sum;
        }
    }

    // Compare actual and expected matrices
    EXPECT_EQ_MAT(actualMulMatrix, expectedMulMatrix);
}

TYPED_TEST(MatrixAlgorithmsTests, MatrixMatrixDiv) {
    PREPARE_TEST();
    std::cout << "Testing matrix division for type " << typeid(Type).name() << "\n";
    // Div uses inverse, and inverse is only defined for square matrices less than 5x5
    if constexpr (N <= 4 && M <= 4 && N == M) {
        // ------------ Divide matrices ------------
        GLESC::Math::MatrixData<Type, M, N> matrixToDiv = {};
        initializeMatrixWithValues(matrixToDiv);

        GLESC::Math::MatrixData<Type, N, N> actualDivMatrix = {};
        GLESC::Math::MatrixAlgorithms::matrixMatrixDiv(this->matrix, matrixToDiv, actualDivMatrix);

        GLESC::Math::MatrixData<Type, N, N> inverseMatrixToMul = {};
        GLESC::Math::MatrixAlgorithms::matrixInverse(matrixToDiv, inverseMatrixToMul);
        GLESC::Math::MatrixData<Type, N, N> expectedDivMatrix = {};
        GLESC::Math::MatrixAlgorithms::matrixMatrixMul(this->matrix, inverseMatrixToMul, expectedDivMatrix);
        EXPECT_EQ_MAT(actualDivMatrix, expectedDivMatrix);
    }
}

TYPED_TEST(MatrixAlgorithmsTests, Transpose) {
    PREPARE_TEST();
    std::cout << "Testing matrix transpose for type " << typeid(Type).name() << "\n";

    // ------------ Transpose matrix ------------
    GLESC::Math::MatrixData<Type, M, N> actualTransposedMatrix = {};
    GLESC::Math::MatrixAlgorithms::transpose<Type, N, M>(this->matrix, actualTransposedMatrix);
    GLESC::Math::MatrixData<Type, M, N> expectedTransposedMatrix = {};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectedTransposedMatrix[j][i] = this->matrix[i][j];
        }
    }
    EXPECT_EQ_MAT(actualTransposedMatrix, expectedTransposedMatrix);
}


// ------------------------------ Exact solutions -----------------------------
TEST(MatrixAlgorithmsTests, LaplaceExpansionDeterminantAlgorithm) {
    GLESC::Math::MatrixData<double, 2, 2> matrix2x2;
    GLESC::Math::MatrixData<double, 3, 3> matrix3x3;
    GLESC::Math::MatrixData<double, 4, 4> matrix4x4;
    GLESC::Math::MatrixData<double, 5, 5> matrix5x5;
    double expectedDeterminant;
    double actualDeterminant;

    TEST_SECTION("Testing all elements are zero")
    {
        // Zero determinant - All elements of a row are zero
        matrix3x3 = {{{1, 2, 3}, {0, 0, 0}, {7, 8, 9}}};
        expectedDeterminant = 0;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Testing two rows are identical")
    {
        // 2. Zero determinant - Two rows are identical
        matrix3x3 = {{{1, 2, 3}, {1, 2, 3}, {7, 8, 9}}};
        expectedDeterminant = 0;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Testing two rows are proportional")
    {
        // Zero determinant - Two rows are proportional
        matrix3x3 = {{{1, 2, 3}, {2, 4, 6}, {7, 8, 9}}};
        expectedDeterminant = 0;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 2x2 matrix")
    {
        // Determinant of a 2x2 matrix
        matrix2x2 = {{{1, 2}, {3, 4}}};
        // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%7D%2C%7B3%2C4%7D%7D
        expectedDeterminant = -2;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix2x2);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 3x3 matrix")
    {
        // Determinant of a 3x3 matrix
        matrix3x3 = {{{-1, 2, 3}, {4, 5, -6}, {7, -8, 9}}};
        // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B-1%2C2%2C3%7D%2C%7B4%2C5%2C-6%7D%2C%7B7%2C-8%2C9%7D%7D
        expectedDeterminant = -354;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 4x4 matrix")
    {
        // Determinant of a 4x4 matrix
        matrix4x4 = {{{1, 2, 3, -4}, {-5, 6, 7, 8}, {9, 15, -1, 2}, {3, -4, 5, 6}}};
        // https://www.wolframalpha.com/
        // input?i2d=true&i=%7B%7B1%2C2%2C3%2C-4%7D%2C%7B-5%2C6%2C7%2C8%7D%2C%7B9%2C15%2C-1%2C2%7D%2C%7B3%2C-4%2C5%2C6%7D%7D
        expectedDeterminant = -9588;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix4x4);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 5x5 matrix")
    {
        // Determinant of a 5x5 matrix
        matrix5x5 = {
            {
                {-1, 2, 3, 4, 5}, {6, 7, 8, -9, 0}, {11, -21, 31, -41, 51}, {-61, 71, 81, 91, 10},
                {11.1, 32.1, -53.1, 64.1, -75.1}
            }
        };
        // https://www.wolframalpha.com/
        // input?i2d=true&i=%7B%7B-1%2C2%2C3%2C4%2C5%7D%2C%7B6%2C7%2C8%2C-9%2C0%7D%2C%7B11%2C-21%2C31%2C-41%2C51%7D%2C%7B-
        // 61%2C71%2C81%2C91%2C10%7D%2C%7B11.1%2C32.1%2C-53.1%2C64.1%2C-75.1%7D%7D
        expectedDeterminant = -6.344832400000001 * pow(10, 6);
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix5x5);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
}

// TODO: Make gaussian elimination work
//TYPED_TEST(MatrixAlgorithmsTests, DeterminantAlgorithm) {
//    PREPARE_TEST();
//    }TEST_SECTION("Testing matrix determinant algorithm"){
//    if constexpr (N == M) {
//        GLESC::Math::MatrixData<Type, N, M> matrixToTest;
//        generateMatrixWithRandomNumbers(matrixToTest);
//        std::cout<<"Matrix to test: \n"<<GLESC::Stringer::toString(matrixToTest)<<"\n";
//        // Check if both determinant algorithms return the same result
//        auto laplaceDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrixToTest);
//        auto gaussianDeterminant = GLESC::Math::MatrixAlgorithms::gaussianElimination(matrixToTest).determinant;
//        EXPECT_EQ_CUSTOM(laplaceDeterminant, gaussianDeterminant);
//    }
//}


TEST(MatrixAlgorithmsTests, InverseAlgorithmExactSolution) {
    TEST_SECTION("Testing Inverse of a 2x2 matrix")
    {
        // Test Inverse of a 2x2 matrix
        GLESC::Math::MatrixData<double, 2, 2> matrix2x2({{{1, 2}, {3, 4}}});
        GLESC::Math::MatrixData<double, 2, 2> expectedInverse2x2({{{-2, 1}, {1.5, -0.5}}});
        GLESC::Math::MatrixData<double, 2, 2> actualInverse2x2;
        GLESC::Math::MatrixAlgorithms::matrixInverse(matrix2x2, actualInverse2x2);
        EXPECT_EQ_MAT(actualInverse2x2, expectedInverse2x2);
    }
    TEST_SECTION("Testing Inverse of a 3x3 matrix")
    {
        // Test Inverse of a 3x3 matrix
        GLESC::Math::MatrixData<double, 3, 3> matrix3x3({{{1, 2, -3}, {-3, 4, -5}, {7, -8, 9}}});
        GLESC::Math::MatrixData<double, 3, 3>
            expectedInverse3x3({{{0.5, -0.75, -0.25}, {1, -3.75, -1.75}, {0.5, -2.75, -1.25}}});
        GLESC::Math::MatrixData<double, 3, 3> actualInverse3x3;
        GLESC::Math::MatrixAlgorithms::matrixInverse(matrix3x3, actualInverse3x3);
        EXPECT_EQ_MAT(actualInverse3x3, expectedInverse3x3);
    }
    TEST_SECTION("Testing Inverse of a 4x4 matrix")
    {
        // Test Inverse of a 4x4 matrix
        GLESC::Math::MatrixData<double, 4, 4> matrix4x4({
            {{1, 2, 3, -4}, {-5, 6, 7, 8}, {9, 15, -1, 2}, {3, -4, 5, 6}}
        });
        GLESC::Math::MatrixData<double, 4, 4> expectedInverse4x4(
            {
                {
                    {0.0223196, -0.0636212, 0.0450563, 0.0846892},
                    {0.01335, 0.0367126, 0.0362954, -0.0521485},
                    {0.148728, 0.0340008, -0.0175219, 0.0596579},
                    {-0.126199, 0.0279516, 0.0162703, 0.0398415}
                }
            });
        GLESC::Math::MatrixData<double, 4, 4> actualInverse4x4;
        GLESC::Math::MatrixAlgorithms::matrixInverse(matrix4x4, actualInverse4x4);
        EXPECT_EQ_MAT(actualInverse4x4, expectedInverse4x4);
    }
    TEST_SECTION("Testing Inverse of a 5x5 matrix")
    {
        // Test Inverse of a 5x5 matrix
        GLESC::Math::MatrixData<double, 5, 5> matrix5x5({
            {
                {-1, 2, 3, 4, 5},
                {6, 7, 8, -9, 0},
                {11, -21, 31, -41, 51},
                {-61, 71, 81, 91, 10},
                {11.1, 32.1, -53.1, 64.1, -75.1}
            }
        });
    }


    // @TODO: Implement inverse for any matrix size
    //GLESC::Math::MatrixData<double, 5, 5> expectedInverse5x5(
    //    {
    //        {
    //            {-0.0935895, -0.0085282, 0.0719947, 0.00517271, 0.043349},
    //            {0.351945, 0.119422, -0.0858807, -0.0162524, -0.0370535},
    //            {-0.326954, -0.0438212, 0.0777137, 0.02122, 0.0338326},
    //            {-0.0792838, -0.0628653, 0.0502792, 0.00966992, 0.0301534},
    //            {0.300103, 0.0271107, -0.0381003, -0.0129324, -0.020931}
    //        }
    //    });
    //GLESC::Math::MatrixData<double, 5, 5> actualInverse5x5;
    //GLESC::Math::MatrixAlgorithms::matrixInverse(matrix5x5, actualInverse5x5);
    //EXPECT_EQ_MAT(actualInverse5x5, expectedInverse5x5);
}

TEST(MatrixAlgorithmsTests, TranslateAlgorithm) {
    GLESC::Math::VectorData<float, 3> translateVec2D({2.0f, 3.0f, 1.0f});
    GLESC::Math::MatrixData<float, 4, 4> matrixToTranslate;
    GLESC::Math::MatrixAlgorithms::setMatrixZero(matrixToTranslate);
    GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(matrixToTranslate, 1.0f);

    GLESC::Math::MatrixAlgorithms::setTranslate(matrixToTranslate, translateVec2D, matrixToTranslate);

    // Do the same with glm
    auto glmMatToTranslate = glm::mat4(1.0f);
    glmMatToTranslate = glm::translate(glmMatToTranslate,
                                       glm::vec3(translateVec2D[0], translateVec2D[1], translateVec2D[2]));

    // Check if the two matrices are equal
    GLESC::Math::MatrixData<float, 4, 4> expectedTranslateMatrix({});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expectedTranslateMatrix[i][j] = glmMatToTranslate[i][j];
        }
    }
    EXPECT_EQ_MAT(matrixToTranslate, expectedTranslateMatrix);
}


TEST(MatrixAlgorithmsTests, ScaleAlgorithm) {
    GLESC::Math::VectorData<float, 3> scaleVec2D({2.0f, 3.0f, 1.0f});
    GLESC::Math::MatrixData<float, 4, 4> matrixToScale;
    GLESC::Math::MatrixAlgorithms::setMatrixZero(matrixToScale);
    GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(matrixToScale, 1.0f);

    GLESC::Math::MatrixAlgorithms::setScale(matrixToScale, scaleVec2D, matrixToScale);

    // Do the same with glm
    auto glmMatToScale = glm::mat4(1.0f);
    glmMatToScale = glm::scale(glmMatToScale, glm::vec3(scaleVec2D[0], scaleVec2D[1], scaleVec2D[2]));

    // Check if the two matrices are equal
    GLESC::Math::MatrixData<float, 4, 4> expectedScaleMatrix({});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expectedScaleMatrix[i][j] = glmMatToScale[i][j];
        }
    }
    EXPECT_EQ_MAT(matrixToScale, expectedScaleMatrix);
}

TEST(MatrixAlgorithmsTests, RotateAlgorithm) {
    std::vector<GLESC::Math::VectorData<float, 3>> rotateVecDegrs = {
        {45.0f, 0.0f, 0.0f},
        {0.0f, 45.0f, 0.0f},
        {0.0f, 0.0f, 45.0f},
        {11.0f, 22.0f, 0.0f},
        {45.0f, 99.0f, 53.0f}
    };

    for (const auto& vecDegrs : rotateVecDegrs) {
        auto glmMatToRotate3D = glm::mat4(1.0f);
        GLESC::Math::MatrixData<float, 4, 4> rotate3D({});
        GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(rotate3D, 1.0f);

        GLESC::Math::MatrixMixedAlgorithms::rotate3D(rotate3D, vecDegrs[0], {1, 0, 0}, rotate3D);
        GLESC::Math::MatrixMixedAlgorithms::rotate3D(rotate3D, vecDegrs[1], {0, 1, 0}, rotate3D);
        GLESC::Math::MatrixMixedAlgorithms::rotate3D(rotate3D, vecDegrs[2], {0, 0, 1}, rotate3D);

        // Rotate around X-axis
        glmMatToRotate3D = glm::rotate(glmMatToRotate3D, glm::radians(vecDegrs[0]), glm::vec3(1, 0, 0));
        // Rotate around Y-axis
        glmMatToRotate3D = glm::rotate(glmMatToRotate3D, glm::radians(vecDegrs[1]), glm::vec3(0, 1, 0));
        // Rotate around Z-axis
        glmMatToRotate3D = glm::rotate(glmMatToRotate3D, glm::radians(vecDegrs[2]), glm::vec3(0, 0, 1));

        GLESC::Math::MatrixData<float, 4, 4> expectedRotate3D({});
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                expectedRotate3D[i][j] = glmMatToRotate3D[i][j];
            }
        }
        std::cout << "Degrees: " << vecDegrs[0] << " " << vecDegrs[1] << " " << vecDegrs[2] << "\n";
        // Use your testing framework's method to compare matrices.
        EXPECT_EQ_MAT(rotate3D, expectedRotate3D);
    }
}

TEST(MatrixAlgorithmsTests, LookAtAlgorithm) {
    GLESC::Math::VectorData<float, 3> eye({0.0f, 0.0f, 0.0f});
    GLESC::Math::VectorData<float, 3> center({0.0f, 0.0f, -1.0f});
    GLESC::Math::VectorData<float, 3> up({0.0f, 1.0f, 0.0f});

    GLESC::Math::MatrixData<float, 4, 4> lookAtMatrix;
    GLESC::Math::MatrixMixedAlgorithms::lookAt3D(eye, center, up, lookAtMatrix);

    // Do the same with glm
    auto glmLookAtMatrix = glm::lookAt(glm::vec3(eye[0], eye[1], eye[2]),
                                       glm::vec3(center[0], center[1], center[2]),
                                       glm::vec3(up[0], up[1], up[2]));

    // Check if the two matrices are equal
    GLESC::Math::MatrixData<float, 4, 4> expectedLookAtMatrix({});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expectedLookAtMatrix[i][j] = glmLookAtMatrix[i][j];
        }
    }
    EXPECT_EQ_MAT(lookAtMatrix, expectedLookAtMatrix);
}

TEST(MatrixAlgorithmsTests, PerspectiveProjectionAlgorithm) {
    TEST_SECTION("Test against glm")
    {
        // Convert your values to glm::vec3
        float fovRads = 0.3;
        float nearPlane = 10;
        float farPlane = 40.4;
        float viewWidth = 140.0;
        float viewHeight = 120.0;
        glm::mat4 perspectiveMatrixGlm = glm::perspective(fovRads, viewWidth / viewHeight, nearPlane, farPlane);
        // Convert to GLESC matrix
        GLESC::Math::MatrixData<double, 4, 4> perspectiveGlmMatrix;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                perspectiveGlmMatrix[i][j] = perspectiveMatrixGlm[i][j];
            }
        }

        GLESC::Math::MatrixData<double, 4, 4> perspectiveMatrix;
        GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, farPlane, viewWidth, viewHeight,
                                                   perspectiveMatrix);

        EXPECT_EQ_MAT(perspectiveMatrix, perspectiveGlmMatrix);
    }

    TEST_SECTION("Testing errors in projection matrix")
    {
        // Far plane is closer than the near plane
        float fovRads = 0.3;
        float nearPlane = 10;
        float farPlane = 5;
        float viewWidth = 140.0;
        float viewHeight = 120.0;
        GLESC::Math::MatrixData<double, 4, 4> perspectiveMatrix;
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, farPlane, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);

        // Restore to a valid far plane and near plane
        farPlane = 40.4;
        nearPlane = 10;

        // Fov is negative and zero
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(-fovRads, nearPlane, farPlane, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(0, nearPlane, farPlane, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);

        // Near plane is negative
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, -nearPlane, farPlane, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, 0, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);

        // Far plane is negative
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, -farPlane, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, 0, viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);

        // View width is negative
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, farPlane, -viewWidth, viewHeight,
                         perspectiveMatrix), AssertFailedException);
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, farPlane, viewWidth, 0,
                         perspectiveMatrix), AssertFailedException);

        // View height is negative
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, farPlane, viewWidth, -viewHeight,
                         perspectiveMatrix), AssertFailedException);
        EXPECT_THROW(GLESC::Math::MatrixAlgorithms::perspective(fovRads, nearPlane, farPlane, 0, viewHeight,
                         perspectiveMatrix), AssertFailedException);
    }
}
glm::mat4 calculateGlmViewMatrix(const GLESC::Math::VectorData<float, 3>& cameraPosition,
                                 const GLESC::Math::VectorData<float, 3>& cameraRotationDegrees) {
    glm::mat4 glmView = glm::mat4(1.0f);
    glmView = glm::rotate(glmView, glm::radians(cameraRotationDegrees[0]), glm::vec3(1, 0, 0));
    glmView = glm::rotate(glmView, glm::radians(cameraRotationDegrees[1]), glm::vec3(0, 1, 0));
    glmView = glm::rotate(glmView, glm::radians(cameraRotationDegrees[2]), glm::vec3(0, 0, 1));
    glmView = glm::translate(glmView, glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]));
    return glmView;
}

glm::mat4 calculateGlmModelMatrix(const GLESC::Math::VectorData<float, 3>& position,
                                  const GLESC::Math::VectorData<float, 3>& rotationDegrees,
                                  const GLESC::Math::VectorData<float, 3>& scale) {
    glm::mat4 glmModel = glm::mat4(1.0f);
    glmModel = glm::translate(glmModel, glm::vec3(position[0], position[1], position[2]));
    glmModel = glm::rotate(glmModel, glm::radians(rotationDegrees[0]), glm::vec3(1, 0, 0));
    glmModel = glm::rotate(glmModel, glm::radians(rotationDegrees[1]), glm::vec3(0, 1, 0));
    glmModel = glm::rotate(glmModel, glm::radians(rotationDegrees[2]), glm::vec3(0, 0, 1));
    glmModel = glm::scale(glmModel, glm::vec3(scale[0], scale[1], scale[2]));
    return glmModel;
}
glm::mat4 calculateGlmNormalMatrix(const glm::mat4& modelViewMatrix) {
    return glm::transpose(glm::inverse(glm::mat3(modelViewMatrix)));
}
TEST(MatrixAlgorithmsTests, CalculateNormalMatrix) {
    GLESC::Math::VectorData<float, 3> position({1, 2, 3});
    GLESC::Math::VectorData<float, 3> scale({1, 2, 3});
    GLESC::Math::VectorData<float, 3> rotationDegrees({12, 32, 211});

    GLESC::Math::VectorData<float, 3> cameraPosition({0, 12, 3});
    GLESC::Math::VectorData<float, 3> cameraRotationDegrees({13, 10, 222});

    // Calculate model matrix using glm
    glm::mat4 glmModel = calculateGlmModelMatrix(position, rotationDegrees, scale);
    // Calculate view matrix using glm
    glm::mat4 glmView = calculateGlmViewMatrix(cameraPosition, cameraRotationDegrees);
    // Combine model and view matrices
    glm::mat4 glmMV = glmModel * glmView;
    // Calculate the normal matrix using glm, row major
    glm::mat3 glmNormalMatrix = calculateGlmNormalMatrix(glmMV);

    // Convert glmMV to our MatrixData format
    GLESC::Math::MatrixData<float, 4, 4> ourMV;
    GLESC::Math::MatrixData<float, 4, 4> ourModelMat;
    GLESC::Math::MatrixMixedAlgorithms::calculateModelMatrix(position, rotationDegrees, scale, ourModelMat);
    GLESC::Math::MatrixData<float, 4, 4> ourViewMat;
    GLESC::Math::MatrixMixedAlgorithms::calculateViewMatrixPosRot(cameraPosition, cameraRotationDegrees, ourViewMat);
    GLESC::Math::MatrixAlgorithms::matrixMatrixMul(ourModelMat, ourViewMat, ourMV);

    // Calculate the normal matrix using our implementation
    GLESC::Math::MatrixData<float, 3, 3> ourNormalMatrix;
    GLESC::Math::MatrixMixedAlgorithms::calculateNormalMatrix(ourMV, ourNormalMatrix);

    // Convert glmNormalMatrix to our MatrixData format for comparison
    GLESC::Math::MatrixData<float, 3, 3> glmNormalMatrixConverted;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            glmNormalMatrixConverted[i][j] = glmNormalMatrix[i][j];
        }
    }

    // Finally, compare our normal matrix to glm's normal matrix
    EXPECT_EQ_MAT(ourNormalMatrix, glmNormalMatrixConverted);
}

TEST(MatrixAlgorithmsTests, CalculateModelMatrixAlgorithm) {
    // Model matrix
    GLESC::Math::MatrixData<float, 4, 4> modelMatrix;
    std::vector<std::tuple<GLESC::Math::VectorData<float, 3>,
                           GLESC::Math::VectorData<float, 3>,
                           GLESC::Math::VectorData<float, 3>>> transforms = {
        // Scale, RotationDegrees, Position
        {{1, 1.1, 1.2}, {10, 20, -30}, {100, 200, 300}},
        {{1.3, 1.4, 1.5}, {40, 50, 60}, {400, 500, -600}},
        {{1.6, 1.7, 1.8}, {-70, -80, 90}, {-700, 800, 900}},
        {{1.9, 2.0, 2.1}, {100, 110, 120}, {1000, -1100, 1200}},
        {{2.2, 2.3, 2.4}, {130, 140, -150}, {1300, 1400, 1500}},
    };
    for (const auto& [scale, rotationDegrees, position] : transforms) {
        GLESC::Math::MatrixMixedAlgorithms::calculateModelMatrix(position, rotationDegrees, scale, modelMatrix);

        // Check against glm
        glm::mat4 glmMat = calculateGlmModelMatrix(position, rotationDegrees, scale);

        GLESC::Math::MatrixData<float, 4, 4> modelGlmMatrix;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                modelGlmMatrix[i][j] = glmMat[i][j];
            }
        }
        EXPECT_EQ_MAT(modelMatrix, modelGlmMatrix);
    }
}

TEST(MatrixAlgorithmsTests, CalculateViewMatrixPosRot) {
    // View matrix
    GLESC::Math::MatrixData<float, 4, 4> viewMatrix;
    GLESC::Math::VectorData<float, 3> position({1, 2, 3});
    GLESC::Math::VectorData<float, 3> rotationDegrees({12, 32, 211});

    GLESC::Math::MatrixMixedAlgorithms::calculateViewMatrixPosRot(position, rotationDegrees, viewMatrix);

    // Check against glm
    glm::mat4 glmMat = calculateGlmViewMatrix(position, rotationDegrees);

    GLESC::Math::MatrixData<float, 4, 4> viewGlmMatrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            viewGlmMatrix[i][j] = glmMat[i][j];
        }
    }
    EXPECT_EQ_MAT(viewMatrix, viewGlmMatrix);
}

TEST(MatrixAlgorithmsTests, CalculateViewMatrixAlgorithmEyeTarget) {
    // View matrix
    GLESC::Math::MatrixData<float, 4, 4> viewMatrix;
    GLESC::Math::VectorData<float, 3> eyePos({1, 2, 3});
    GLESC::Math::VectorData<float, 3> target({11, 12, 13});
    GLESC::Math::VectorData<float, 3> up({0, 1, 0});

    GLESC::Math::MatrixMixedAlgorithms::calculateViewMatrixEye(eyePos, target, up, viewMatrix);

    // Check against glm
    glm::mat4 glmMat = glm::lookAt(glm::vec3(eyePos[0], eyePos[1], eyePos[2]),
                                   glm::vec3(target[0], target[1], target[2]),
                                   glm::vec3(up[0], up[1], up[2]));

    GLESC::Math::MatrixData<float, 4, 4> viewGlmMatrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            viewGlmMatrix[i][j] = glmMat[i][j];
        }
    }
    EXPECT_EQ_MAT(viewMatrix, viewGlmMatrix);
}

#endif // MATH_ALGEBRA_UNIT_TESTING
