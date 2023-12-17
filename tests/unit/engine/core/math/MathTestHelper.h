/******************************************************************************
 * @file   MathTestHelper.h
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <cmath>
#include "engine/core/debugger/Stringer.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/Matrix.h"


template <typename Type1, typename Type2>
void expectEqFlexible(const Type1& a, const Type2& b) {
    if constexpr (std::is_floating_point_v<Type1> || std::is_floating_point_v<Type2>) {
        // Calculate epsilon only for floating-point types
        constexpr auto epsilon1 = std::is_floating_point_v<Type1> ? GLESC::Math::epsilon<Type1>() : 0;
        constexpr auto epsilon2 = std::is_floating_point_v<Type2> ? GLESC::Math::epsilon<Type2>() : 0;
        const auto maxEpsilon = std::max(epsilon1, epsilon2);
        
        EXPECT_NEAR(a, b, maxEpsilon);
    } else {
        // For non-floating point types, use EXPECT_EQ
        EXPECT_EQ(a, b);
    }
}

template <typename T, size_t N, size_t M>
void expectEqMatrices(const GLESC::Math::Matrix<T, N, M>& a,
                      const GLESC::Math::Matrix<T, N, M>& b) {
    std::cout<< "Comparing matrices:\n";
    std::cout<< "Left matrix: \n" << a.toString();
    std::cout<< "Right matrix: \n" << b.toString();
    for (size_t i = 0; i < a.rows(); ++i)
        for (size_t j = 0; j < a.cols(); ++j)
            expectEqFlexible((a).get(i, j), (b).get(i, j));
    std::cout<< "Matrices are equal\n"; \
}

template <typename T, size_t N>
void expectEqVectors(const GLESC::Math::Vector<T, N>& lVector,
                     const GLESC::Math::Vector<T, N>& rVector) {
    std::cout<< "Comparing vectors:\n";
    std::cout << "Left vector: " << lVector.toString() << "\n";
    std::cout << "Right vector: " << rVector.toString() << "\n";
    for (size_t i = 0; i < lVector.size(); ++i)
        expectEqFlexible(lVector.get(i), rVector.get(i));
    std::cout<< "Vectors are equal\n"; \
}

template <typename T>
void expectEqVectors(const std::vector<T>& a,
                     const std::vector<T>& b) {
    std::cout<< "Comparing vectors:\n";
    std::cout<< "Left vector: " << GLESC::toString(a) <<"\n";
    std::cout<< "Right vector: " << GLESC::toString(b) <<"\n";
    for (size_t i = 0; i < a.size(); ++i)
        expectEqFlexible(a[i], b[i]);
    std::cout<< "Vectors are equal\n"; \
}



#define EXPECT_EQ_CUSTOM(a, b) \
    expectEqFlexible(a, b)

#define EXPECT_EQ_MAT(a, b) \
    expectEqMatrices(a, b)

#define EXPECT_EQ_VEC(a, b) \
    expectEqVectors(a, b)

