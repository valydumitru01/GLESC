/******************************************************************************
 * @file   LineTests.cpp
 * @author Valentin Dumitru
 * @date   2023-12-14
 * @brief  * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "TestsConfig.h"
#if MATH_GEOMETRY_UNIT_TESTING
#include <gtest/gtest.h>
#include "engine/core/exceptions/core/AssertFailedException.h"
#include <engine/core/math/geometry/GeometryTypes.h>
#include "engine/core/math/geometry/figures/line/Line.h"
#include "unit/engine/core/math/MathCustomTestingFramework.h"
using namespace GLESC::Math;
TEST(LineTests, Constructor) {
    // Test construction with point and direction
    Point p1(0, 0, 0);
    Direction d1(0, 0, 1);
    Line line1(p1, d1, Line::Construct::PointDirection);
    EXPECT_EQ_VEC(line1.getPoint(), p1);
    EXPECT_EQ_VEC(line1.getDirection(), d1);
    
    // Test construction with two points
    Point p2(0, 0, 0);
    Point p3(1, 1, 1);
    Line line2(p2, p3, Line::Construct::PointPoint);
    EXPECT_EQ_VEC(line2.getPoint(), p2);
    EXPECT_EQ_VEC(line2.getDirection(), (p3 - p2).normalize());
    
    // Expect death when constructing with a zero direction
    Direction zeroDirection(0, 0, 0);
    EXPECT_THROW(Line line3(Point(0, 0, 0), zeroDirection), AssertFailedException);
}

TEST(LineTests, IntersectsAnotherLine) {
    // Parallel lines should not intersect
    Line line1(Point(0, 0, 0), Direction(1, 0, 0));
    Line line2(Point(0, 1, 0), Direction(1, 0, 0));
    EXPECT_FALSE(line1.intersects(line2));
    
    // Intersecting lines
    Line line3(Point(0, 0, 0), Direction(1, 0, 0));
    Line line4(Point(0, 0, 0), Direction(0, 1, 0));
    EXPECT_TRUE(line3.intersects(line4));
}

TEST(LineTests, IntersectsPoint) {
    // Line and point intersect
    Line line(Point(0, 0, 0), Direction(1, 1, 1));
    Point pointOnLine(1, 1, 1);
    EXPECT_TRUE(line.intersects(pointOnLine));
    
    // Line and point do not intersect
    Point pointOffLine(1, 2, 3);
    EXPECT_FALSE(line.intersects(pointOffLine));
}

TEST(LineTests, DirectionNormalization) {
    // When constructing with a non-normalized direction, it should be normalized
    Direction nonNormalizedDirection(1, 2, 3);
    Line line(Point(0, 0, 0), nonNormalizedDirection);
    EXPECT_EQ_CUSTOM(line.getDirection().length(), 1.0);
    
    // When constructing with a normalized direction, it should stay normalized
    Direction normalizedDirection(1, 0, 0);
    Line line2(Point(0, 0, 0), normalizedDirection);
    EXPECT_EQ_CUSTOM(line2.getDirection().length(), 1.0);
    
    // When changing the direction, it should be normalized too
    line2.setDirection(nonNormalizedDirection);
    EXPECT_EQ_CUSTOM(line2.getDirection().length(), 1.0);
    
}
#endif