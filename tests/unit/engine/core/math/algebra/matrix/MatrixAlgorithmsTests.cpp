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
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>

#include "unit/engine/core/math/algebra/matrix/MatrixTestsHelper.cpp"
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"
#ifdef MATH_ALGEBRA_UNIT_TESTING
template<class Type>
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

    TEST_SECTION("Testing matrix zero initialization") {
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
    TEST_SECTION("Testing matrix diagonal initialization") {
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
    TEST_SECTION("Testing matrix array initialization") {
        // ------------ Array initialization ------------
        GLESC::Math::MatrixData<Type, N, M> actualArrayMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(actualArrayMatrix, this->matrix);
        GLESC::Math::MatrixData<Type, N, M> expectedArrayMatrix = {};
        GLESC::Math::MatrixAlgorithms::setMatrix<Type, Type, N, M>(expectedArrayMatrix, this->matrix);
        EXPECT_EQ_MAT(actualArrayMatrix, expectedArrayMatrix);
    }
    TEST_SECTION("Testing matrix copy initialization") {
        // ------------ Copy initialization ------------
        GLESC::Math::MatrixData<Type, N, M> copy = {};
        GLESC::Math::MatrixAlgorithms::copyMatrix(copy, this->matrix);
        EXPECT_EQ_MAT(this->matrix, copy);
    }
    TEST_SECTION("Testing matrix move initialization") {
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


// ------------------------------ Exact solutions -----------------------------
TEST(MatrixAlgorithmsTests, LaplaceExpansionDeterminantAlgorithm) {
    GLESC::Math::MatrixData<double, 2, 2> matrix2x2;
    GLESC::Math::MatrixData<double, 3, 3> matrix3x3;
    GLESC::Math::MatrixData<double, 4, 4> matrix4x4;
    GLESC::Math::MatrixData<double, 5, 5> matrix5x5;
    double expectedDeterminant;
    double actualDeterminant;

    TEST_SECTION("Testing all elements are zero") {
        // Zero determinant - All elements of a row are zero
        matrix3x3 = {{{1, 2, 3}, {0, 0, 0}, {7, 8, 9}}};
        expectedDeterminant = 0;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Testing two rows are identical") {
        // 2. Zero determinant - Two rows are identical
        matrix3x3 = {{{1, 2, 3}, {1, 2, 3}, {7, 8, 9}}};
        expectedDeterminant = 0;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Testing two rows are proportional") {
        // Zero determinant - Two rows are proportional
        matrix3x3 = {{{1, 2, 3}, {2, 4, 6}, {7, 8, 9}}};
        expectedDeterminant = 0;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 2x2 matrix") {
        // Determinant of a 2x2 matrix
        matrix2x2 = {{{1, 2}, {3, 4}}};
        // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C2%7D%2C%7B3%2C4%7D%7D
        expectedDeterminant = -2;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix2x2);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 3x3 matrix") {
        // Determinant of a 3x3 matrix
        matrix3x3 = {{{-1, 2, 3}, {4, 5, -6}, {7, -8, 9}}};
        // https://www.wolframalpha.com/input?i2d=true&i=%7B%7B-1%2C2%2C3%7D%2C%7B4%2C5%2C-6%7D%2C%7B7%2C-8%2C9%7D%7D
        expectedDeterminant = -354;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix3x3);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 4x4 matrix") {
        // Determinant of a 4x4 matrix
        matrix4x4 = {{{1, 2, 3, -4}, {-5, 6, 7, 8}, {9, 15, -1, 2}, {3, -4, 5, 6}}};
        // https://www.wolframalpha.com/
        // input?i2d=true&i=%7B%7B1%2C2%2C3%2C-4%7D%2C%7B-5%2C6%2C7%2C8%7D%2C%7B9%2C15%2C-1%2C2%7D%2C%7B3%2C-4%2C5%2C6%7D%7D
        expectedDeterminant = -9588;
        actualDeterminant = GLESC::Math::MatrixAlgorithms::laplaceExpansionDeterminant(matrix4x4);
        EXPECT_EQ_CUSTOM(actualDeterminant, expectedDeterminant);
    }
    TEST_SECTION("Determinant of a 5x5 matrix") {
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
    TEST_SECTION("Testing Inverse of a 2x2 matrix") {
        // Test Inverse of a 2x2 matrix
        GLESC::Math::MatrixData<double, 2, 2> matrix2x2({{{1, 2}, {3, 4}}});
        GLESC::Math::MatrixData<double, 2, 2> expectedInverse2x2({{{-2, 1}, {1.5, -0.5}}});
        GLESC::Math::MatrixData<double, 2, 2> actualInverse2x2;
        GLESC::Math::MatrixAlgorithms::matrixInverse(matrix2x2, actualInverse2x2);
        EXPECT_EQ_MAT(actualInverse2x2, expectedInverse2x2);
    }
    TEST_SECTION("Testing Inverse of a 3x3 matrix") {
        // Test Inverse of a 3x3 matrix
        GLESC::Math::MatrixData<double, 3, 3> matrix3x3({{{1, 2, -3}, {-3, 4, -5}, {7, -8, 9}}});
        GLESC::Math::MatrixData<double, 3, 3>
                expectedInverse3x3({{{0.5, -0.75, -0.25}, {1, -3.75, -1.75}, {0.5, -2.75, -1.25}}});
        GLESC::Math::MatrixData<double, 3, 3> actualInverse3x3;
        GLESC::Math::MatrixAlgorithms::matrixInverse(matrix3x3, actualInverse3x3);
        EXPECT_EQ_MAT(actualInverse3x3, expectedInverse3x3);
    }
    TEST_SECTION("Testing Inverse of a 4x4 matrix") {
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
    TEST_SECTION("Testing Inverse of a 5x5 matrix") {
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

    for (const auto &vecDegrs : rotateVecDegrs) {
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
    TEST_SECTION("Test against glm") {
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

    TEST_SECTION("Testing errors in projection matrix") {
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

TEST(MatrixAlgorithmsTests, CalculateModelMatrixAlgorithm) {
    // Model matrix
    GLESC::Math::MatrixData<float, 4, 4> modelMatrix;
    GLESC::Math::VectorData<float, 3> scale({1, 2, 3});
    GLESC::Math::VectorData<float, 3> rotationDegrees({12, 32, 211});
    GLESC::Math::VectorData<float, 3> position({1, 2, 3});

    GLESC::Math::MatrixMixedAlgorithms::calculateModelMatrix(position, rotationDegrees, scale, modelMatrix);

    // Check against glm
    glm::mat4 glmMat = glm::mat4(1.0f);
    glmMat = glm::scale(glmMat, glm::vec3(scale[0], scale[1], scale[2]));
    glmMat = glm::rotate(glmMat, glm::radians(rotationDegrees[0]), glm::vec3(1, 0, 0));
    glmMat = glm::rotate(glmMat, glm::radians(rotationDegrees[1]), glm::vec3(0, 1, 0));
    glmMat = glm::rotate(glmMat, glm::radians(rotationDegrees[2]), glm::vec3(0, 0, 1));
    glmMat = glm::translate(glmMat, glm::vec3(position[0], position[1], position[2]));

    GLESC::Math::MatrixData<float, 4, 4> modelGlmMatrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            modelGlmMatrix[i][j] = glmMat[i][j];
        }
    }
    EXPECT_EQ_MAT(modelMatrix, modelGlmMatrix);
}

TEST(MatrixAlgorithmsTests, CalculateViewMatrixAlgorithm) {
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
