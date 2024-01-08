/******************************************************************************
 * @file   GLESC::Math::MatrixTestTyped.cpp
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  @todo Add description of this file if needed
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

/**
 * @brief Generate next value for the matrix
 * @details It will generate numbers for the matrices for the tests. It's important to generate
 * the numbers in a way the matrix is invertible and the laplaceExpansionDeterminant is not zero.
 * @tparam MyType
 * @param i
 * @param j
 * @return The next value for the matrix given the row and column
 */
template <class MyType>
MyType generateNextValue(size_t i, size_t j) {
    if (i == j) { // Diagonal element
        return MyType(1);
    } else { // Off-diagonal element
        return MyType(i + j + i*j*7 + 7);
    }
}
template <class MyType, size_t N, size_t M>
void initializeMatrixWithValues(GLESC::Math::Matrix<MyType, N, M> &matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = generateNextValue<MyType>(i, j);
}
template <class MyType, size_t N, size_t M>
void initializeMatrixWithDifferentValues(GLESC::Math::Matrix<MyType, N, M> &matrix) {
    // Matrices will have the following format (i.e. 3x3):
    // |13 23 33|
    // |43 53 63|
    // |73 83 93|
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            matrix[i][j] = generateNextValue<MyType>(i + 10, j + 10);
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
        MatrixType<double, 10, 10>, MatrixType<float, 10, 10>,
        // Non-square matrices
        MatrixType<float, 2, 3>, MatrixType<double, 2, 3>,
        MatrixType<int, 2, 3>, MatrixType<size_t, 2, 3>,
        MatrixType<float, 3, 2>, MatrixType<double, 3, 2>,
        MatrixType<int, 3, 2>, MatrixType<size_t, 3, 2>,
        MatrixType<float, 4, 3>, MatrixType<double, 4, 3>
>;
template<class Type>
class MatrixTests : public testing::Test {
protected:
    MatrixTests() = default;
    void SetUp() override
    {initializeMatrixWithValues(this->matrix);
    initializeMatrixWithDifferentValues(this->matrix2);}
    void TearDown() override {}
    GLESC::Math::Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix;
    // For combined operations
    GLESC::Math::Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix2;
};

TYPED_TEST_SUITE(MatrixTests, MyTypes);

#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Rows; \
    constexpr size_t M = TypeParam::Cols; \
    using Mat = GLESC::Math::Matrix<Type, N, M>; \
    using VecN = Vector<Type, N>; \
    using VecM = Vector<Type, M>

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
    Mat matrixInitList;
    initializeMatrixWithValues(matrixInitList); // To avoid errors for dimensions
    // that are not checked with constexpr
    if constexpr (N==2 && M==2){
        matrixInitList = {{generateNextValue<Type>(0, 0), generateNextValue<Type>(0, 1)},
                          {generateNextValue<Type>(1, 0), generateNextValue<Type>(1, 1)}};
    }
    else if constexpr (N==3 && M==3){
        matrixInitList =
                {{generateNextValue<Type>(0, 0), generateNextValue<Type>(0, 1),
                        generateNextValue<Type>(0, 2)},
                 {generateNextValue<Type>(1, 0), generateNextValue<Type>(1, 1),
                         generateNextValue<Type>(1, 2)},
                 {generateNextValue<Type>(2, 0), generateNextValue<Type>(2, 1),
                         generateNextValue<Type>(2, 2)}};
    }
    else if constexpr (N==4 && M==4){
        matrixInitList =
                {{generateNextValue<Type>(0, 0), generateNextValue<Type>(0, 1),
                  generateNextValue<Type>(0, 2), generateNextValue<Type>(0, 3)},
                 {generateNextValue<Type>(1, 0), generateNextValue<Type>(1, 1),
                  generateNextValue<Type>(1, 2 ), generateNextValue<Type>(1, 3)},
                 {generateNextValue<Type>(2, 0), generateNextValue<Type>(2, 1),
                  generateNextValue<Type>(2, 2), generateNextValue<Type>(2, 3)},
                 {generateNextValue<Type>(3, 0), generateNextValue<Type>(3, 1),
                  generateNextValue<Type>(3, 2), generateNextValue<Type>(3, 3)}};
    }
    Mat expectedInitList;
    initializeMatrixWithValues(expectedInitList);
    EXPECT_EQ_MAT(matrixInitList, expectedInitList);
    
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
            EXPECT_EQ_CUSTOM(this->matrix[i][j], generateNextValue<Type>(i, j));
    
    // Const Getters ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix.get(i, j), generateNextValue<Type>(i, j));
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

TYPED_TEST(MatrixTests, Assignments){
    PREPARE_TEST();
    // Copy assignment
    Mat matrixCopyAssign;
    matrixCopyAssign = this->matrix;
    EXPECT_EQ_MAT(matrixCopyAssign, this->matrix);
    
    // Move assignment
    Mat matrixMoveAssign;
    matrixMoveAssign = std::move(this->matrix);
    EXPECT_EQ_MAT(matrixMoveAssign, this->matrix);

    // Operator += with matrix
    Mat matrixPlusEquals;
    initializeMatrixWithValues(matrixPlusEquals);
    matrixPlusEquals += this->matrix;
    EXPECT_EQ_MAT(matrixPlusEquals, (this->matrix + this->matrix));

    // Operator += with scalar
    Mat matrixPlusScalarEquals; initializeMatrixWithValues(matrixPlusScalarEquals);
    Type scalar = Type(2);
    matrixPlusScalarEquals += scalar;
    EXPECT_EQ_MAT(matrixPlusScalarEquals, (this->matrix + scalar));

    // Operator -= with matrix
    Mat matrixMinusEquals;
    initializeMatrixWithValues(matrixMinusEquals);
    matrixMinusEquals -= this->matrix;
    EXPECT_EQ_MAT(matrixMinusEquals, (this->matrix - this->matrix));

    // Operator -= with scalar
    Mat matrixMinusScalarEquals; initializeMatrixWithValues(matrixMinusScalarEquals);
    Type scalarMinus = Type(2);
    matrixMinusScalarEquals -= scalarMinus;
    EXPECT_EQ_MAT(matrixMinusScalarEquals, (this->matrix - scalarMinus));

    // Operator *= with matrix
    if constexpr (N==M){ // Only square matrices can be multiplied in place
        GLESC::Math::Matrix<Type, M, N> matrixMultEquals;
        initializeMatrixWithValues(matrixMultEquals);
        matrixMultEquals *= this->matrix;
        EXPECT_EQ_MAT(matrixMultEquals, (this->matrix * this->matrix));
    }
    // Operator *= with scalar
    Mat matrixMultScalarEquals; initializeMatrixWithValues(matrixMultScalarEquals);
    Type scalarMult = Type(2);
    matrixMultScalarEquals *= scalarMult;
    EXPECT_EQ_MAT(matrixMultScalarEquals, (this->matrix * scalarMult));

    // Operator /= with scalar
    Mat matrixDivScalarEquals; initializeMatrixWithValues(matrixDivScalarEquals);
    Type scalarDiv = Type(2);
    matrixDivScalarEquals /= scalarDiv;
    EXPECT_EQ_MAT(matrixDivScalarEquals, (this->matrix / scalarDiv));
    
    // Operator /= with matrix
    if constexpr (N==M){
        Mat matrixDivEquals; initializeMatrixWithValues(matrixDivEquals);
        std::cout<< "Dividing matrices:\n";
        matrixDivEquals /= this->matrix;
        Mat expectedDivEquals;
        initializeMatrixWithValues(expectedDivEquals);
        expectedDivEquals = expectedDivEquals * this->matrix.inverse();
        EXPECT_EQ_MAT(matrixDivEquals, expectedDivEquals);
        // Dividing by zero
        Mat matrixDivZero; initializeMatrixWithValues(matrixDivZero);
        EXPECT_THROW(matrixDivZero /= Mat(), MathException);
        EXPECT_THROW(matrixDivZero /= Type(0), MathException);
    }
}

TYPED_TEST(MatrixTests, ArithmeticOperators) {
    PREPARE_TEST();
    // ------------------------------ Addition -----------------------------

    // Addition operator
    Mat matrixAdditionResult = this->matrix + this->matrix;
    Mat expectedAddition = this->matrix; // Initialize it with identical values to this->matrix
    for (size_t i = 0; i < expectedAddition.rows(); ++i)
        for (size_t j = 0; j < expectedAddition.cols(); ++j)
            expectedAddition[i][j] *= 2;  // Double each element
    EXPECT_EQ_MAT(matrixAdditionResult, expectedAddition);

    // Addition operator with scalar
    Mat matrixAddScalarResult = this->matrix + 2;
    Mat expectedAddScalar = this->matrix; // Initialize it with identical values to this->matrix
    for (size_t i = 0; i < expectedAddScalar.rows(); ++i)
        for (size_t j = 0; j < expectedAddScalar.cols(); ++j)
            expectedAddScalar[i][j] += 2;  // Add 2 to each element
    EXPECT_EQ_MAT(matrixAddScalarResult, expectedAddScalar);

    // ------------------------------ Subtraction -----------------------------
    
    // Subtraction operator
    Mat matrixSubtrResult = this->matrix - this->matrix;
    Mat expectedSubtr = this->matrix; // Initialize it with zero values
    for (size_t i = 0; i < expectedSubtr.rows(); ++i)
        for (size_t j = 0; j < expectedSubtr.cols(); ++j)
            expectedSubtr[i][j] = 0;  // All elements should be zero
    EXPECT_EQ_MAT(matrixSubtrResult, expectedSubtr);

    // Subtraction operator with scalar
    Mat matrixSubtrScalarResult = this->matrix - 2;
    Mat expectedSubtrScalar = this->matrix;
    for (size_t i = 0; i < expectedSubtrScalar.rows(); ++i)
        for (size_t j = 0; j < expectedSubtrScalar.cols(); ++j)
            expectedSubtrScalar[i][j] -= 2;  // Subtract 2 from each element
    EXPECT_EQ_MAT(matrixSubtrScalarResult, expectedSubtrScalar);

    // Unary minus operator
    Mat matrixUnaryMinusResult = -this->matrix;
    Mat expectedUnaryMinus = this->matrix;
    for (size_t i = 0; i < expectedUnaryMinus.rows(); ++i)
        for (size_t j = 0; j < expectedUnaryMinus.cols(); ++j)
            expectedUnaryMinus[i][j] = -expectedUnaryMinus[i][j];  // Negate each element
    EXPECT_EQ_MAT(matrixUnaryMinusResult, expectedUnaryMinus);

    // ------------------------------ Multiplication -----------------------------

    // Multiplication operator (dot product)
    if constexpr (N == M) {
        Mat matrixMultResult = this->matrix * this->matrix;
        Mat expectedMultResult;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                expectedMultResult[i][j] = 0;
                for (size_t k = 0; k < N; ++k) {
                    expectedMultResult[i][j] += this->matrix[i][k] * this->matrix[k][j];
                }
            }
        }
        EXPECT_EQ_MAT(matrixMultResult, expectedMultResult);
    }

    // Multiplication operator with scalar
    Mat matrixMultScalarResult = this->matrix * 2;
    Mat expectedMultScalar = this->matrix;
    for (size_t i = 0; i < expectedMultScalar.rows(); ++i)
        for (size_t j = 0; j < expectedMultScalar.cols(); ++j)
            expectedMultScalar[i][j] *= 2;  // Multiply each element by 2
    EXPECT_EQ_MAT(matrixMultScalarResult, expectedMultScalar);

    // ----------------------------------------- Division ------------------------------------------
    // Division operator
    if constexpr (N == M) {
        Mat matrixDivResult = this->matrix2 / this->matrix;
        Mat expectedDivResult = this->matrix2;
        expectedDivResult *= this->matrix.inverse();
        EXPECT_EQ_MAT(matrixDivResult, expectedDivResult);
        
        // Division operator with scalar
        Mat matrixDivScalarResult = this->matrix / 2;
        Mat expectedDivScalarResult = this->matrix;
        for (size_t i = 0; i < expectedDivScalarResult.rows(); ++i)
            for (size_t j = 0; j < expectedDivScalarResult.cols(); ++j)
                expectedDivScalarResult[i][j] /= 2;  // Divide each element by 2
        EXPECT_EQ_MAT(matrixDivScalarResult, expectedDivScalarResult);
        
        // Division by zero
        Mat matrixDivZero; initializeMatrixWithValues(matrixDivZero);
        Mat zeroMatrix;
        EXPECT_THROW(matrixDivZero / zeroMatrix, MathException);
        EXPECT_THROW(matrixDivZero / Type(0), MathException);
    }
}

TYPED_TEST(MatrixTests, Determinan){
    PREPARE_TEST();
    // Determinant
    if constexpr (N==M){
        Type matrixDeterminantResult = this->matrix.determinant();
        Type expectedDeterminantResult =
                MatrixAlgorithms::laplaceExpansionDeterminant(this->matrix);
        EXPECT_EQ_CUSTOM(matrixDeterminantResult,
                      expectedDeterminantResult);
    }
}

TYPED_TEST(MatrixTests, Transpose){
    PREPARE_TEST();
    // Transpose
    GLESC::Math::Matrix<Type, M,N> matrixTransposeResult = this->matrix.transpose();
    GLESC::Math::Matrix<Type, M,N> expectedTransposeResult;
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            expectedTransposeResult[j][i] = this->matrix[i][j];
    EXPECT_EQ_MAT(matrixTransposeResult, expectedTransposeResult);
}

TYPED_TEST(MatrixTests, Inverse){
    PREPARE_TEST();
    // Inverse
    if constexpr (N==M){
        Mat matrixInverseResult = this->matrix.inverse();
        Mat expectedInverseResult = MatrixAlgorithms::gaussianInverse(this->matrix);
    }
}

TYPED_TEST(MatrixTests, MatrixTranslate){
    PREPARE_TEST();
    // ---------------------------------- Matrix transformations -----------------------------------
    // All transformations need to be tested only for square matrices
    if constexpr (N==M) {
        // Translate
        auto translateVec = VectorT<Type, N - 1>(1);
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
}

TYPED_TEST(MatrixTests, MatrixScale){
    PREPARE_TEST();
    // Scale
    auto scaleVec = VectorT<Type, N - 1>(2);
    Mat matrixScaleResult = this->matrix.scale(scaleVec);
    Mat expectedScaleResult = this->matrix;
    
    for (size_t i = 0; i < N - 1; ++i) {
        expectedScaleResult[i][i] += scaleVec[i];
        
    }
    
    EXPECT_EQ_MAT(matrixScaleResult, expectedScaleResult);
}

TYPED_TEST(MatrixTests, MatrixRotate){
    PREPARE_TEST();
    // Rotate
    // Only defined (or necessary) for 3x3 and 4x4 matrices
    if constexpr (N == 3 && M == 3) {
        Type angle = GLESC::Math::PI/4; // 45 degree rotation for instance
        Mat matrixRotateResult = this->matrix.rotate(angle);
        
        Mat expectedRotateResult(MatrixAlgorithms::rotate2D(this->matrix, angle));
        
        EXPECT_EQ_MAT(matrixRotateResult, expectedRotateResult);
    }else if constexpr (N == 4 && M == 4) {
        Type angle = GLESC::Math::PI/4; // 45 degree rotation for instance
        Vector<Type, 3> axis(0, 0, 1); // Rotation about the z-axis
        Mat matrixRotateResult = this->matrix.rotate(axis * angle);
        
        Mat expectedRotateResult(MatrixAlgorithms::rotate3D(this->matrix, axis * angle));
        
        EXPECT_EQ_MAT(matrixRotateResult, expectedRotateResult);
    }
}
/*
TYPED_TEST(MatrixTests, Functions){
    PREPARE_TEST();
    // Determinant
    if constexpr (N==M){
        Type matrixDeterminantResult = this->matrix.determinant();
        Type expectedDeterminantResult =
                MatrixAlgorithms::laplaceExpansionDeterminant(this->matrix);
        EXPECT_EQ_CUSTOM(matrixDeterminantResult,
                      expectedDeterminantResult);
    }
    
    // Transpose
    GLESC::Math::Matrix<Type, M,N> matrixTransposeResult = this->matrix.transpose();
    GLESC::Math::Matrix<Type, M,N> expectedTransposeResult;
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            expectedTransposeResult[j][i] = this->matrix[i][j];
    EXPECT_EQ_MAT(matrixTransposeResult, expectedTransposeResult);
    
    // Inverse
    if constexpr (N==M){
        Mat matrixInverseResult = this->matrix.inverse();
        Mat expectedInverseResult = MatrixAlgorithms::gaussianInverse(this->matrix);
    }
    
    // ---------------------------------- Matrix transformations -----------------------------------
    // All transformations need to be tested only for square matrices
    if constexpr (N==M){
        // Translate
        auto translateVec=VectorT<Type, N - 1>(1);
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
        
        // Scale
        auto scaleVec=VectorT<Type, N - 1>(2);
        Mat matrixScaleResult = this->matrix.scale(scaleVec);
        Mat expectedScaleResult = this->matrix;
        
        for (size_t i = 0; i < N - 1; ++i) {
            expectedScaleResult[i][i] += scaleVec[i];
            
        }
        
        EXPECT_EQ_MAT(matrixScaleResult, expectedScaleResult);
        
        
        // Rotate
        // Only defined (or necessary) for 3x3 and 4x4 matrices
        if constexpr (N == 3 && M == 3) {
            Type angle = GLESC::Math::PI/4; // 45 degree rotation for instance
            Mat matrixRotateResult = this->matrix.rotate(angle);
            
            Mat expectedRotateResult(MatrixAlgorithms::rotate2D(this->matrix, angle));
            
            EXPECT_EQ_MAT(matrixRotateResult, expectedRotateResult);
        }else if constexpr (N == 4 && M == 4) {
            Type angle = GLESC::Math::PI/4; // 45 degree rotation for instance
            Vector<Type, 3> axis(0, 0, 1); // Rotation about the z-axis
            Mat matrixRotateResult = this->matrix.rotate(axis * angle);
            
            Mat expectedRotateResult(MatrixAlgorithms::rotate3D(this->matrix, axis * angle));
            
            EXPECT_EQ_MAT(matrixRotateResult, expectedRotateResult);
        }
        
        // LookAt
        if constexpr (N == 3){
            Vector<Type, 2> target(4, -12);
            Mat matrixLookAtResult = this->matrix.lookAt(target);
            Mat expectedLookAtResult;
            expectedLookAtResult = MatrixAlgorithms::lookAt2D(this->matrix, target);
            
            EXPECT_EQ_MAT(matrixLookAtResult, expectedLookAtResult);
        
        }
        else if constexpr (N == 4) {
            Vector<Type, 3> target(-3, 12, 1);
            Vector<Type, 3> up(0, 1, 0);
            Mat matrixLookAtResult = this->matrix.lookAt(target, up);
            Mat expectedLookAtResult;
            expectedLookAtResult = MatrixAlgorithms::lookAt3D(this->matrix, target, up);
            
            EXPECT_EQ_MAT(matrixLookAtResult, expectedLookAtResult);
        }

    }
    
}

*/


TYPED_TEST(MatrixTests, Rank){
    PREPARE_TEST();
    // Rank
    if constexpr (N==M){
        size_t matrixRankResult = this->matrix.rank();
        size_t expectedRankResult =
                MatrixAlgorithms::gaussianEliminationRank(this->matrix);
        EXPECT_EQ_CUSTOM(matrixRankResult,
                      expectedRankResult);
    }
}

// ------------------------------ Exact solutions -----------------------------
TEST(MatrixTests, ExactSolutionDeterminant){
    // Zero determinant - All elements of a row are zero
    GLESC::Math::Matrix<double, 3, 3> matrix1{
            {1, 2, 3},
            {0, 0, 0},
            {7, 8, 9}
    };
    double expectedDeterminant1 = 0;
    EXPECT_EQ_CUSTOM(matrix1.determinant(), expectedDeterminant1);
    
    // 2. Zero determinant - Two rows are identical
    GLESC::Math::Matrix<double, 3, 3> matrix2{
            {1, 2, 3},
            {1, 2, 3},
            {7, 8, 9}
    };
    double expectedDeterminant2 = 0;
    EXPECT_EQ_CUSTOM(matrix2.determinant(), expectedDeterminant2);

    
    // Zero determinant - Two rows are proportional
    GLESC::Math::Matrix<double, 3, 3> matrix4{
            {1, 2, 3},
            {2, 4, 6},
            {7, 8, 9}
    };
    double expectedDeterminant4 = 0;
    EXPECT_EQ_CUSTOM(matrix4.determinant(), expectedDeterminant4);
    
    // Determinant of a 2x2 matrix
    GLESC::Math::Matrix<double, 2, 2> matrix5{
            {1, 2},
            {3, 4}
    };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%7D%2C%7B3%2C4%7D%7D
    double expectedDeterminant5 = -2;
    EXPECT_EQ_CUSTOM(matrix5.determinant(), expectedDeterminant5);
    
    // Determinant of a 3x3 matrix
    GLESC::Math::Matrix<double, 3, 3> matrix6{
            {-1, 2, 3},
            {4, 5, -6},
            {7, -8, 9}
    };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B-1%2C2%2C3%7D%2C%7B4%2C5%2C-6%7D%2C%7B7%2C-8%2C9%7D%7D
    double expectedDeterminant6 = -354;
    EXPECT_EQ_CUSTOM(matrix6.determinant(), expectedDeterminant6);
    
    // Determinant of a 4x4 matrix
    GLESC::Math::Matrix<double, 4, 4> matrix7{
                {1, 2, 3, -4},
                {-5, 6, 7, 8},
                {9, 15, -1, 2},
                {3, -4, 5, 6}
        };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%2C3%2C-4%7D%2C%7B-5%2C6%2C7%2C8%7D%2C%7B9%2C15%2C-1%2C2%7D%2C%7B3%2C-4%2C5%2C6%7D%7D
    double expectedDeterminant7 = -9588;
    EXPECT_EQ_CUSTOM(matrix7.determinant(), expectedDeterminant7);
    
    // Determinant of a 5x5 matrix
    GLESC::Math::Matrix<double, 5, 5> matrix8{
            {-1, 2, 3, 4, 5},
            {6, 7, 8, -9, 0},
            {11, -21, 31, -41, 51},
            {-61, 71, 81, 91, 10},
            {11.1, 32.1, -53.1, 64.1, -75.1}
    };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B-1%2C2%2C3%2C4%2C5%7D%2C%7B6%2C7%2C8%2C-9%2C0%7D%2C%7B11%2C-21%2C31%2C-41%2C51%7D%2C%7B-61%2C71%2C81%2C91%2C10%7D%2C%7B11.1%2C32.1%2C-53.1%2C64.1%2C-75.1%7D%7D
    double expectedDeterminant8 = -6.344832400000001* pow(10,6);
    EXPECT_EQ_CUSTOM(matrix8.determinant(), expectedDeterminant8);
    
}

TEST(MatrixTests, ExactSolutionInverse){
    // Inverse of a 2x2 matrix
    GLESC::Math::Matrix<double, 2, 2> matrix1{
            {1, 2},
            {3, 4}
    };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%7D%2C%7B3%2C4%7D%7D
    GLESC::Math::Matrix<double, 2, 2> expectedInverse1{
            {-2, 1},
            {1.5, -0.5}
    };
    EXPECT_EQ_MAT(matrix1.inverse(), expectedInverse1);
    
    // Inverse of a 3x3 matrix
    GLESC::Math::Matrix<double, 3, 3> matrix2{
            {1, 2, -3},
            {-3, 4, -5},
            {7, -8, 9}
    };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%2C-3%7D%2C%7B-3%2C4%2C-5%7D%2C%7B7%2C-8%2C9%7D%7D
    GLESC::Math::Matrix<double, 3, 3> expectedInverse2{
            {0.5, -0.75, -0.25},
            {1, -3.75, -1.75},
            {0.5, -2.75, -1.25}
    };
    EXPECT_EQ_MAT(matrix2.inverse(), expectedInverse2);
    
    // Inverse of a 4x4 matrix
    GLESC::Math::Matrix<double, 4, 4> matrix3{
            {1, 2, 3, -4},
            {-5, 6, 7, 8},
            {9, 15, -1, 2},
            {3, -4, 5, 6}
    };
    //https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%2C3%2C-4%7D%2C%7B-5%2C6%2C7%2C8%7D%2C%7B9%2C15%2C-1%2C2%7D%2C%7B3%2C-4%2C5%2C6%7D%7D
    GLESC::Math::Matrix<double, 4, 4> expectedInverse3{
            {0.0223196, -0.0636212, 0.0450563, 0.0846892},
            {0.01335, 0.0367126, 0.0362954, -0.0521485},
            {0.148728, 0.0340008, -0.0175219, 0.0596579},
            {-0.126199, 0.0279516, 0.0162703, 0.0398415}
    };
    EXPECT_EQ_MAT(matrix3.inverse(), expectedInverse3);
    
    // Inverse of a 5x5 matrix
    GLESC::Math::Matrix<double, 5, 5> matrix4{
            {-1, 2, 3, 4, 5},
            {6, 7, 8, -9, 0},
            {11, -21, 31, -41, 51},
            {-61, 71, 81, 91, 10},
            {11.1, 32.1, -53.1, 64.1, -75.1}
    };
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B-1%2C2%2C3%2C4%2C5%7D%2C%7B6%2C7%2C8%2C-9%2C0%7D%2C%7B11%2C-21%2C31%2C-41%2C51%7D%2C%7B-61%2C71%2C81%2C91%2C10%7D%2C%7B11.1%2C32.1%2C-53.1%2C64.1%2C-75.1%7D%7D
    GLESC::Math::Matrix<double, 5, 5> expectedInverse4{
            {-0.0935895, -0.0085282, 0.0719947, 0.00517271, 0.043349},
            {0.351945, 0.119422, -0.0858807, -0.0162524, -0.0370535},
            {-0.326954, -0.0438212, 0.0777137, 0.02122, 0.0338326},
            {-0.0792838, -0.0628653, 0.0502792, 0.00966992, 0.0301534},
            {0.300103, 0.0271107, -0.0381003, -0.0129324, -0.020931}
    };
    EXPECT_EQ_MAT(matrix4.inverse(), expectedInverse4);
}

TEST(MatrixTests, ExactSolutionTranslate){
    // Translation of a 3x3 matrix
    GLESC::Math::Matrix<double, 3, 3> transform2D{
            {1, 2, -3},
            {-3, 4, -5},
            {7, -8, 9}
    };
    VectorT<double, 2> translateVec2D(1, 2);
    // Must increase the last column by the translation vector
    GLESC::Math::Matrix<double, 3, 3> expectedTranslate2D{
            {1, 2, -2},
            {-3, 4, -5},
            {7, -8, 9}
    };
    expectedTranslate2D = expectedTranslate2D.translate(translateVec2D);
    EXPECT_EQ_MAT(expectedTranslate2D, expectedTranslate2D);

    // Translation of a 4x4 matrix
    GLESC::Math::Matrix<double, 4, 4> transform3D{
            {1, 2, -3, 4},
            {-3, 4, -5, 6},
            {7, -8, 9, 10},
            {11, 12, 13, 14}
    };
    VectorT<double, 3> translate3D(1, 2, 3);
    GLESC::Math::Matrix<double, 4, 4> expectedTranslate3D{
            {1, 2, -3, 5},
            {-3, 4, -5, 8},
            {7, -8, 9, 13},
            {11, 12, 13, 14}
    };
    expectedTranslate3D = expectedTranslate3D.translate(translate3D);
    EXPECT_EQ_MAT(expectedTranslate3D, expectedTranslate3D);
}

TEST(MatrixTests, ExactSolutionScale){
    // Translation of a 3x3 matrix
    GLESC::Math::Matrix<double, 3, 3> scale2D{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    VectorT<double, 2> scaleVec2D(1, 2);
    // Must increase (add +) diagonal elements (expect the last one) by the scale vector
    GLESC::Math::Matrix<double, 3, 3> expectedScale2D{
            {2, 2, 3},
            {4, 7, 6},
            {7, 8, 9}
    };
    scale2D = scale2D.scale(scaleVec2D);
    EXPECT_EQ_MAT(scale2D, expectedScale2D);
    
    // Translation of a 4x4 matrix
    GLESC::Math::Matrix<double, 4, 4> scale3D{
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    VectorT<double, 3> scaleVec3D(1, 2, 3);
    GLESC::Math::Matrix<double, 4, 4> expectedScale3D{
            {2, 2, 3, 4},
            {5, 8, 7, 8},
            {9, 10, 14, 12},
            {13, 14, 15, 16}
    };
    scale3D = scale3D.scale(scaleVec3D);
    EXPECT_EQ_MAT(scale3D, expectedScale3D);
}

TEST(MatrixTests, ExactSolutionRotate){
    // Rotation of a 3x3 matrix
    GLESC::Math::Matrix<double, 3, 3> rotate2D{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    double dgrs = GLESC::Math::PI/4; // 45 degree rotation for instance
    rotate2D = rotate2D.rotate(dgrs);
    GLESC::Math::Matrix<double, 3, 3> expectedRotate2D = {
            {-2.12132034, -2.12132034, -2.12132034},
            {3.53553391, 4.94974747, 6.36396103},
            {7, 8, 9}
    };
    EXPECT_EQ_MAT(rotate2D, expectedRotate2D);
    
    
    // Rotation of a 4x4 matrix
    GLESC::Math::Matrix<double, 4, 4> rotate3D{
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    VectorT<double, 3> axis(0, 0, 1); // Rotation about the z-axis
    double dgrs3D = GLESC::Math::PI/4; // 45 degree rotation for instance
    rotate3D = rotate3D.rotate(axis * dgrs3D);
    
    GLESC::Math::Matrix<double, 4, 4> expectedRotate3D = {
            {-2.82842712, -2.82842712, -2.82842712, -2.82842712},
            {4.24264069, 5.65685425, 7.07106781, 8.48528137},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    EXPECT_EQ_MAT(rotate3D, expectedRotate3D);
}

TEST(MatrixTests, ExactSolutionLookAt){
    // LookAt for a 3x3 matrix (2D transformation)
    GLESC::Math::Matrix<double, 3, 3> matrix2D{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
    };
    VectorT<double, 2> target2D(1, 1);
    
    matrix2D = matrix2D.lookAt(target2D);
    
    GLESC::Math::Matrix<double, 3, 3> expectedLookAt2D = {
            {0.70710678, 0.70710678, 0.0},
            {-0.70710678, 0.70710678, 0.0},
            {0.0, 0.0, 1.0}
    };
    
    EXPECT_EQ_MAT(matrix2D, expectedLookAt2D);
    
    // LookAt for a 4x4 matrix
    GLESC::Math::Matrix<double, 4, 4> matrix3D{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
    VectorT<double, 3> target3D(1, 3, -1);
    VectorT<double, 3> up(0, 1, 0);
    
    matrix3D = matrix3D.lookAt(target3D, up);
    
    GLESC::Math::Matrix<double, 4, 4> expectedLookAt3D = {
            {0.70710678, -0.63960215, -0.30151134, 0.0},
            {0.0, 0.42640143, -0.90453403, 0.0},
            {0.70710678, 0.63960215, 0.30151134, 0.0},
            {0.0, 0.0, 0.0, 1.0}
    };
    
    EXPECT_EQ_MAT(matrix3D, expectedLookAt3D);
}