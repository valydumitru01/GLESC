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
#include "unit/engine/core/math/MathTestHelper.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/geometry/figures/plane/Plane.h"

TEST(PlaneTests, Constructor) {
    using namespace GLESC::Math;
    
    // Test default constructor
    Plane defaultPlane;
    EXPECT_EQ_VEC(defaultPlane.getNormal(), Direction(0, 0, 1));
    EXPECT_EQ_CUSTOM(defaultPlane.getDistance(), 0.0);
    
    // Test constructor with normal and distance
    Plane planeNormalDistance(Direction(0, 1, 0), 5);
    EXPECT_EQ_VEC(planeNormalDistance.getNormal(), Direction(0, 1, 0));
    EXPECT_EQ_CUSTOM(planeNormalDistance.getDistance(), 5.0);
    
    // Test constructor with three points
    Plane plane3Points(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
    // Normal pointing out of the XY plane
    EXPECT_EQ_VEC(plane3Points.getNormal(), Direction(0, 0, 1));
    
    // Test constructor with a point and a line
    Plane planePointLine(Point(0, 2, 0), Line(Point(1, 1, 1), Direction(1, 1, 1)));
    // Ensuring normal is not a zero vector
    EXPECT_EQ_CUSTOM(planePointLine.getNormal().length(), 1.0);
    
    // Test construct with invalid normal (expect death due to invalid input)
    EXPECT_DEATH({ Plane planeInvalidNormal(Direction(0, 0, 0), 0);
        }, "");
    
    // Test constructor with collinear points (expect death due to invalid input)
    EXPECT_DEATH({ Plane planeCollinearPoints(Point(0, 0, 0), Point(1, 1, 1), Point(2, 2, 2));
        },"");
    
    // Test constructor with a point lying on the line (expect death due to invalid input)
    EXPECT_DEATH({Plane planePointOnLine(Point(0, 0, 0), Line(Point(0, 0, 0), Direction(1, 1, 1)));
                 }, "");
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
    
    // Line parallel to the plane, above the plane
    Line parallelLineAbove(Point(0, 0, 1), Direction(1, 0, 0));
    EXPECT_FALSE(plane.intersects(parallelLineAbove));
    
    // Line parallel to the plane, below the plane
    Line parallelLineBelow(Point(0, 0, -1), Direction(1, 0, 0));
    EXPECT_FALSE(plane.intersects(parallelLineBelow));
    
    // Line intersecting the plane
    Line intersectingLine(Point(0, 0, -1), Direction(0, 0, 1));
    EXPECT_TRUE(plane.intersects(intersectingLine));
    
    // Line coincident with the plane
    Line coincidentLine(Point(0, 0, 0), Direction(1, 0, 0));
    EXPECT_TRUE(plane.intersects(coincidentLine));
    
    // Line intersecting the plane at a non-origin point
    Line nonOriginIntersectingLine(Point(1, 1, -1), Direction(0, 0, 1));
    EXPECT_TRUE(plane.intersects(nonOriginIntersectingLine));
    
    // Check intersection point
    Point intersectionPoint;
    EXPECT_TRUE(plane.intersects(intersectingLine, intersectionPoint));
    EXPECT_EQ_VEC(intersectionPoint, Point(0, 0, 0)); // Expect intersection at the origin
    
    // Check intersection point for non-origin intersecting line
    EXPECT_TRUE(plane.intersects(nonOriginIntersectingLine, intersectionPoint));
    EXPECT_EQ_VEC(intersectionPoint, Point(1, 1, 0)); // Expect intersection at (1, 1, 0)
    
    // Line that starts on the plane and goes away
    Line startsOnPlaneLine(Point(0, 0, 0), Direction(0, 1, 1));
    EXPECT_TRUE(plane.intersects(startsOnPlaneLine));
    
    // Line that starts on the plane and goes parallel
    Line startsOnPlaneGoesParallel(Point(0, 0, 0), Direction(1, 0, 0));
    EXPECT_TRUE(plane.intersects(startsOnPlaneGoesParallel));
    
    // Test with a skewed line that should intersect
    Line skewedIntersectingLine(Point(1, 2, 3), Direction(-4, -5, -6));
    EXPECT_TRUE(plane.intersects(skewedIntersectingLine));
    
    // Test with a skewed line that should intersect
    Line skewedNonIntersectingLine(Point(1, 2, 3), Direction(4, 5, 6));
    EXPECT_TRUE(plane.intersects(skewedNonIntersectingLine));
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