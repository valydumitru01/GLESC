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
#include "engine/core/math/algebra/matrix/Matrix.h"


// Macro for flexible equality check
#define EXPECT_EQ_CUSTOM(a, b) \
    do { \
        if constexpr (std::is_floating_point_v<decltype(a)> || std::is_floating_point_v<decltype(b)>) { \
            constexpr auto epsilon1 = std::is_floating_point_v<decltype(a)> ? \
                                            GLESC::Math::epsilon<decltype(a)>() : 0.0; \
            constexpr auto epsilon2 = std::is_floating_point_v<decltype(b)> ? \
                                            GLESC::Math::epsilon<decltype(b)>() : 0.0; \
            const auto maxEpsilon = std::max(static_cast<double>(epsilon1), static_cast<double>(epsilon2)); \
            EXPECT_NEAR(a, b, maxEpsilon); \
        } else { \
            EXPECT_EQ(a, b); \
        } \
    } while (false)

// Macro for matrix equality check
#define EXPECT_EQ_MAT(a, b) \
    do { \
        std::cout << "Comparing matrices:\n"; \
        std::cout << "Left matrix: \n" << (a).toString(); \
        std::cout << "Right matrix: \n" << (b).toString(); \
        for (size_t i = 0; i < (a).rows(); ++i) \
            for (size_t j = 0; j < (a).cols(); ++j) \
                EXPECT_EQ_CUSTOM((a).get(i, j), (b).get(i, j)); \
        std::cout << "Matrices are equal\n"; \
    } while (false)

// Macro for vector equality check
#define EXPECT_EQ_VEC(a, b) \
    do { \
        std::cout << "Comparing vectors:\n"; \
        std::cout << "Left vector: " << (a).toString() << "\n"; \
        std::cout << "Right vector: " << (b).toString() << "\n"; \
        std::cout << "------------------ Vector Values comparison: -------------------\n"; \
        for (size_t i = 0; i < (a).size(); ++i) \
            EXPECT_EQ_CUSTOM((a).get(i), (b).get(i)); \
        std::cout << "----------------------------------------------------------------\n"; \
        std::cout << "Vectors are equal\n"; \
    } while (false)


