/******************************************************************************
 * @file   GLESC::Math::MatrixTestTyped.cpp
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "unit/engine/core/math/algebra/matrix/MatrixTestsHelper.cpp"

template<class Type>
class MatrixTests : public testing::Test {
protected:
    MatrixTests() = default;
    
    void SetUp() override {
        initializeMatrixWithValues(this->matrix);
        initializeMatrixWithDifferentValues(this->matrix2);
    }
    
    void TearDown() override {}
    
    GLESC::Math::Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix;
    // For combined operations
    GLESC::Math::Matrix<typename Type::ValueType, Type::Rows, Type::Cols> matrix2;
};


TYPED_TEST_SUITE(MatrixTests, MyTypes);


TYPED_TEST(MatrixTests, Constructors) {
    PREPARE_TEST();
    std::cout << "Testing matrix constructors\n";
    
    std::cout << "Testing default constructor\n";
    // Default constructor
    Mat matrixDefault;
    Mat expectedDefault;
    GLESC::Math::MatrixAlgorithms::setMatrxZero(expectedDefault.data);
    EXPECT_EQ_MAT(matrixDefault, expectedDefault);
    
    std::cout << "Testing diagonal constructor\n";
    // Diagonal constructor
    Type diagonalValue = 1;
    Mat matrixDiagonal(diagonalValue);
    Mat expectedDiagonal;
    GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(expectedDiagonal.data, diagonalValue);
    EXPECT_EQ_MAT(matrixDiagonal, expectedDiagonal);
    
    std::cout << "Testing array constructor\n";
    // Array constructor
    Type arrayValues[N][M];
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            arrayValues[i][j] = generateNextValue<Type>(i, j);
    Mat matrixArray(arrayValues);
    Mat expectedArray;
    GLESC::Math::MatrixAlgorithms::setMatrix(expectedArray.data, arrayValues);
    EXPECT_EQ_MAT(matrixArray, expectedArray);
    
    
    std::cout << "Testing copy constructor\n";
    // Copy constructor
    Mat matrixCopy(this->matrix);
    Mat matrixCopyReference;
    EXPECT_EQ_MAT(matrixCopy, this->matrix);
    
    std::cout << "Testing move constructor\n";
    // Move constructor
    Mat matrixMove(std::move(this->matrix));
    EXPECT_EQ_MAT(matrixMove, this->matrix);
}

TYPED_TEST(MatrixTests, Accessors) {
    PREPARE_TEST();
    std::cout << "Testing matrix accessors\n";
    
    std::cout << "Testing rows\n";
    // Get rows
    EXPECT_EQ_CUSTOM(this->matrix.rows(), N);
    
    std::cout << "Testing cols\n";
    // Get cols
    EXPECT_EQ_CUSTOM(this->matrix.cols(), M);
    
    std::cout << "Testing set over []\n";
    // Set value
    Mat matrixSetCols;
    Type setValue = Type(9999);
    matrixSetCols[5][5] = setValue;
    EXPECT_EQ_CUSTOM(matrixSetCols[5][5], setValue);
    
    std::cout << "Testing get over []\n";
    // Operator [] ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix[i][j], generateNextValue<Type>(i, j));
    
    std::cout << "Testing const getters\n";
    // Const Getters ----------------------------------
    for (size_t i = 0; i < this->matrix.rows(); ++i)
        for (size_t j = 0; j < this->matrix.cols(); ++j)
            EXPECT_EQ_CUSTOM(this->matrix.get(i, j), generateNextValue<Type>(i, j));
    
    // Getters must return a const reference
    S_ASSERT_TRUE((std::is_same_v<decltype(this->matrix.get(0, 0)), const Type &>),
                  "Getters (index1, index2) must return a const reference to the matrix element");
    
    S_ASSERT_TRUE((std::is_same_v<decltype(this->matrix.get(0)), const GLESC::Math::MatrixRow<Type, M> &>),
                  "Getter (index) must return a const reference to the matrix row");
    
    S_ASSERT_TRUE((std::is_same_v<decltype(this->matrix[0][0]), Type &>),
                  "Operator [] must return a reference");
    
    
}

TYPED_TEST(MatrixTests, ComparisonOperators) {
    PREPARE_TEST();
    std::cout << "Testing matrix comparison operators\n";
    
    std::cout << "Testing equality operator\n";
    // Equality operator
    Mat matrixEquals;
    initializeMatrixWithValues(matrixEquals);
    EXPECT_EQ(this->matrix, matrixEquals);
    
    std::cout << "Testing inequality operator\n";
    // Inequality operator
    Mat matrixNotEquals;
    initializeMatrixWithValues(matrixNotEquals);
    matrixNotEquals[0][0] += Type(1);
    EXPECT_NE(this->matrix, matrixNotEquals);
    
}

TYPED_TEST(MatrixTests, Assignments) {
    PREPARE_TEST();
    std::cout << "Testing matrix assignments\n";
    
    std::cout << "Testing copy assignment\n";
    // Copy assignment
    Mat matrixCopyAssign;
    matrixCopyAssign = this->matrix;
    EXPECT_EQ_MAT(matrixCopyAssign, this->matrix);
    
    std::cout << "Testing move assignment\n";
    // Move assignment
    Mat matrixMoveAssign;
    matrixMoveAssign = std::move(this->matrix);
    EXPECT_EQ_MAT(matrixMoveAssign, this->matrix);
    
    std::cout << "Testing += operator with matrix\n";
    // Operator += with matrix
    Mat matrixPlusEquals;
    initializeMatrixWithValues(matrixPlusEquals);
    matrixPlusEquals += this->matrix;
    EXPECT_EQ_MAT(matrixPlusEquals, (this->matrix + this->matrix));
    
    std::cout << "Testing += operator with scalar\n";
    // Operator += with scalar
    Mat matrixPlusScalarEquals;
    initializeMatrixWithValues(matrixPlusScalarEquals);
    Type scalar = Type(2);
    matrixPlusScalarEquals += scalar;
    EXPECT_EQ_MAT(matrixPlusScalarEquals, (this->matrix + scalar));
    
    std::cout << "Testing -= operator with matrix\n";
    // Operator -= with matrix
    Mat matrixMinusEquals;
    initializeMatrixWithValues(matrixMinusEquals);
    matrixMinusEquals -= this->matrix;
    EXPECT_EQ_MAT(matrixMinusEquals, (this->matrix - this->matrix));
    
    std::cout << "Testing -= operator with scalar\n";
    // Operator -= with scalar
    Mat matrixMinusScalarEquals;
    initializeMatrixWithValues(matrixMinusScalarEquals);
    Type scalarMinus = Type(2);
    matrixMinusScalarEquals -= scalarMinus;
    EXPECT_EQ_MAT(matrixMinusScalarEquals, (this->matrix - scalarMinus));
    
    std::cout << "Testing *= operator with matrix\n";
    // Operator *= with matrix
    if constexpr (N == M) { // Only square matrices can be multiplied in place
        GLESC::Math::Matrix<Type, M, N> matrixMultEquals;
        initializeMatrixWithValues(matrixMultEquals);
        matrixMultEquals *= this->matrix;
        EXPECT_EQ_MAT(matrixMultEquals, (this->matrix * this->matrix));
    }
    
    std::cout << "Testing *= operator with scalar\n";
    // Operator *= with scalar
    Mat matrixMultScalarEquals;
    initializeMatrixWithValues(matrixMultScalarEquals);
    Type scalarMult = Type(2);
    matrixMultScalarEquals *= scalarMult;
    EXPECT_EQ_MAT(matrixMultScalarEquals, (this->matrix * scalarMult));
    
    std::cout << "Testing /= operator with scalar\n";
    // Operator /= with scalar
    Mat matrixDivScalarEquals;
    initializeMatrixWithValues(matrixDivScalarEquals);
    Type scalarDiv = Type(2);
    matrixDivScalarEquals /= scalarDiv;
    EXPECT_EQ_MAT(matrixDivScalarEquals, (this->matrix / scalarDiv));
    
    std::cout << "Testing /= operator with matrix\n";
    // Operator /= with matrix
    if constexpr (N == M) { // Only square matrices can be divided in place
        Mat matrixDivEquals;
        initializeMatrixWithValues(matrixDivEquals);
        std::cout << "Dividing matrices:\n";
        matrixDivEquals /= this->matrix;
        Mat expectedDivEquals;
        initializeMatrixWithValues(expectedDivEquals);
        expectedDivEquals = expectedDivEquals * this->matrix.inverse();
        EXPECT_EQ_MAT(matrixDivEquals, expectedDivEquals);
        // Dividing by zero
        Mat matrixDivZero;
        initializeMatrixWithValues(matrixDivZero);
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
        GLESC::Math::MatrixAlgorithms::matrixHadamardMul(this->matrix.data, this->matrix.data,
                                                         expectedMultResult.data);
        EXPECT_EQ_MAT(matrixMultResult, expectedMultResult);
    }
    
    // Multiplication operator with scalar
    Type scalar = Type(2);
    Mat matrixMultScalarResult = this->matrix * scalar;
    Mat expectedMultScalar = this->matrix;
    GLESC::Math::MatrixAlgorithms::matrixScalarMul(this->matrix.data, scalar, expectedMultScalar.data);
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
    if constexpr (N == M) {
        Mat matrixInverseResult = this->matrix.inverse();
        GLESC::Math::MatrixData<Type, N, M> expectedInverseResult =
                GLESC::Math::MatrixAlgorithms::gaussianElimination(this->matrix.data).inverse;
        EXPECT_EQ_MAT(matrixInverseResult.data, expectedInverseResult);
    }
}

TYPED_TEST(MatrixTests, MatrixTranslate) {
    PREPARE_TEST();
    // ---------------------------------- Matrix transformations -----------------------------------
    // All transformations need to be tested only for square matrices
    if constexpr (N == M) {
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

TYPED_TEST(MatrixTests, MatrixScale) {
    PREPARE_TEST();
    if constexpr ((N == 2 || N == 3) && N == M) {
        // Scale
        auto scaleVec = VectorT<Type, N - 1>(2);
        Mat matrixTransform = this->matrix;
        Mat matrixScaleResult = this->matrix.scale(scaleVec);
        Mat expectedScaleResult;
        GLESC::Math::MatrixAlgorithms::scale(matrixTransform.data, scaleVec.data, expectedScaleResult.data);
        
        
        EXPECT_EQ_MAT(matrixScaleResult, expectedScaleResult);
    }
}

TYPED_TEST(MatrixTests, MatrixRotate) {
    PREPARE_TEST();
    Type angle = GLESC::Math::PI / 4; // 45 degrees rotation for instance
    Mat matrixRotateResult;
    Mat expectedRotateResult;
    // Rotate
    // Only defined (or necessary) for 3x3 and 4x4 matrices
    if constexpr (N == 3 && M == 3) {
        matrixRotateResult = this->matrix.rotate(angle);
        GLESC::Math::MatrixMixedAlgorithms::rotate2D(this->matrix.data, angle, expectedRotateResult.data);
        
    } else if constexpr (N == 4 && M == 4) {
        GLESC::Math::Vector<Type, 3> rotateVector(Type(0), Type(0), Type(angle)); // Rotation about the z-axis
        matrixRotateResult = this->matrix.rotate(rotateVector);
        
        GLESC::Math::MatrixMixedAlgorithms::rotate3D(this->matrix.data, rotateVector.data, expectedRotateResult.data);
        
    }
    EXPECT_EQ_MAT(matrixRotateResult, expectedRotateResult);
}
/*
TYPED_TEST(MatrixTests, Functions){
    PREPARE_TEST();
    // Determinant
    if constexpr (N==M){
        Type matrixDeterminantResult = this->matrix.determinant();
        Type expectedDeterminantResult =
                GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(this->matrix);
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
        Mat expectedInverseResult = GLESC::Math::MatrixAlgorithms::gaussianInverse(this->matrix);
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
            expectedLookAtResult = GLESC::Math::MatrixAlgorithms::lookAt2D(this->matrix, target);
            
            EXPECT_EQ_MAT(matrixLookAtResult, expectedLookAtResult);
        
        }
        else if constexpr (N == 4) {
            Vector<Type, 3> target(-3, 12, 1);
            Vector<Type, 3> up(0, 1, 0);
            Mat matrixLookAtResult = this->matrix.lookAt(target, up);
            Mat expectedLookAtResult;
            expectedLookAtResult = GLESC::Math::MatrixAlgorithms::lookAt3D(this->matrix, target, up);
            
            EXPECT_EQ_MAT(matrixLookAtResult, expectedLookAtResult);
        }

    }
    
}

*/


TYPED_TEST(MatrixTests, Rank) {
    PREPARE_TEST();
    // Rank
    if constexpr (N == M) {
        size_t matrixRankResult = this->matrix.rank();
        auto gaussianEliminationData = GLESC::Math::MatrixAlgorithms::gaussianElimination(this->matrix.data);
        EXPECT_EQ_CUSTOM(matrixRankResult, gaussianEliminationData.rank);
    }
}

