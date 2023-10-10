/******************************************************************************
 * @file   VectorTest.cpp
 * @author Valentin Dumitru
 * @date   2023-10-06
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
 
#include <gtest/gtest.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/Vector.h"


using namespace GLESC::Math;

TEST(VectorTests, DefaultConstructor) {
    Vec<float, 3> vec;
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[1], 0);
    EXPECT_EQ(vec[2], 0);
}

TEST(VectorTests, ParametrizedConstructor) {
    Vec<float, 3> vec(1.0, 2.0, 3.0);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTests, CopyConstructor) {
    Vec<float, 3> vec1(1.0, 2.0, 3.0);
    Vec<float, 3> vec2(vec1);
    EXPECT_EQ(vec1, vec2);
}

TEST(VectorTests, MoveConstructor) {
    Vec<float, 3> vec1(1.0, 2.0, 3.0);
    Vec<float, 3> vec2(std::move(vec1));
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
}