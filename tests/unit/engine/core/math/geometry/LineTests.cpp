/******************************************************************************
 * @file   LineTests.cpp
 * @author Valentin Dumitru
 * @date   2023-12-14
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <gtest/gtest.h>
#include <engine/core/math/geometry/GeometryTypes.h>
#include <engine/core/math/geometry/Line.h>

TEST(LineTests, Constructor) {
    using namespace GLESC::Math;
    
    // Test construction with point and direction
    Point p1(0, 0, 0);
    Direction d1(1, 1, 1);
    Line line1(p1, d1);
    EXPECT_EQ(line1.point, p1);
    EXPECT_EQ(line1.direction, d1);
    
    // Test construction with two points
    Point p2(0, 0, 0);
    Point p3(1, 1, 1);
    Line line2(p2, p3, Line::Construct::PointPoint);
    EXPECT_EQ(line2.point, p2);
    EXPECT_EQ(line2.direction, p3 - p2);
}

TEST(LineTests, IntersectsAnotherLine) {
    using namespace GLESC::Math;
    
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
    using namespace GLESC::Math;
    
    // Line and point intersect
    Line line(Point(0, 0, 0), Direction(1, 1, 1));
    Vec3D pointOnLine(1, 1, 1);
    EXPECT_TRUE(line.intersects(pointOnLine));
    
    // Line and point do not intersect
    Vec3D pointOffLine(1, 2, 3);
    EXPECT_FALSE(line.intersects(pointOffLine));
}

TEST(LineTests, DirectionNormalization) {
    using namespace GLESC::Math;
    
    Direction nonNormalizedDirection(1, 2, 3);
    Line line(Point(0, 0, 0), nonNormalizedDirection);
    EXPECT_DOUBLE_EQ(line.direction.length(), 1.0);  // Assuming a 'length()' method exists
}