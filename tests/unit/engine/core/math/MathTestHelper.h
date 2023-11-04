/******************************************************************************
 * @file   MathTestHelper.h
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  Add description of this file if needed @todo 
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
#include "engine/core/math/Math.h"
#include "engine/core/math/Matrix.h"

#define EXPECT_EQ_F(a, b) \
    EXPECT_NEAR(a,b,GLESC::Math::FLOAT_COMPARISON_EPSILON \
    *std::max(static_cast<float>(std::abs(a)),static_cast<float>(std::abs(b))))
#define EXPECT_EQ_D(a, b) \
    ASSERT_NEAR(a,b,GLESC::Math::DOUBLE_COMPARISON_EPSILON*std::max(std::abs(a),std::abs(b)))

#define EXPECT_EQ_CUSTOM(a, b) \
    do { \
        using ValueType = std::decay_t<decltype(a)>; \
        if constexpr (std::is_floating_point_v<ValueType>) { \
            ValueType epsilon = GLESC::Math::ENGINE_EPSILON \
                * std::max(std::max(static_cast<ValueType>(std::fabs(a)),          \
                           static_cast<ValueType>(std::fabs(b))),static_cast<ValueType>(1)); \
            EXPECT_NEAR((a), (b), epsilon); \
        } else { \
            EXPECT_EQ((a), (b)); \
        } \
    } while (false)

/**
 * @brief Old version, TODO: need fixing
 */
/*
#define EXPECT_EQ_CUSTOM(a, b)                                 \
    do {                                                       \
        if constexpr (std::is_floating_point_v<decltype(a)>) {           \
            decltype(a) epsilon;                                   \
            if constexpr (std::is_same_v<decltype(a), float>) {    \
                epsilon = GLESC::Math::FLOAT_COMPARISON_EPSILON;   \
            }                                                      \
            else if constexpr (std::is_same_v<decltype(a), double>){ \
                epsilon = GLESC::Math::DOUBLE_COMPARISON_EPSILON;  \
            }                                                      \
            epsilon *= std::max(std::fabs(a), std::fabs(b));       \
            std::cout << "Epsilon: " << epsilon << "\n";           \
            EXPECT_NEAR((a), (b), epsilon);                    \
        } else {                                               \
            EXPECT_EQ((a), (b));                               \
        }                                                      \
    } while (false)
*/

#define EXPECT_EQ_MAT(a, b) \
    do {                    \
        std::cout<< "Comparing matrices:\n"; \
        std::cout<< "Left matrix: \n" << a.toString(); \
        std::cout<< "Right matrix: \n" << b.toString(); \
        for (size_t i = 0; i < a.rows(); ++i) \
            for (size_t j = 0; j < a.cols(); ++j) \
                EXPECT_EQ_CUSTOM((a).get(i, j), (b).get(i, j)); \
        std::cout<< "Matrices are equal\n"; \
    } while (false)

#define EXPECT_EQ_VEC(a, b) \
    do { \
        std::cout<< "Comparing vectors:\n"; \
        std::cout<< "Left vector: " << a.toString() <<"\n"; \
        std::cout<< "Right vector: " << b.toString() <<"\n";\
        for (size_t i = 0; i < a.size(); ++i) \
            EXPECT_EQ_CUSTOM((a).get(i), (b).get(i)); \
    } while (false)


