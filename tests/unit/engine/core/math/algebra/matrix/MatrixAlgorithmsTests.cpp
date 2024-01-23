/**************************************************************************************************
 * @file   MatrixAlgorithmsTests.cpp
 * @author Valentin Dumitru
 * @date   16/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
 
#include <gtest/gtest.h>
#include "unit/engine/core/math/algebra/matrix/MatrixTestsHelper.cpp"

template<class Type>
class MatrixAlgorithmsTests : public testing::Test {
protected:
    MatrixAlgorithmsTests() = default;
    void SetUp() override
    {initializeMatrixWithValues(this->matrix);}
    void TearDown() override {}
    typename GLESC::Math::MatrixData<typename Type::ValueType,Type::Rows,Type::Cols> matrix{};
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


TYPED_TEST_SUITE(MatrixAlgorithmsTests, MyTypes);

TYPED_TEST(MatrixAlgorithmsTests, MatrixInit) { // HERE
    PREPARE_TEST();
    
    // ------------ Zero initialization ------------
    GLESC::Math::MatrixBasicAlgorithms::setMatrxZero(this->matrix);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            EXPECT_EQ_CUSTOM(this->matrix[i][j], 0);
        }
    }

    // ------------ Diagonal initialization ------------
    auto value = Type(5);
    GLESC::Math::MatrixBasicAlgorithms::setMatrixDiagonal(this->matrix, value);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (i == j) {
                EXPECT_EQ_CUSTOM(this->matrix[i][j], value);
            } else {
                EXPECT_EQ_CUSTOM(this->matrix[i][j], 0);
            }
        }
    }
    
    
    // ------------ Array initialization ------------
    GLESC::Math::MatrixData<Type, N, M> values = {};
    // Fill the values array with arbitrary values
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            values[i][j] = static_cast<Type>((i + 1) * (j + 1));
        }
    }
    GLESC::Math::MatrixBasicAlgorithms::setMatrix(this->matrix, values);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            EXPECT_EQ_CUSTOM(this->matrix[i][j], values[i][j]);
        }
    }
    
    
    
    // ------------ Copy initialization ------------
    GLESC::Math::MatrixData<Type, N, M> copy = {};
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            copy[i][j] = this->matrix[i][j];
        }
    }
    GLESC::Math::MatrixBasicAlgorithms::copyMatrix(this->matrix, copy);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            EXPECT_EQ_CUSTOM(this->matrix[i][j], copy[i][j]);
        }
    }
    
    
    // ------------ Move initialization ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToMove = {};
    // Fill the matrixToMove with arbitrary values
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            matrixToMove[i][j] = static_cast<Type>((i + 1) * (j + 2));
        }
    }
    GLESC::Math::MatrixBasicAlgorithms::moveMatrix(this->matrix, std::move(matrixToMove));
    // Note: The matrixToMove is left in an unspecified state after the move.
    // So we can only check the matrixObjective for the expected values.
    EXPECT_EQ_MAT(this->matrix, matrixToMove);
    
}


