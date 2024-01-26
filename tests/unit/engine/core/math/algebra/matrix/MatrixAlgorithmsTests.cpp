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
    
    void SetUp() override { initializeMatrixWithValues(this->matrix); }
    
    void TearDown() override {}
    
    typename GLESC::Math::MatrixData<typename Type::ValueType, Type::Rows, Type::Cols> matrix{};
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
    
    std::cout << "Testing matrix zero initialization\n";
    // ------------ Zero initialization ------------
    GLESC::Math::MatrixAlgorithms::setMatrxZero(this->matrix);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            EXPECT_EQ_CUSTOM(this->matrix[i][j], 0);
        }
    }
    
    std::cout << "Testing matrix diagonal initialization";
    // ------------ Diagonal initialization ------------
    auto value = Type(5);
    GLESC::Math::MatrixAlgorithms::setMatrixDiagonal(this->matrix, value);
    GLESC::Math::MatrixData<Type, N, M> matrixObjective = {};
    for (size_t i = 0; i < N; ++i) {
        matrixObjective[i][i] = value;
    }
    EXPECT_EQ_MAT(this->matrix, matrixObjective);
    
    
    std::cout << "Testing matrix array initialization";
    // ------------ Array initialization ------------
    GLESC::Math::MatrixData<Type, N, M> values = {};
    // Fill the values array with arbitrary values
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            values[i][j] = static_cast<Type>((i + 1) * (j + 1));
        }
    }
    GLESC::Math::MatrixAlgorithms::setMatrix(values, this->matrix);
    EXPECT_EQ_MAT(this->matrix, values);
    
    
    std::cout << "Testing matrix copy initialization";
    // ------------ Copy initialization ------------
    GLESC::Math::MatrixData<Type, N, M> copy = {};
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            copy[i][j] = this->matrix[i][j];
        }
    }
    GLESC::Math::MatrixAlgorithms::copyMatrix(copy, this->matrix);
    EXPECT_EQ_MAT(this->matrix, copy);
    
    std::cout << "Testing matrix move initialization";
    // ------------ Move initialization ------------
    GLESC::Math::MatrixData<Type, N, M> matrixToMove;
    GLESC::Math::MatrixAlgorithms::copyMatrix(copy, this->matrix);
    // Fill the matrixToMove with arbitrary values
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            matrixToMove[i][j] = static_cast<Type>((i + 1) * (j + 2));
        }
    }
    GLESC::Math::MatrixData<Type, N, M> matrixToMoveTo = {};
    GLESC::Math::MatrixAlgorithms::moveMatrix(matrixToMoveTo, std::move(matrixToMove));
    // Note: The matrixToMove is left in an unspecified state after the move.
    // So we can only check the matrixObjective for the expected values.
    EXPECT_EQ_MAT(this->matrix, matrixToMoveTo);
    
}



// ------------------------------ Exact solutions -----------------------------
TEST(MatrixAlgorithmsTests, LaplaceExpansionDeterminantAlgorithm) {
    GLESC::Math::MatrixData<double, 2, 2> matrix2x2;
    GLESC::Math::MatrixData<double, 3, 3> matrix3x3;
    GLESC::Math::MatrixData<double, 4, 4> matrix4x4;
    GLESC::Math::MatrixData<double, 5, 5> matrix5x5;
    
    
    // Zero determinant - All elements of a row are zero
    matrix3x3 = {{{1, 2, 3}, {0, 0, 0}, {7, 8, 9}}};
    double expectedDeterminant = 0;
    double actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    // 2. Zero determinant - Two rows are identical
    matrix3x3 = {{{1, 2, 3}, {1, 2, 3}, {7, 8, 9}}};
    expectedDeterminant = 0;
    actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    
    // Zero determinant - Two rows are proportional
    matrix3x3 = {{{1, 2, 3}, {2, 4, 6}, {7, 8, 9}}};
    expectedDeterminant = 0;
    actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    // Determinant of a 2x2 matrix
    matrix2x2 = {{{1, 2}, {3, 4}}};
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%7D%2C%7B3%2C4%7D%7D
    expectedDeterminant = -2;
    actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix2x2);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    // Determinant of a 3x3 matrix
    matrix3x3 = {{{-1, 2, 3}, {4, 5, -6}, {7, -8, 9}}};
    // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B-1%2C2%2C3%7D%2C%7B4%2C5%2C-6%7D%2C%7B7%2C-8%2C9%7D%7D
    expectedDeterminant = -354;
    actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    // Determinant of a 4x4 matrix
    matrix4x4 = {{{1, 2, 3, -4}, {-5, 6, 7, 8}, {9, 15, -1, 2}, {3, -4, 5, 6}}};
    // https://www.wolframalpha.com/
    // input?i2d=true&i=%7B%7B1%2C2%2C3%2C-4%7D%2C%7B-5%2C6%2C7%2C8%7D%2C%7B9%2C15%2C-1%2C2%7D%2C%7B3%2C-4%2C5%2C6%7D%7D
    expectedDeterminant = -9588;
    actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix4x4);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    // Determinant of a 5x5 matrix
    matrix5x5 = {{{-1, 2, 3, 4, 5}, {6, 7, 8, -9, 0}, {11, -21, 31, -41, 51}, {-61, 71, 81, 91, 10},
                  {11.1, 32.1, -53.1, 64.1, -75.1}}};
    // https://www.wolframalpha.com/
    // input?i2d=true&i=%7B%7B-1%2C2%2C3%2C4%2C5%7D%2C%7B6%2C7%2C8%2C-9%2C0%7D%2C%7B11%2C-21%2C31%2C-41%2C51%7D%2C%7B-
    // 61%2C71%2C81%2C91%2C10%7D%2C%7B11.1%2C32.1%2C-53.1%2C64.1%2C-75.1%7D%7D
    expectedDeterminant = -6.344832400000001 * pow(10, 6);
    actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix5x5);
    EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    
    
}

TYPED_TEST(MatrixAlgorithmsTests, DeterminantAlgorithm) {
    PREPARE_TEST();
    if constexpr (N == M) {
        GLESC::Math::MatrixData<Type, N, M> matrixToTest;
        generateMatrixWithRandomNumbers(matrixToTest);
        // Check if both determinant algorithms return the same result
        auto laplaceDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrixToTest);
        auto gaussianDeterminant = GLESC::Math::MatrixAlgorithms::gaussianElimination(matrixToTest).determinant;
        EXPECT_EQ_CUSTOM(laplaceDeterminant, gaussianDeterminant);
    }
}

TEST(MatrixAlgorithmsTests, InverseAlgorithm) {
    // Test Inverse of a 2x2 matrix
    GLESC::Math::MatrixData<double, 2, 2> matrix2x2({{{1, 2}, {3, 4}}});
    GLESC::Math::MatrixData<double, 2, 2> expectedInverse2x2({{{-2, 1}, {1.5, -0.5}}});
    GLESC::Math::MatrixData<double, 2, 2>
            actualInverse2x2 = GLESC::Math::MatrixAlgorithms::gaussianElimination(matrix2x2).inverse;
    EXPECT_EQ_MAT(actualInverse2x2, expectedInverse2x2);
    
    // Test Inverse of a 3x3 matrix
    GLESC::Math::MatrixData<double, 3, 3> matrix3x3({{{1, 2, -3}, {-3, 4, -5}, {7, -8, 9}}});
    GLESC::Math::MatrixData<double, 3, 3>
            expectedInverse3x3({{{0.5, -0.75, -0.25}, {1, -3.75, -1.75}, {0.5, -2.75, -1.25}}});
    GLESC::Math::MatrixData<double, 3, 3>
            actualInverse3x3 = GLESC::Math::MatrixAlgorithms::gaussianElimination(matrix3x3).inverse;
    EXPECT_EQ_MAT(actualInverse3x3, expectedInverse3x3);
    
    // Test Inverse of a 4x4 matrix
    GLESC::Math::MatrixData<double, 4, 4> matrix4x4({{{1, 2, 3, -4}, {-5, 6, 7, 8}, {9, 15, -1, 2}, {3, -4, 5, 6}}});
    GLESC::Math::MatrixData<double, 4, 4> expectedInverse4x4(
            {{{0.0223196, -0.0636212, 0.0450563, 0.0846892},
              {0.01335, 0.0367126, 0.0362954, -0.0521485},
              {0.148728, 0.0340008, -0.0175219, 0.0596579},
              {-0.126199, 0.0279516, 0.0162703, 0.0398415}}});
    GLESC::Math::MatrixData<double, 4, 4>
            actualInverse4x4 = GLESC::Math::MatrixAlgorithms::gaussianElimination(matrix4x4).inverse;
    EXPECT_EQ_MAT(actualInverse4x4, expectedInverse4x4);
    
    // Test Inverse of a 5x5 matrix
    GLESC::Math::MatrixData<double, 5, 5> matrix5x5({{{-1, 2, 3, 4, 5},
                                                      {6, 7, 8, -9, 0},
                                                      {11, -21, 31, -41, 51},
                                                      {-61, 71, 81, 91, 10},
                                                      {11.1, 32.1, -53.1, 64.1, -75.1}}});
    GLESC::Math::MatrixData<double, 5, 5> expectedInverse5x5(
            {{{-0.0935895, -0.0085282, 0.0719947, 0.00517271, 0.043349},
              {0.351945, 0.119422, -0.0858807, -0.0162524, -0.0370535},
              {-0.326954, -0.0438212, 0.0777137, 0.02122, 0.0338326},
              {-0.0792838, -0.0628653, 0.0502792, 0.00966992, 0.0301534},
              {0.300103, 0.0271107, -0.0381003, -0.0129324, -0.020931}}});
    GLESC::Math::MatrixData<double, 5, 5>
            actualInverse5x5 = GLESC::Math::MatrixAlgorithms::gaussianElimination(matrix5x5).inverse;
    EXPECT_EQ_MAT(actualInverse5x5, expectedInverse5x5);
}

TEST(MatrixAlgorithmsTests, TranslateAlgorithm) {
    
    // Translation of a 3x3 matrix
    GLESC::Math::MatrixData<double, 3, 3> transform2D({{{1, 2, -3},
                                                        {-3, 4, -5},
                                                        {7, -8, 9}}});
    GLESC::Math::VectorData<double, 2> translateVec2D({1, 2});
    GLESC::Math::MatrixData<double, 3, 3> actualTranslate2D;
    GLESC::Math::MatrixAlgorithms::translate(transform2D, translateVec2D, actualTranslate2D);
    GLESC::Math::MatrixData<double, 3, 3> expectedTranslate2D({{
                                                                       {1, 2, -2},
                                                                       {-3, 4, -5},
                                                                       {7, -8, 9}}
                                                              });
    EXPECT_EQ_MAT(actualTranslate2D, expectedTranslate2D);
    
    // Translation of a 4x4 matrix
    GLESC::Math::MatrixData<double, 4, 4> transform3D({{
                                                               {1, 2, -3, 4},
                                                               {-3, 4, -5, 6},
                                                               {7, -8, 9, 10},
                                                               {11, 12, 13, 14}}
                                                      });
    GLESC::Math::VectorData<double, 3> translateVec3D({1, 2, 3});
    GLESC::Math::MatrixData<double, 4, 4> actualTranslate3D;
    GLESC::Math::MatrixAlgorithms::translate(transform3D, translateVec3D, actualTranslate3D);
    GLESC::Math::MatrixData<double, 4, 4> expectedTranslate3D({{
                                                                       {1, 2, -3, 5},
                                                                       {-3, 4, -5, 8},
                                                                       {7, -8, 9, 13},
                                                                       {11, 12, 13, 14}
                                                               }});
    EXPECT_EQ_MAT(expectedTranslate3D, expectedTranslate3D);
}


TEST(MatrixAlgorithmsTests, ScaleAlgorithm) {
    // Translation of a 3x3 matrix
    GLESC::Math::MatrixData<double, 3, 3> scale2D({{{1, 2, 3},
                                                    {4, 5, 6},
                                                    {7, 8, 9}}});
    GLESC::Math::VectorData<double, 2> scaleVec2D({1, 2});
    // Must increase (add +) diagonal elements (expect the last one) by the scale vector
    GLESC::Math::MatrixData<double, 3, 3> expectedScale2D({{{2, 2, 3},
                                                            {4, 7, 6},
                                                            {7, 8, 9}}});
    GLESC::Math::MatrixAlgorithms::scale(scale2D, scaleVec2D, scale2D);
    EXPECT_EQ_MAT(scale2D, expectedScale2D);
    
    // Translation of a 4x4 matrix
    GLESC::Math::MatrixData<double, 4, 4> scale3D({{{1, 2, 3, 4},
                                                    {5, 6, 7, 8},
                                                    {9, 10, 11, 12},
                                                    {13, 14, 15, 16}}});
    GLESC::Math::VectorData<double, 3> scaleVec3D({1, 2, 3});
    GLESC::Math::MatrixData<double, 4, 4> expectedScale3D({{{2, 2, 3, 4},
                                                            {5, 8, 7, 8},
                                                            {9, 10, 14, 12},
                                                            {13, 14, 15, 16}}});
    GLESC::Math::MatrixAlgorithms::scale(scale3D, scaleVec3D, scale3D);
    EXPECT_EQ_MAT(scale3D, expectedScale3D);
}

TEST(MatrixAlgorithmsTests, RotateAlgorithm) {
    // Rotation of a 3x3 matrix
    GLESC::Math::MatrixData<double, 3, 3> rotate2D({{{1, 2, 3},
                                                     {4, 5, 6},
                                                     {7, 8, 9}}});
    double dgrs = GLESC::Math::PI / 4; // 45 degree rotation for instance
    GLESC::Math::MatrixMixedAlgorithms::rotate2D(rotate2D, dgrs, rotate2D);
    GLESC::Math::MatrixData<double, 3, 3> expectedRotate2D({{{-2.12132034, -2.12132034, -2.12132034},
                                                             {3.53553391, 4.94974747, 6.36396103},
                                                             {7, 8, 9}}});
    EXPECT_EQ_MAT(rotate2D, expectedRotate2D);
    
    
    // Rotation of a 4x4 matrix
    GLESC::Math::MatrixData<double, 4, 4> rotate3D({{{1, 2, 3, 4},
                                                     {5, 6, 7, 8},
                                                     {9, 10, 11, 12},
                                                     {13, 14, 15, 16}}});
    double dgrs3D = GLESC::Math::PI / 4; // 45 degree rotation for instance
    GLESC::Math::VectorData<double, 3> axis({0, 0, dgrs3D}); // Rotation about the z-axis
    GLESC::Math::MatrixMixedAlgorithms::rotate3D(rotate3D, axis, rotate3D);
    
    GLESC::Math::MatrixData<double, 4, 4> expectedRotate3D({{{-2.82842712, -2.82842712, -2.82842712, -2.82842712},
                                                             {4.24264069, 5.65685425, 7.07106781, 8.48528137},
                                                             {9, 10, 11, 12},
                                                             {13, 14, 15, 16}}});
    EXPECT_EQ_MAT(rotate3D, expectedRotate3D);
}

TEST(MatrixAlgorithmsTests, LookAtAlgorithm) {
    // LookAt for a 3x3 matrix (2D transformation)
    GLESC::Math::MatrixData<double, 3, 3> matrix2D({{{1, 0, 0},
                                                     {0, 1, 0},
                                                     {0, 0, 1}}});
    GLESC::Math::VectorData<double, 2> target2D({1, 1});
    GLESC::Math::MatrixMixedAlgorithms::lookAt2D(matrix2D, target2D, matrix2D);
    GLESC::Math::MatrixData<double, 3, 3> expectedLookAt2D({{{0.70710678, 0.70710678, 0.0},
                                                             {-0.70710678, 0.70710678, 0.0},
                                                             {0.0, 0.0, 1.0}}});
    
    EXPECT_EQ_MAT(matrix2D, expectedLookAt2D);
    
    // LookAt for a 4x4 matrix
    GLESC::Math::MatrixData<double, 4, 4> matrix3D({{{1, 0, 0, 0},
                                                     {0, 1, 0, 0},
                                                     {0, 0, 1, 0},
                                                     {0, 0, 0, 1}}});
    GLESC::Math::VectorData<double, 3> target3D({1, 3, -1});
    GLESC::Math::VectorData<double, 3> up({0, 1, 0});
    GLESC::Math::MatrixMixedAlgorithms::lookAt3D(matrix3D, target3D, up, matrix3D);
    
    GLESC::Math::MatrixData<double, 4, 4> expectedLookAt3D({{{0.70710678, -0.63960215, -0.30151134, 0.0},
                                                             {0.0, 0.42640143, -0.90453403, 0.0},
                                                             {0.70710678, 0.63960215, 0.30151134, 0.0},
                                                             {0.0, 0.0, 0.0, 1.0}}});
    
    EXPECT_EQ_MAT(matrix3D, expectedLookAt3D);
}

