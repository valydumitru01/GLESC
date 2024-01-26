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
    T minValue = T(1);
    T maxValue = T(100);
};

// Declare the types to be used in the tests
using MyTypes = ::testing::Types<int, long, unsigned int, unsigned long, float, double>;
TYPED_TEST_SUITE(RandomNumberGeneratorTest, MyTypes);

TYPED_TEST(RandomNumberGeneratorTest, GeneratesNumberWithinRange) {
    auto randomNumber = GLESC::Math::generateRandomNumber<TypeParam>(this->minValue, this->maxValue);
    
    EXPECT_GE(randomNumber, this->minValue)
                        << "Random number " << randomNumber << " is not within range [" << this->minValue << ", "
                        << this->maxValue << "]\n";
    
    EXPECT_LE(randomNumber, this->maxValue)
                        << "Random number " << randomNumber << " is not within range [" << this->minValue << ", "
                        << this->maxValue << "]\n";
}

TYPED_TEST(RandomNumberGeneratorTest, GeneratesUniqueNumbers) {
    std::vector<TypeParam> uniqueNumbers;
    size_t numSamples = 5; // Number of samples to generate and test for uniqueness
    
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
                std::cout << uniqueNumbers[i] << " !=? " << uniqueNumbers[j] << ": "
                          << (isEq ? "False" : "True \n");
                EXPECT_FALSE(isEq);
            }
            
        }
        
        EXPECT_FALSE(std::isinf(uniqueNumbers[i]) || std::isnan(uniqueNumbers[i])) << "Number is not finite";
        std::cout << "\n";
    }
}

TYPED_TEST(RandomNumberGeneratorTest, GeneratesDecimalsForFloatingPointTypes) {
    if constexpr (std::is_floating_point_v<TypeParam>) {
        
        for (int i = 0; i < 100; ++i) {
            // Max range test
            auto randomNumber = GLESC::Math::generateRandomNumber<TypeParam>();
            auto decimalPart = randomNumber - std::floor(randomNumber);
            auto numberHasDecimals = decimalPart > std::numeric_limits<TypeParam>::epsilon();
            EXPECT_FALSE(numberHasDecimals) << "Generator did produce numbers with fractional parts for max range "
                                               "(and shouldn't)\n";
            
            std::cout << "Number with widest range:" << randomNumber << " has these decimals: " << decimalPart << "\n";
            // Define range test
            randomNumber = GLESC::Math::generateRandomNumber<TypeParam>(this->minValue, this->maxValue);
            decimalPart = randomNumber - std::floor(randomNumber);
            numberHasDecimals = decimalPart > std::numeric_limits<TypeParam>::epsilon();
            std::cout << "Number with defined range:" << randomNumber << " has these decimals: " << decimalPart << "\n";
            EXPECT_TRUE(numberHasDecimals)
                                << "Generator did not produce numbers with fractional parts for defined range\n";
            
        }
        
    }
}