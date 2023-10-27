/******************************************************************************
 * @file   MatrixTestTyped.cpp
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <gtest/gtest.h>
#include "engine/core/math/Matrix.h"
#include "MathTestHelper.h"

template<typename T, size_t N, size_t M>
struct MatrixType {
    using ValueType = T;
    static const size_t Rows = N;
    static const size_t Cols = M;
};

template <class MyType, size_t N, size_t M>
void initializeMatrixWithValues(Matrix<MyType, N, M> &matrix) {
    // Matrices will have the following format (i.e. 3x3):
    // |1 2 3|
    // |4 5 6|
    // |7 8 9|
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = i * matrix.cols() + j +1;
}
template <class MyType, size_t N, size_t M>
void initializeMatrixWithDifferentValues(Matrix<MyType, N, M> &matrix) {
    // Matrices will have the following format (i.e. 3x3):
    // |13 23 33|
    // |43 53 63|
    // |73 83 93|
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = ((MyType(i) * matrix.cols() + MyType(j)) * MyType(10)) + MyType(3);
}
using MyTypes = ::testing::Types<
        MatrixType<float, 2, 2>, MatrixType<double, 2, 2>,
        MatrixType<int, 2, 2>, MatrixType<size_t, 2, 2>,
        MatrixType<float, 3, 3>, MatrixType<double, 3, 3>,
        MatrixType<int, 3, 3>, MatrixType<size_t, 3, 3>,
        MatrixType<float, 4, 4>, MatrixType<double, 4, 4>,
        MatrixType<int, 4, 4>, MatrixType<size_t, 4, 4>,
        MatrixType<float, 5, 5>, MatrixType<double, 5, 5>,
        MatrixType<int, 5, 5>, MatrixType<size_t, 5, 5>,
        MatrixType<double, 10, 10>, MatrixType<float, 10, 10>
>;
template<class Type>
class MatrixTests : public testing::Test {
protected:
    MatrixTests() {}
    void SetUp() override
    {initializeMatrixWithValues(this->matrix);
    initializeMatrixWithDifferentValues(this->matrix2);}
    void TearDown() override {}
    Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix;
    Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix2; // For combined operations
};

TYPED_TEST_SUITE(MatrixTests, MyTypes);

#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Rows; \
    constexpr size_t M = TypeParam::Cols; \
    using Mat = Matrix<Type, N, M>; \
    using VecN = Vec<Type, N>; \
    using VecM = Vec<Type, M>

TYPED_TEST(MatrixTests, Constructors) {
    PREPARE_TEST();
    // Default constructor
    Mat matrixDefault;
    Mat expectedDefault;
    for (size_t i = 0; i < matrixDefault.rows(); ++i)
        for (size_t j = 0; j < matrixDefault.cols(); ++j)
            expectedDefault[i][j] = 0;
    EXPECT_EQ_MAT(matrixDefault, expectedDefault);
    
    // Diagonal constructor
    Type diagonalValue = 1;
    Mat matrixDiagonal(diagonalValue);
    Mat expectedDiagonal;
    for (size_t i = 0; i < matrixDiagonal.rows(); ++i)
        expectedDiagonal[i][i] = diagonalValue;
    EXPECT_EQ_MAT(matrixDiagonal, expectedDiagonal);
    
    // Array constructor
    Type arrayValues[N][M];
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            arrayValues[i][j] = i * M + j + 1;
    Mat matrixArray(arrayValues);
    Mat expectedArray;
    for (size_t i = 0; i < matrixArray.rows(); ++i)
        for (size_t j = 0; j < matrixArray.cols(); ++j)
            expectedArray[i][j] = arrayValues[i][j];
    EXPECT_EQ_MAT(matrixArray, expectedArray);
    
    // Copy constructor
    Mat matrixCopy(this->matrix);
    EXPECT_EQ_MAT(matrixCopy, this->matrix);
    
    // Move constructor
    Mat matrixMove(std::move(this->matrix));
    EXPECT_EQ_MAT(matrixMove, this->matrix);
    
    // Initializer list constructor
    // TODO: Can't be done dynamically
}

TYPED_TEST(MatrixTests, Accessors) {
    PREPARE_TEST();
    
    // Get rows
    EXPECT_EQ_CUSTOM(this->matrix.rows(), N);
    
    // Get cols
    EXPECT_EQ_CUSTOM(this->matrix.cols(), M);
    
    // Set rows
    Mat matrixSetRows;
    VecM setVector(9999);
    matrixSetRows[1] = setVector;
    for (size_t i = 0; i < matrixSetRows.cols(); ++i)
        EXPECT_EQ_CUSTOM(matrixSetRows[1][i], setVector[i]);
    
    // Set value
    Mat matrixSetCols;
    Type setValue = Type(9999);
    matrixSetCols[5][5] = setValue;
    EXPECT_EQ_CUSTOM(matrixSetCols[5][5], setValue);
    
    // Operator [] ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix[i][j], i * this->matrix.cols() + j + 1);
    
    // Const Getters ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix.get(i, j), i * this->matrix.cols() + j + 1);
    // Getters must return a const reference
    static_assert(std::is_same_v<decltype(this->matrix.get(0, 0)), const Type&>);
    
}

TYPED_TEST(MatrixTests, ComparisonOperators){
    PREPARE_TEST();
    // Equality operator
    Mat matrixEquals; initializeMatrixWithValues(matrixEquals);
    EXPECT_EQ(this->matrix, matrixEquals);
    
    // Inequality operator
    Mat matrixNotEquals; initializeMatrixWithValues(matrixNotEquals);
    matrixNotEquals[0][0] += Type(1);
    EXPECT_NE(this->matrix, matrixNotEquals);
    
}

// Define test
TYPED_TEST(MatrixTests, MatrixOperators) {
    PREPARE_TEST();
    // ------------------------------ Addition -----------------------------
    
    // Addition operator
    Mat matrixAdditionResult = this->matrix + this->matrix;
    for (size_t i = 0; i < matrixAdditionResult.rows(); ++i)
        for (size_t j = 0; j < matrixAdditionResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixAdditionResult[i][j], this->matrix[i][j] + this->matrix[i][j]);
    
    // Addition operator with scalar
    Mat matrixAddScalarResult = this->matrix + 2;
    for (size_t i = 0; i < matrixAddScalarResult.rows(); ++i)
        for (size_t j = 0; j < matrixAddScalarResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixAddScalarResult[i][j], this->matrix[i][j] + 2);
    
    // ------------------------------ Subtraction -----------------------------
    
    // Subtraction operator
    Mat matrixSubtrResult = this->matrix - this->matrix;
    for (size_t i = 0; i < matrixSubtrResult.rows(); ++i)
        for (size_t j = 0; j < matrixSubtrResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixSubtrResult[i][j], this->matrix[i][j] - this->matrix[i][j]);
    
    // Subtraction operator with scalar
    Mat matrixSubtrScalarResult = this->matrix - 2;
    for (size_t i = 0; i < matrixSubtrScalarResult.rows(); ++i)
        for (size_t j = 0; j < matrixSubtrScalarResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixSubtrScalarResult[i][j], this->matrix[i][j] - 2);
    
    // Unary minus operator
    Mat matrixUnaryMinusResult = -this->matrix;
    for (size_t i = 0; i < matrixUnaryMinusResult.rows(); ++i)
        for (size_t j = 0; j < matrixUnaryMinusResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixUnaryMinusResult[i][j], -this->matrix[i][j]);
    
    // ------------------------------ Multiplication -----------------------------
    
    // Multiplication operator (dot product)
    Mat matrixMultResult = this->matrix * this->matrix;
    for (size_t i = 0; i < matrixMultResult.rows(); ++i) {
        for (size_t j = 0; j < matrixMultResult.cols(); ++j) {
            int expectedValue = 0;
            for (size_t k = 0; k < this->matrix.cols(); ++k) {
                expectedValue += this->matrix[i][k] * this->matrix[k][j];
            }
            EXPECT_EQ_CUSTOM(matrixMultResult[i][j], expectedValue);
        }
    }
    
    // Multiplication operator with different size matrices
    using FirstMat = Matrix<typename TypeParam::ValueType, TypeParam::Rows+1, TypeParam::Cols>;
    using OtherMat = Matrix<typename TypeParam::ValueType, TypeParam::Rows, TypeParam::Cols + 1>;
    using ExpectedMat = Matrix<typename TypeParam::ValueType, TypeParam::Rows+1, TypeParam::Cols+1>;
    FirstMat firstMatrix;
    OtherMat matrixToMultiply;
    initializeMatrixWithValues(firstMatrix);
    initializeMatrixWithValues(matrixToMultiply);
    ExpectedMat vectorMultResult = firstMatrix * matrixToMultiply;
    ExpectedMat expectedVectorMultResult;
    
    
    // Multiplication operator with scalar
    Mat matrixMultScalarResult = this->matrix * 2;
    for (size_t i = 0; i < matrixMultScalarResult.rows(); ++i)
        for (size_t j = 0; j < matrixMultScalarResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixMultScalarResult[i][j], this->matrix[i][j] * 2);
    
    // ------------------------------ Division -----------------------------
    // Division operator
    Mat matrixDivResult = this->matrix2 / this->matrix;
    for (size_t i = 0; i < matrixDivResult.rows(); ++i)
        for (size_t j = 0; j < matrixDivResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixDivResult[i][j], this->matrix2[i][j] / this->matrix[i][j]);
    
    // Division operator with scalar
    Mat matrixDivScalarResult = this->matrix / 2;
    for (size_t i = 0; i < matrixDivScalarResult.rows(); ++i)
        for (size_t j = 0; j < matrixDivScalarResult.cols(); ++j)
            EXPECT_EQ_CUSTOM(matrixDivScalarResult[i][j], this->matrix[i][j] / 2);

}

TYPED_TEST(MatrixTests, Functions){
    PREPARE_TEST();
    // Determinant
    Type matrixDeterminantResult = this->matrix.determinant();
    
    
    // Transpose
    Mat matrixTransposeResult = this->matrix.transpose();
    Mat expectedTransposeResult;
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            expectedTransposeResult[j][i] = this->matrix[i][j];
    EXPECT_EQ_MAT(matrixTransposeResult, expectedTransposeResult);
    
    // Translate
    auto translateVec=Vec<Type, N-1>(1);
    Mat matrixTranslateResult = this->matrix.translate(translateVec);
    Mat expectedTranslateResult = this->matrix;
    
    for (size_t i = 0; i < N - 1; ++i) {
        expectedTranslateResult[i][N - 1] += translateVec[i];
    }
    
    for (size_t i = 0; i < expectedTranslateResult.rows(); ++i) {
        for (size_t j = 0; j < expectedTranslateResult.cols(); ++j) {
            EXPECT_EQ_CUSTOM(matrixTranslateResult[i][j], expectedTranslateResult[i][j]);
        }
    }
}