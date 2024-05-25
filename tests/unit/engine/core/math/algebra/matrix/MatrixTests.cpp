/******************************************************************************
 * @file   MatrixTests.cpp
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <gtest/gtest.h>
#include "engine/core/math/algebra/matrix/MatrixAlgorithms.h"
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"
#include "unit/engine/core/math/algebra/matrix/MatrixTestsHelper.cpp"
#ifdef MATH_ALGEBRA_UNIT_TESTING
template <class Type>
class MatrixTests : public testing::Test {
protected:
    MatrixTests() = default;

    void SetUp() override {
        initializeMatrixWithValues(this->matrix);
        initializeMatrixWithDifferentValues(this->matrix2);
    }

    void TearDown() override {
    }

    GLESC::Math::Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix;
    // For combined operations
    GLESC::Math::Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix2;
};


TYPED_TEST_SUITE(MatrixTests, MyTypes);


TYPED_TEST(MatrixTests, DefaultConstructors) {
    PREPARE_TEST();
    // Default constructor
    Mat matrixDefault;
    Mat expectedDefault;
    GLESC::Math::MatrixAlgorithms::setMatrixZero(expectedDefault.data);
    EXPECT_EQ_MAT(matrixDefault, expectedDefault);
}

TYPED_TEST(MatrixTests, DiagonalConstructors) {
    PREPARE_TEST();
    if constexpr (N == M) {
        // Diagonal constructor
        Type diagonalValue = 100;
        Mat diagonalMat(diagonalValue);
        Mat expectedDiagonal;
        GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(expectedDiagonal.data, diagonalValue);
        EXPECT_EQ_MAT(diagonalMat, expectedDiagonal);
    }
}

TYPED_TEST(MatrixTests, ArrayConstructors) {
    PREPARE_TEST();
    // Array constructor
    Type arrayValues[N][M];
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            arrayValues[i][j] = this->matrix[i][j];

    Mat matrixArray(arrayValues);
    Mat expectedArray = this->matrix;
    GLESC::Math::MatrixAlgorithms::setMatrix(expectedArray.data, arrayValues);
    EXPECT_EQ_MAT(matrixArray, expectedArray);
}

TYPED_TEST(MatrixTests, CopyConstructors) {
    PREPARE_TEST();
    // Copy constructor
    Mat matrixCopy(this->matrix);
    Mat matrixCopyReference;
    EXPECT_EQ_MAT(matrixCopy, this->matrix);
}

TYPED_TEST(MatrixTests, MoveConstructors) {
    PREPARE_TEST();
    // Move constructor
    Mat matrixMove(std::move(this->matrix));
    EXPECT_EQ_MAT(matrixMove, this->matrix);
}

TYPED_TEST(MatrixTests, RowsAndColsAccessors) {
    PREPARE_TEST();
    // Get rows
    EXPECT_EQ_CUSTOM(this->matrix.rows(), N);

    // Get cols
    EXPECT_EQ_CUSTOM(this->matrix.cols(), M);
}

TYPED_TEST(MatrixTests, BracketAccessor) {
    PREPARE_TEST();

    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Testing get over []%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    // Operator [] ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix[i][j], generateNextValue<Type>(i, j));

    S_ASSERT_TRUE((std::is_same_v<decltype(this->matrix[0][0]), Type &>),
                  "Operator [] must return a reference");
}

TYPED_TEST(MatrixTests, GetAccessor) {
    PREPARE_TEST();
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Testing const getters%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    // Const Getters ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix.get(i, j), generateNextValue<Type>(i, j));

    // Getters must return a const reference
    S_ASSERT_TRUE((std::is_same_v<decltype(this->matrix.get(0, 0)), const Type &>),
                  "Getters (index1, index2) must return a const reference to the matrix element");

    S_ASSERT_TRUE((std::is_same_v<decltype(this->matrix.get(0)), const GLESC::Math::MatrixRow<Type, M> &>),
                  "Getter (index) must return a const reference to the matrix row");
}

TYPED_TEST(MatrixTests, EqualityOperators) {
    PREPARE_TEST();
    // Equality operator
    Mat matrixEquals;
    initializeMatrixWithValues(matrixEquals);
    EXPECT_EQ(this->matrix, matrixEquals);
}

TYPED_TEST(MatrixTests, InequalityOperators) {
    PREPARE_TEST();
    // Inequality operator
    Mat matrixNotEquals;
    initializeMatrixWithValues(matrixNotEquals);
    matrixNotEquals[0][0] += Type(1);
    EXPECT_NE(this->matrix, matrixNotEquals);
}

TYPED_TEST(MatrixTests, CopyAssignment) {
    PREPARE_TEST();
    // Copy assignment
    Mat matrixCopyAssign;
    matrixCopyAssign = this->matrix;
    EXPECT_EQ_MAT(matrixCopyAssign, this->matrix);
}

TYPED_TEST(MatrixTests, MoveAssignment) {
    PREPARE_TEST();
    // Move assignment
    Mat matrixMoveAssign;
    matrixMoveAssign = std::move(this->matrix);
    EXPECT_EQ_MAT(matrixMoveAssign, this->matrix);
}

TYPED_TEST(MatrixTests, AddAssignment) {
    PREPARE_TEST();
    // Operator += with matrix
    Mat matrixPlusEquals;
    initializeMatrixWithValues(matrixPlusEquals);
    matrixPlusEquals += this->matrix;
    EXPECT_EQ_MAT(matrixPlusEquals, (this->matrix + this->matrix));
}

TYPED_TEST(MatrixTests, AddScalarAssignment) {
    PREPARE_TEST();
    // Operator += with scalar
    Mat matrixPlusScalarEquals = this->matrix;
    Type scalar = Type(2);
    matrixPlusScalarEquals += scalar;
    EXPECT_EQ_MAT(matrixPlusScalarEquals, (this->matrix + scalar));
}

TYPED_TEST(MatrixTests, SubAssignment) {
    PREPARE_TEST();
    // Operator -= with matrix
    Mat matrixMinusEquals = this->matrix;
    matrixMinusEquals -= this->matrix;
    EXPECT_EQ_MAT(matrixMinusEquals, (this->matrix - this->matrix));

    Mat matrixMinusEquals2 = this->matrix2;
    matrixMinusEquals2 -= this->matrix;
    EXPECT_EQ_MAT(matrixMinusEquals2, (this->matrix2 - this->matrix));
}

TYPED_TEST(MatrixTests, SubScalarAssignment) {
    PREPARE_TEST();
    // Operator -= with scalar
    Mat matrixMinusScalarEquals = this->matrix;
    Type scalarMinus = Type(2);
    matrixMinusScalarEquals -= scalarMinus;
    EXPECT_EQ_MAT(matrixMinusScalarEquals, (this->matrix - scalarMinus));
}

TYPED_TEST(MatrixTests, MultAssignment) {
    PREPARE_TEST();
    if constexpr (N == M) {
        Mat matrixToMultiplyWith = this->matrix;
        // Operator *= with matrix
        Mat matrixMultAssign = this->matrix;
        matrixMultAssign *= matrixToMultiplyWith;

        //
        auto expectedMultAssign = this->matrix;
        GLESC::Math::MatrixAlgorithms::matrixMatrixMulInPlace(expectedMultAssign.data, matrixToMultiplyWith.data,
                                                              expectedMultAssign.data);
        EXPECT_EQ_MAT(matrixMultAssign, expectedMultAssign);
    }
}

TYPED_TEST(MatrixTests, MultScalarAssignment) {
    PREPARE_TEST();
    // Operator *= with scalar
    Mat matrixMultScalarEquals = this->matrix;
    Type scalarMult = Type(2);
    matrixMultScalarEquals *= scalarMult;
    EXPECT_EQ_MAT(matrixMultScalarEquals, (this->matrix * scalarMult));
}

TYPED_TEST(MatrixTests, DivAssignment) {
    PREPARE_TEST();
    // Operator /= with matrix
    // Only square matrices can be divided in place
    // And only dimensions 2, 3 and 4 are supported due to the implementation of the inverse
    if constexpr (N == M && N <= 4) {
        Mat matrixDivEquals = this->matrix2;
        matrixDivEquals /= this->matrix;

        Mat expectedDivEquals = this->matrix2;
        GLESC::Math::MatrixAlgorithms::matrixMatrixDiv(expectedDivEquals.data, this->matrix.data,
                                                       expectedDivEquals.data);
        EXPECT_EQ_MAT(matrixDivEquals, expectedDivEquals);

        // Dividing by zero
        Mat matrixDivZero = this->matrix;
        EXPECT_THROW(matrixDivZero /= Mat(), MathException);
    }
}

TYPED_TEST(MatrixTests, DivScalarAssignment) {
    PREPARE_TEST();
    // Operator /= with scalar
    Mat matrixDivScalarEquals;
    initializeMatrixWithValues(matrixDivScalarEquals);
    Type scalarDiv = Type(2);
    matrixDivScalarEquals /= scalarDiv;
    EXPECT_EQ_MAT(matrixDivScalarEquals, (this->matrix / scalarDiv));

    // Dividing by zero
    Mat matrixDivZero = this->matrix;
    EXPECT_THROW(matrixDivZero /= Type(0), MathException);
}

TYPED_TEST(MatrixTests, AddOperator) {
    PREPARE_TEST();
    std::cout <<
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Testing + operator with matrix%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    // Addition operator
    Mat matrixAdditionResult = this->matrix + this->matrix;
    Mat expectedAddition = this->matrix; // Initialize it with identical values to this->matrix
    for (size_t i = 0; i < expectedAddition.rows(); ++i)
        for (size_t j = 0; j < expectedAddition.cols(); ++j)
            expectedAddition[i][j] *= 2; // Double each element
    EXPECT_EQ_MAT(matrixAdditionResult, expectedAddition);
}

TYPED_TEST(MatrixTests, AddScalarOperator) {
    PREPARE_TEST();
    // Addition operator with scalar
    Mat matrixAddScalarResult = this->matrix + 2;
    Mat expectedAddScalar = this->matrix; // Initialize it with identical values to this->matrix
    for (size_t i = 0; i < expectedAddScalar.rows(); ++i)
        for (size_t j = 0; j < expectedAddScalar.cols(); ++j)
            expectedAddScalar[i][j] += 2; // Add 2 to each element
    EXPECT_EQ_MAT(matrixAddScalarResult, expectedAddScalar);
}

TYPED_TEST(MatrixTests, SubOperator) {
    PREPARE_TEST();
    // Subtraction operator
    Mat matrixSubstrResult = this->matrix - this->matrix;
    Mat expectedSubstr = this->matrix; // Initialize it with zero values
    for (size_t i = 0; i < expectedSubstr.rows(); ++i)
        for (size_t j = 0; j < expectedSubstr.cols(); ++j)
            expectedSubstr[i][j] = 0; // All elements should be zero
    EXPECT_EQ_MAT(matrixSubstrResult, expectedSubstr);
}

TYPED_TEST(MatrixTests, SubScalarOperator) {
    PREPARE_TEST();
    // Subtraction operator with scalar
    Mat matrixSubtrScalarResult = this->matrix - 2;
    Mat expectedSubtrScalar = this->matrix;
    for (size_t i = 0; i < expectedSubtrScalar.rows(); ++i)
        for (size_t j = 0; j < expectedSubtrScalar.cols(); ++j)
            expectedSubtrScalar[i][j] -= 2; // Subtract 2 from each element
    EXPECT_EQ_MAT(matrixSubtrScalarResult, expectedSubtrScalar);
}

TYPED_TEST(MatrixTests, UnaryMinusOperator) {
    PREPARE_TEST();
    // Unary minus operator
    Mat matrixUnaryMinusResult = -this->matrix;
    Mat expectedUnaryMinus = this->matrix;
    for (size_t i = 0; i < expectedUnaryMinus.rows(); ++i)
        for (size_t j = 0; j < expectedUnaryMinus.cols(); ++j)
            expectedUnaryMinus[i][j] = -expectedUnaryMinus[i][j]; // Negate each element
    EXPECT_EQ_MAT(matrixUnaryMinusResult, expectedUnaryMinus);
}

TYPED_TEST(MatrixTests, MulOperator) {
    PREPARE_TEST();
    // Multiplication operator (dot product)
    constexpr auto X = 4;


    if constexpr (GLESC::Math::MatrixAlgorithms::colMajorMatrix) {
        GLESC::Math::Matrix<Type, M, N> matrixToMultiplyLeft;
        initializeMatrixWithValues(matrixToMultiplyLeft);

        GLESC::Math::Matrix<Type, X, M> matrixToMultiplyRight;
        initializeMatrixWithValues(matrixToMultiplyRight);


        GLESC::Math::Matrix<Type, X, N> expectedMultResult;
        GLESC::Math::Matrix<Type, X, N> actualMultResult;

        actualMultResult = matrixToMultiplyLeft * matrixToMultiplyRight;
        GLESC::Math::MatrixAlgorithms::matrixMatrixMulColMaj(matrixToMultiplyLeft.data, matrixToMultiplyRight.data,
                                                             expectedMultResult.data);
        EXPECT_EQ_MAT(actualMultResult, expectedMultResult);
    }
    else {
        GLESC::Math::Matrix<Type, N, M> matrixToMultiplyLeft;
        initializeMatrixWithValues(matrixToMultiplyLeft);

        GLESC::Math::Matrix<Type, M, X> matrixToMultiplyRight;
        initializeMatrixWithValues(matrixToMultiplyRight);

        GLESC::Math::Matrix<Type, N, X> expectedMultResult;
        GLESC::Math::Matrix<Type, N, X> actualMultResult;

        actualMultResult = matrixToMultiplyLeft * matrixToMultiplyRight;
        GLESC::Math::MatrixAlgorithms::matrixMatrixMulRowMaj(matrixToMultiplyLeft, matrixToMultiplyRight.data,
                                                             expectedMultResult.data);
        EXPECT_EQ_MAT(actualMultResult, expectedMultResult);
    }
}

TYPED_TEST(MatrixTests, MulScalarOperator) {
    PREPARE_TEST();
    // Multiplication operator with scalar
    Type scalar = Type(2);
    Mat matrixMultScalarResult = this->matrix * scalar;
    Mat expectedMultScalar = this->matrix;
    GLESC::Math::MatrixAlgorithms::matrixScalarMul(this->matrix.data, scalar, expectedMultScalar.data);
    EXPECT_EQ_MAT(matrixMultScalarResult, expectedMultScalar);
}

TYPED_TEST(MatrixTests, DivOperator) {
    PREPARE_TEST();
    // ----------------------------------------- Division ------------------------------------------
    // Division operator
    // Only square matrices can be divided
    // And only dimensions 2, 3 and 4 are supported due to the implementation of the inverse
    if constexpr (N == M && (N == 2 || N == 3 || N == 4)) {
        Mat matrixDivResult = this->matrix2 / this->matrix;
        Mat expectedDivResult = this->matrix2;
        expectedDivResult *= this->matrix.inverse();
        EXPECT_EQ_MAT(matrixDivResult, expectedDivResult);

        // Division operator with scalar
        Mat matrixDivScalarResult = this->matrix / 2;
        Mat expectedDivScalarResult = this->matrix;
        for (size_t i = 0; i < expectedDivScalarResult.rows(); ++i)
            for (size_t j = 0; j < expectedDivScalarResult.cols(); ++j)
                expectedDivScalarResult[i][j] /= 2; // Divide each element by 2
        EXPECT_EQ_MAT(matrixDivScalarResult, expectedDivScalarResult);

        // Division by zero
        Mat matrixDivZero;
        initializeMatrixWithValues(matrixDivZero);
        Mat zeroMatrix;
        EXPECT_THROW(matrixDivZero / zeroMatrix, MathException);
        EXPECT_THROW(matrixDivZero / Type(0), MathException);
    }
}

TYPED_TEST(MatrixTests, Determinan) {
    PREPARE_TEST();
    // Determinant
    if constexpr (N == M) {
        Type matrixDeterminantResult = this->matrix.determinant();
        Type expectedDeterminantResult =
            GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(this->matrix.data);
        EXPECT_EQ_CUSTOM(matrixDeterminantResult, expectedDeterminantResult);
    }
}

TYPED_TEST(MatrixTests, Transpose) {
    PREPARE_TEST();
    // Transpose
    GLESC::Math::Matrix<Type, M, N> matrixTransposeResult = this->matrix.transpose();
    GLESC::Math::Matrix<Type, M, N> expectedTransposeResult;
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            expectedTransposeResult[j][i] = this->matrix[i][j];
    EXPECT_EQ_MAT(matrixTransposeResult, expectedTransposeResult);
}

TYPED_TEST(MatrixTests, Inverse) {
    PREPARE_TEST();
    // Inverse
    // Only square matrices can be inverted
    // And only dimensions 2, 3 and 4 are supported due to the implementation of the inverse
    if constexpr (N == M && N <= 4) {
        Mat matrixInverseResult = this->matrix.inverse();

        GLESC::Math::MatrixData<Type, N, M> expectedInverseResult{};
        GLESC::Math::MatrixAlgorithms::matrixInverse(this->matrix.data, expectedInverseResult);

        EXPECT_EQ_MAT(matrixInverseResult.data, expectedInverseResult);
    }
}


TYPED_TEST(MatrixTests, Rank) {
    //
    //PREPARE_TEST();
    //// Rank
    //if constexpr (N == M) {
    //    size_t matrixRankResult = this->matrix.rank();
    //    auto gaussianEliminationData = GLESC::Math::MatrixAlgorithms::gaussianElimination(this->matrix.data);
    //    EXPECT_EQ_CUSTOM(matrixRankResult, gaussianEliminationData.rank);
    //}
    //
}

#endif // MATH_ALGEBRA_UNIT_TESTING
