/******************************************************************************
 * @file   PolyhedronTests.cpp
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
#include <unit/engine/core/math/MathCustomTestingFramework.h>
#include "engine/core/exceptions/core/AssertFailedException.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"

using namespace GLESC::Math;


TEST(GeometryTests, PolyhedronConstructor) {
    TEST_SECTION("Empty polyhedron constructor");
    Polyhedron emptyPolyhedron;
    EXPECT_EQ_CUSTOM(emptyPolyhedron.getVertices().size(), 0);
    EXPECT_EQ_CUSTOM(emptyPolyhedron.getFaces().size(), 0);


    TEST_SECTION("Polyhedron with 3 vertices and 1 face");
    Polyhedron polyhedronWithVertices({
                                          {0, 0, 0},
                                          {1, 1, 1},
                                          {2, 3, 2}
                                      }, {{0, 1, 2}});
    EXPECT_EQ_CUSTOM(polyhedronWithVertices.getVertices().size(), 3);
    EXPECT_EQ_CUSTOM(polyhedronWithVertices.getFaces().size(), 1);


    TEST_SECTION("Polyhedron with 3 vertices and 2 faces");
    Polyhedron verticesAndFacesPolyhedron2({
                                               {0, 0, 0},
                                               {1, 1, 1},
                                               {2, 3, 2}
                                           }, {
                                               {0, 1, 2},
                                               {0, 1, 2}
                                           });
    EXPECT_EQ_CUSTOM(verticesAndFacesPolyhedron2.getVertices().size(), 3);
    EXPECT_EQ_CUSTOM(verticesAndFacesPolyhedron2.getFaces().size(), 2);


    TEST_SECTION("Polyhedron with collinear vertices, expect death");
    EXPECT_THROW({
                 Polyhedron polyhedronCollinearVertices({{0, 0, 0},
                     {1, 1, 1},
                     {2, 2, 2}}, {{0, 1, 2}});
                 }, AssertFailedException);
}

Polyhedron createTetrahedron() {
    Polyhedron polyhedron;
    polyhedron.addVertex({0, 0, 0});
    polyhedron.addVertex({1, 0, 0});
    polyhedron.addVertex({0, 1, 0});
    polyhedron.addVertex({0, 0, 1});
    polyhedron.addFace({0, 1, 2});
    polyhedron.addFace({0, 1, 3});
    polyhedron.addFace({0, 2, 3});
    polyhedron.addFace({1, 2, 3});
    return polyhedron;
}

TEST(GeometryTests, PolyhedronIntersectsPoint) {
    using namespace GLESC::Math;

    // Polyhedron that intersects points
    auto polyhedronIntersectsPoint = createTetrahedron();

    // Test points inside the polyhedron
    EXPECT_TRUE(polyhedronIntersectsPoint.intersects(Point{0.25f, 0.25f, 0.25f}));
    // Test points on the edge of the polyhedron
    EXPECT_TRUE(polyhedronIntersectsPoint.intersects(Point{0.5f, 0.5f, 0}));
    // Test points at the vertices of the polyhedron
    EXPECT_TRUE(polyhedronIntersectsPoint.intersects(Point{0, 0, 0}));

    // Polyhedron that does not intersect points
    auto polyhedronNotIntersectsPoint = createTetrahedron();

    // Test points outside the polyhedron
    EXPECT_FALSE(polyhedronNotIntersectsPoint.intersects(Point{1.5f, 1.5f, 1.5f}));
    // Test points close to but outside the polyhedron
    EXPECT_FALSE(polyhedronNotIntersectsPoint.intersects(Point{-0.01f, -0.01f, -0.01f}));
}

TEST(GeometryTests, PolyhedronIntersectsLine) {
    using namespace GLESC::Math;

    auto tetrahedron = createTetrahedron();

    // Test line intersecting the polyhedron
    EXPECT_TRUE(tetrahedron.intersects(Line({0, 0, 0}, {1, 1, 1}))); // Through the body
    EXPECT_TRUE(tetrahedron.intersects(Line({0.5f, 0, 0}, {0, 1, 1}))); // Along the edge
    EXPECT_TRUE(tetrahedron.intersects(Line({0, 0, 0}, {0, 0, 1}))); // At the vertex

    // Test line not intersecting the polyhedron
    EXPECT_FALSE(tetrahedron.intersects(Line({2, 2, 2}, {3, 3, 3})));
}

TEST(GeometryTests, PolyhedronIntersectsPlane) {
    using namespace GLESC::Math;

    auto tetrahedron = createTetrahedron();

    // Test plane intersecting the polyhedron
    EXPECT_TRUE(tetrahedron.intersects(Plane({0, 0, 0.5f}, {0, 0, 1}))); // Through the body
    EXPECT_TRUE(tetrahedron.intersects(Plane({0, 0, 0}, {0, 1, 0}))); // Along the face
    EXPECT_TRUE(tetrahedron.intersects(Plane({0, 0, 0}, {1, 1, 1}))); // At the vertex

    // Test plane not intersecting the polyhedron
    EXPECT_FALSE(tetrahedron.intersects(Plane({2, 2, 2}, {1, 1, 1})));
}

TEST(GeometryTests, PolyhedronIntersectsPolyhedron) {
    using namespace GLESC::Math;

    auto tetrahedron = createTetrahedron();
    auto displacedTetrahedron = createTetrahedron();
    // Move the displacedTetrahedron so it doesn't intersect with the original
    for (auto& vertex : displacedTetrahedron.getVerticesMutable()) {
        vertex += Point{2, 2, 2}; // Displace by a vector
    }

    // Test polyhedron intersecting itself
    EXPECT_TRUE(tetrahedron.intersects(tetrahedron));

    // Test polyhedron not intersecting another polyhedron
    EXPECT_FALSE(tetrahedron.intersects(displacedTetrahedron));
}
#endif
