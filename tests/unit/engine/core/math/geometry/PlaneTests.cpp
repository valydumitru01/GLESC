/******************************************************************************
 * @file   PlaneTests.cpp
 * @author Valentin Dumitru
 * @date   2023-12-14
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
 
#include <gtest/gtest.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/geometry/Plane.h"

TEST(PlaneTests, Constructor) {
    using namespace GLESC::Math;
    
    // Test default constructor
    Plane defaultPlane;
    EXPECT_EQ(defaultPlane.getNormal(), Direction(0, 0, 0));
    EXPECT_DOUBLE_EQ(defaultPlane.getDistance(), 0);
    
    // Test constructor with normal and distance
    Plane planeNormalDistance(Direction(0, 1, 0), 5);
    EXPECT_EQ(planeNormalDistance.getNormal(), Direction(0, 1, 0));
    EXPECT_DOUBLE_EQ(planeNormalDistance.getDistance(), 5);
    
    // Test constructor with three points
    Plane plane3Points(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
    EXPECT_EQ(plane3Points.getNormal(), Direction(0, 0, 1)); // Normal pointing out of the XY plane
    
    // Test constructor with a point and a line
    Plane planePointLine(Point(0, 0, 0), Line(Point(1, 1, 1), Direction(1, 1, 1)));
    EXPECT_TRUE(planePointLine.getNormal().length() > 0); // Ensuring normal is not a zero vector
    
    // Test construct with invalid normal (expect death due to invalid input)
    EXPECT_DEATH({
        Plane planeInvalidNormal(Direction(0, 0, 0), 0);
                 }, "Invalid plane definition from normal and distance");
    
    // Test constructor with collinear points (expect death due to invalid input)
    EXPECT_DEATH({
        Plane planeCollinearPoints(Point(0, 0, 0), Point(1, 1, 1), Point(2, 2, 2));
                 }, "Invalid plane definition from 3 points");
    
    // Test constructor with a point lying on the line (expect death due to invalid input)
    EXPECT_DEATH({
        Plane planePointOnLine(Point(0, 0, 0), Line(Point(0, 0, 0), Direction(1, 1, 1)));
                 }, "Invalid plane definition from point and line");
}

TEST(PlaneTests, IntersectsPoint) {
    using namespace GLESC::Math;
    
    Plane plane(Direction(0, 0, 1), 0); // XY plane
    
    // Point on the plane
    EXPECT_TRUE(plane.intersects(Point(1, 1, 0)));
    
    // Point not on the plane
    EXPECT_FALSE(plane.intersects(Point(1, 1, 1)));
}

TEST(PlaneTests, IntersectsLine) {
    using namespace GLESC::Math;
    
    Plane plane(Direction(0, 0, 1), 0); // XY plane
    
    // Line parallel to the plane
    Line parallelLine(Point(0, 0, 1), Direction(1, 0, 0));
    EXPECT_FALSE(plane.intersects(parallelLine));
    
    // Line intersecting the plane
    Line intersectingLine(Point(0, 0, -1), Direction(0, 0, 1));
    EXPECT_TRUE(plane.intersects(intersectingLine));
}

TEST(PlaneTests, IntersectsPlane) {
    using namespace GLESC::Math;
    
    Plane plane1(Direction(0, 0, 1), 0); // XY plane
    Plane plane2(Direction(0, 1, 0), 0); // XZ plane
    
    // Intersecting planes
    EXPECT_TRUE(plane1.intersects(plane2));
    
    // Parallel planes
    Plane plane3(Direction(0, 0, 1), 1); // XY plane, shifted by 1 unit along Z
    EXPECT_FALSE(plane1.intersects(plane3));
}