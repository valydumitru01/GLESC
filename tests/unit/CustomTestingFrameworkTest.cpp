/**************************************************************************************************
 * @file   CustomTestingFrameworkTest.cpp
 * @author Valentin Dumitru
 * @date   25/01/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "unit/CustomTestingFramework.h"
#include <gtest/gtest.h>
#include <random>

template<typename T>
class CustomTestingFrameworkTest : public testing::Test {
protected:
    int iterations=100;
};

// Specify the types you want to run your tests on
using TypesToTest = testing::Types<float, double, int, long>;
TYPED_TEST_SUITE(CustomTestingFrameworkTest, TypesToTest);

// Define the type-parameterized tests
TYPED_TEST(CustomTestingFrameworkTest, ExpectEqualCustomWithRandomNumbers) {
    for (int i = 0; i < this->iterations; ++i) {
        auto a = GLESC::Math::generateRandomNumber<TypeParam>();
        TypeParam b = a;
        
        EXPECT_EQ_CUSTOM(a, b);
        
        // Now change "b" to be different from "a" to see if the test fails
        b = GLESC::Math::generateRandomNumber<TypeParam>();
        
        EXPECT_NE_CUSTOM(a, b);
    }
}
