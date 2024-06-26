/**************************************************************************************************
 * @file   CustomTestingFramework.h
 * @author Valentin Dumitru
 * @date   25/01/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once


#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <type_traits>
#include "engine/core/debugger/Stringer.h"
#include "engine/core/math/Math.h"


template <typename Type1, typename Type2>
void expectEqCustom(const Type1& a, const Type2& b) {
    std::cout << "Comparing values: " << GLESC::Stringer::toString(a) << " and " << GLESC::Stringer::toString(b);
    if constexpr (std::is_floating_point_v<Type1> || std::is_floating_point_v<Type2>) {
        // * 1000 to account for multiple operations
        auto epsilon = GLESC::Math::max(GLESC::Math::epsilon(a), GLESC::Math::epsilon(b)) * 10000;
        std::cout << " with epsilon: " << GLESC::Stringer::toString(epsilon) << "\n";
        EXPECT_NEAR(a, b, epsilon);
    }
    else{
        EXPECT_EQ(a, b);
        std::cout << "\n";
    }
}

template <typename Type1, typename Type2>
void expectEqCustomEpsilon(const Type1& a, const Type2& b, const Type1& epsilon) {
    std::cout << "Comparing values: " << GLESC::Stringer::toString(a) << " and " << GLESC::Stringer::toString(b);
    if constexpr (std::is_floating_point_v<Type1> || std::is_floating_point_v<Type2>) {
        std::cout << " with epsilon: " << GLESC::Stringer::toString(epsilon) << "\n";
        EXPECT_NEAR(a, b, epsilon);
    }
    else{
        EXPECT_EQ(a, b);
        std::cout << "\n";
    }
}

template <typename Type1, typename Type2>
void expectNeCustom(const Type1& a, const Type2& b) {
    EXPECT_FALSE(GLESC::Math::eq(a, b));
}

#define EXPECT_NE_CUSTOM(a, b) \
    expectNeCustom(a, b)

// Macro for flexible equality check
#define EXPECT_EQ_CUSTOM(a, b) \
    expectEqCustom(a, b)


#define TEST_SECTION(title) \
    std::cout << "______________________________________________________________________________________________\n"; \
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << title << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"; \
    std::cout << "______________________________________________________________________________________________\n";