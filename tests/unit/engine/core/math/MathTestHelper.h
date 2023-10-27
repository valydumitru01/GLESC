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
#include "engine/core/logger/Logger.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/Matrix.h"

#define EXPECT_EQ_F(a, b) \
    EXPECT_NEAR(a,b,GLESC::Math::FLOAT_COMPARISON_EPSILON \
    *std::max(static_cast<float>(std::abs(a)),static_cast<float>(std::abs(b))))
#define EXPECT_EQ_D(a, b) \
    ASSERT_NEAR(a,b,GLESC::Math::DOUBLE_COMPARISON_EPSILON*std::max(std::abs(a),std::abs(b)))


#define EXPECT_EQ_CUSTOM(a, b) \
    do {                       \
        if (std::is_same_v<decltype(a), float>) \
            EXPECT_NEAR((a), (b),               \
            GLESC::Math::FLOAT_COMPARISON_EPSILON \
            * std::max(static_cast<float>(std::fabs(a)), static_cast<float>(std::fabs(b)))); \
        else if (std::is_same_v<decltype(a), double>) \
            EXPECT_NEAR((a), (b),               \
            GLESC::Math::DOUBLE_COMPARISON_EPSILON \
            * std::max(static_cast<double>(std::fabs(a)), static_cast<double>(std::fabs(b)))); \
        else \
            EXPECT_EQ((a), (b)); \
    } while (false)

#define EXPECT_EQ_MAT(a, b) \
    do {                    \
        std::cout<<"Comparing matrices:\n"; \
        std::cout<<"Left matrix: \n"<<a.toString(); \
        std::cout<<"Right matrix: \n"<<b.toString(); \
        for (size_t i = 0; i < a.rows(); ++i) \
            for (size_t j = 0; j < a.cols(); ++j) \
                EXPECT_EQ_CUSTOM((a).get(i, j), (b).get(i, j)); \
        Logger::get().success("Matrices are equal\n"); \
    } while (false)

#define EXPECT_EQ_VEC(a, b) \
    do { \
        for (size_t i = 0; i < 2; ++i) \
            EXPECT_EQ_CUSTOM((a).get(i), (b).get(i)); \
    } while (false)