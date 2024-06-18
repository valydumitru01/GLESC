/******************************************************************************
 * @file   PlaneTests.cpp
 * @author Valentin Dumitru
 * @date   2023-12-14
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "TestsConfig.cpp"
#if MATH_GEOMETRY_UNIT_TESTING
#include <gtest/gtest.h>
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"
#include "engine/core/math/Math.h"
#include "engine/core/math/geometry/figures/plane/Plane.h"


// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- Default constructor ---------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

TEST(PlaneTests, DefaultConstructor) {
    using namespace GLESC::Math;
    // Test default constructor
    Plane defaultPlane;
    EXPECT_EQ_VEC(defaultPlane.getNormal(), Direction(0, 0, 1));
    EXPECT_EQ_CUSTOM(defaultPlane.getDistance(), 0.0);
}

TEST(PlaneTests, DefaultConstructor_ZeroLengthNormalException) {
    using namespace GLESC::Math;
    // Test zero-length normal vector throws exception
    EXPECT_THROW({ Plane zeroNormalPlane(Direction(0, 0, 0), 1); }, AssertFailedException);
}
// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- 3 Points constructor --------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
TEST(PlaneTests, ThreePointsConstructor) {
    using namespace GLESC::Math;
    // Test correct distance calculation from points
    Plane planeFromPoints(Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1));
    EXPECT_EQ_CUSTOM(GLESC::Math::abs(planeFromPoints.getDistance()), 1.0);
}

TEST(PlaneTests, ThreePointsConstructor_IdenticalPointsException) {
    using namespace GLESC::Math;
    // Test constructor with identical points throws exception
    EXPECT_THROW({Plane identicalPointsPlane(Point(1, 1, 1), Point(1, 1, 1), Point(1, 1, 1));}, std::runtime_error);
}

TEST(PlaneTests, ThreePointsConstructor_CollinearPointsException) {
    using namespace GLESC::Math;
    // Test constructor with collinear points throws exception
    EXPECT_THROW({Plane collinearPointsPlane(Point(0, 0, 0), Point(1, 1, 1), Point(2, 2, 2));}
                 , AssertFailedException);
}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------- Point Line Constructor --------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------


TEST(PlaneTests, PointLineConstructor) {
    using namespace GLESC::Math;
    // Test constructor with a point and a line
    Plane planePointLine(Point(0, 0, 1), Line(Point(1, 1, 1), Direction(1, 0, 0)));
    EXPECT_EQ_CUSTOM(GLESC::Math::abs(planePointLine.getDistance()), 1.0);
}

TEST(PlaneTests, PointLineConstructor_PointOnLineException) {
    using namespace GLESC::Math;
    // Test constructor with a point on the line throws exception
    EXPECT_THROW({Plane pointOnLinePlane(Point(1, 1, 1), Line(Point(1, 1, 1), Direction(1, 0, 0)));},
        AssertFailedException);
}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------- Point Normal Constructor ------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------


TEST(PlaneTests, PointNormalConstructor) {
    using namespace GLESC::Math;
    // Test constructor with a point and a normal vector
    Plane planePointNormal(Point(0, 0, 1), Direction(0, 0, 1));
    EXPECT_EQ_CUSTOM(planePointNormal.getDistance(), -1.0);
}



TEST(PlaneTests, PerpendicularToCoordinateAxes) {
    using namespace GLESC::Math;
    // Plane perpendicular to Y axis
    Plane yPerpendicularPlane(Point(0, 1, 0), Direction(0, 1, 0));
    EXPECT_TRUE(yPerpendicularPlane.getNormal().isParallel(Direction(0, 1, 0)));
}




// ---------------------------------------------------------------------------------------------------------------------
// ----------------------------------------- Normal distance constructor -----------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

TEST(PlaneTests, NormalDistanceConstructor) {
    using namespace GLESC::Math;
    // Test constructor with normal and distance
    Plane planeNormalDistance(Direction(1, 0, 0), 1);
    EXPECT_EQ_VEC(planeNormalDistance.getNormal(), Direction(1, 0, 0));
    EXPECT_EQ_CUSTOM(planeNormalDistance.getDistance(), 1.0);
}

TEST(PlaneTests, NormalDistanceConstructor_NormalZeroLengthException) {
    using namespace GLESC::Math;
    // Test constructor with zero-length normal vector throws exception
    EXPECT_THROW({Plane zeroLengthNormalPlane(Direction(0, 0, 0), 1);}, AssertFailedException);
}
// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- Compare Planes --------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

TEST(PlaneTests, EqualityOperator) {
    using namespace GLESC::Math;
    // Two planes defined differently but are the same
    Plane plane1(Point(0, 0, 1), Direction(0, 0, 1));
    Plane plane2(Point(1, 1, 1), Direction(0, 0, 1));
    EXPECT_TRUE(plane1 == plane2);
}


TEST(PlaneTests, InequalityDueToDistance) {
    using namespace GLESC::Math;
    // Two planes with the same normal but different distances
    Plane plane1(Direction(1, 0, 0), 1);
    Plane plane2(Direction(1, 0, 0), 2);
    EXPECT_FALSE(plane1 == plane2);
}

TEST(PlaneTests, InequalityDueToNormal) {
    using namespace GLESC::Math;
    // Two planes with different normals but the same distance
    Plane plane1(Direction(1, 0, 0), 1);
    Plane plane2(Direction(0, 1, 0), 1);
    EXPECT_FALSE(plane1 == plane2);
}

TEST(PlaneTests, InequalityDueToBothNormalAndDistance) {
    using namespace GLESC::Math;
    // Two planes with different normals and distances
    Plane plane1(Direction(1, 0, 0), 1);
    Plane plane2(Direction(0, 1, 0), 2);
    EXPECT_FALSE(plane1 == plane2);
}

// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- Intersecting Planes ---------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

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

#endif