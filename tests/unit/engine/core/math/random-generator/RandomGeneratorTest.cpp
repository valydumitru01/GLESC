/**************************************************************************************************
 * @file   RandomGeneratorTest.cpp
 * @author Valentin Dumitru
 * @date   25/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include <gtest/gtest.h>
#include <unordered_set>
#include <cmath>
#include <engine/core/math/Math.h>

// Test fixture for typed tests
template<typename T>
class RandomNumberGeneratorTest : public ::testing::Test {
protected:
    T minValue = std::numeric_limits<T>::lowest();
    T maxValue = std::numeric_limits<T>::max();
    // A range for testing that excludes the extreme values to avoid overflows for floating-point types
    T testMin = std::is_floating_point<T>::value ? std::nextafter(minValue, T(0)) : minValue;
    T testMax = std::is_floating_point<T>::value ? std::nextafter(maxValue, T(0)) : maxValue;
};

// Declare the types to be used in the tests
using MyTypes = ::testing::Types<int, long, unsigned int, unsigned long, float, double>;
TYPED_TEST_SUITE(RandomNumberGeneratorTest, MyTypes);

TYPED_TEST(RandomNumberGeneratorTest, GeneratesNumberWithinRange) {
    auto randomNumber = GLESC::Math::generateRandomNumber<TypeParam>();
    EXPECT_GE(randomNumber, this->testMin);
    EXPECT_LE(randomNumber, this->testMax);
}

TYPED_TEST(RandomNumberGeneratorTest, GeneratesUniqueNumbers) {
    std::vector<TypeParam> uniqueNumbers;
    size_t numSamples = 20; // Number of samples to generate and test for uniqueness
    
    // Fill the set with random numbers
    for (size_t i = 0; i < numSamples; ++i) {
        auto randomNumber = GLESC::Math::generateRandomNumber<TypeParam>();
        uniqueNumbers.push_back(randomNumber);
    }
    
    std::cout << "Checking random number uniqueness for type " << typeid(TypeParam).name() << "\n";
    
    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < numSamples; ++j) {
            if (i != j) {
                bool isEq = GLESC::Math::eq(uniqueNumbers[i], uniqueNumbers[j]);
                std::cout << "[" << uniqueNumbers[i] << " !=? " << uniqueNumbers[j] << "]: " << (isEq ? "YES" : "NO");
                EXPECT_FALSE(isEq);
            }
        }
        std::cout << "\n";
    }
}