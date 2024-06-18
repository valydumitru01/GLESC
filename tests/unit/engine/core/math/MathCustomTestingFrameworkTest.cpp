/**************************************************************************************************
 * @file   MathCustomTestingFrameworkTest.cpp
 * @author Valentin Dumitru
 * @date   25/01/2024
 * @brief  Test cases to ensure the proper functionality of the custom testing framework
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include <gtest/gtest.h>
#include <random>
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"


template<typename T>
class MathCustomTestingFrameworkTest : public ::testing::Test {
};

// Specify the types you want to run your tests on
using TypesToTest = ::testing::Types<float, double, int, long>;

TYPED_TEST_SUITE(MathCustomTestingFrameworkTest, TypesToTest);

// Define the type-parameterized tests
TYPED_TEST(MathCustomTestingFrameworkTest, ExpectEqMatWithRandomNumbers) {
    GLESC::Math::Matrix<TypeParam, 2, 2> a;
    generateMatrixWithRandomNumbers(a);
    GLESC::Math::Matrix<TypeParam, 2, 2> b(a);
    std::cout << "a: \n" << GLESC::Stringer::toString(a) << "\n";
    EXPECT_EQ_MAT(a, b);

    // Now change "b" to be different from "a" to see if the test fails
    generateMatrixWithRandomNumbers(b);

    EXPECT_NE_MAT(a, b);
}