/******************************************************************************
 * @file   PolyhedronFaceTests.cpp
 * @author Valentin Dumitru
 * @date   2023-12-14
 * @brief  Tests for the PolyhedronFace class.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/


#if MATH_GEOMETRY_UNIT_TESTING
#include "TestsConfig.cpp"
#include <gtest/gtest.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/core/math/geometry/figures/polyhedron/PolyhedronFace.h"

TEST(FaceTests, Constructor) {
    using namespace GLESC::Math;
    std::vector<Point> vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace face({0, 1, 2}, vertices);

    // Test if face normal is correct
    Direction expectedNormal(0, 0, 1); // Assuming a CCW winding order
    EXPECT_EQ(face.getNormal(), expectedNormal);

    // Test if face's vertices are set correctly
    const auto &faceVertices = face.getPolyhedronVertices();
    EXPECT_EQ(faceVertices, vertices);

    vertices = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}}; // Collinear points
    EXPECT_THROW({
                 PolyhedronFace({0, 1, 2}, vertices);
                 }, AssertFailedException);

    vertices = {{0, 0, 0}, {1, 0, 0}}; // Only 2 points
    EXPECT_THROW({
                 PolyhedronFace({0, 1}, vertices);
                 }, AssertFailedException);

    PolyhedronFace vertexTouchingFace({0, 1, 2}, {{1, 0, 0}, {2, -1, 0}, {2, 1, 0}});

    vertices.clear();
    vertices = {
        {1, -2, 3}, // We'll use this vertex
        {567899, -7878, 789}, {56456, -56756, 3456}, {563456, -56465, 34566}, {34565, -8876, 245},
        {7898, -23451, 76565}, {213419, -83675, 4521234}, {8741, -34524, 654356}, {56456, -342134, 6655},
        {3, -2, -1}, // And this one
        {343214, -5455435, 9786}, {34123, -65431, 54352}, {32313, -32312, 8888}, {404342, -22321, 443422},
        {1, 1, 1} // And this one
    };

    // Attempt to create a face with non-adjacent vertices
    EXPECT_NO_THROW({
        PolyhedronFace({0, 9, static_cast<unsigned int>(vertices.size())-1},
            vertices); // Non-adjacent but valid non-collinear points
        });

}

TEST(FaceTests, IntersectsPoint) {
    using namespace GLESC::Math;

    // Define a face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace face({0, 1, 2}, vertices);

    // Point inside the face
    Point pointInside(0.1, 0.1, 0);
    EXPECT_TRUE(face.intersects(pointInside));

    // Point outside the face
    Point pointOutside(1, 1, 0);
    EXPECT_FALSE(face.intersects(pointOutside));


    // Degenerate cases
    Points verticesForDegenerateCases = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace faceForDegenerateCases({0, 1, 2}, verticesForDegenerateCases);

    // Point on the edge of the face
    Point pointOnEdge(0.5, 0.5, 0);
    EXPECT_TRUE(faceForDegenerateCases.intersects(pointOnEdge));

    // Point at a vertex of the face
    Point pointOnVertex(0, 0, 0);
    EXPECT_TRUE(faceForDegenerateCases.intersects(pointOnVertex));
}

TEST(FaceTests, IntersectsLine) {
    using namespace GLESC::Math;

    // Define a face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace face({0, 1, 2}, vertices);

    // Line intersecting the face
    Line lineIntersecting(Point(0.5, 0.5, -1), Direction(0, 0, 1));
    EXPECT_TRUE(face.intersects(lineIntersecting));

    // Line not intersecting the face
    Line lineNotIntersecting(Point(2, 2, -1), Direction(0, 0, 1));
    EXPECT_FALSE(face.intersects(lineNotIntersecting));

    // Degenerate cases
    Points verticesForDegenerateCases = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace faceForDegenerateCases({0, 1, 2}, verticesForDegenerateCases);

    // Line parallel to an edge of the face
    Line lineParallel(Point(0, 0, -1), Direction(1, -1, 0));
    EXPECT_FALSE(faceForDegenerateCases.intersects(lineParallel));

    // Line coplanar with the face but not intersecting
    Line lineCoplanar(Point(2, 2, 0), Direction(1, 1, 0));
    EXPECT_FALSE(faceForDegenerateCases.intersects(lineCoplanar));
}

TEST(FaceTests, IntersectsFace) {
    using namespace GLESC::Math;

    // Define vertices for a triangular face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace face({0, 1, 2}, vertices);

    // Face intersecting the face (the same face)
    PolyhedronFace intersectingFace({0, 1, 2}, vertices);
    EXPECT_TRUE(face.intersects(intersectingFace));

    // Face not intersecting the face (above the original face)
    PolyhedronFace nonIntersectingFace({0, 1, 2}, {{0, 0, 1}, {1, 0, 1}, {0, 1, 1}});
    EXPECT_FALSE(face.intersects(nonIntersectingFace));

    // Coplanar face, not intersecting
    PolyhedronFace coplanarNonIntersectingFace({0, 1, 2}, {{2, 0, 0}, {3, 0, 0}, {2, 1, 0}});
    EXPECT_FALSE(face.intersects(coplanarNonIntersectingFace));

    // Edge-touching face
    PolyhedronFace edgeTouchingFace({0, 1, 2}, {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}});
    EXPECT_TRUE(face.intersects(edgeTouchingFace));

    // Vertex-touching face
    PolyhedronFace vertexTouchingFace({0, 1, 2}, {{1, 0, 0}, {2, -1, 0}, {2, 1, 0}});
    EXPECT_TRUE(face.intersects(vertexTouchingFace));
}


TEST(FaceTests, IntersectsPlane) {
    using namespace GLESC::Math;

    // Define vertices for a triangular face
    Points vertices = {{0, -1, 0}, {1, 0, 0}, {0, 1, 0}};
    PolyhedronFace face({0, 1, 2}, vertices);

    // Plane intersecting the face (completely)
    Plane intersectingPlane({0, 0, 1}, Direction(0, -1, 0));
    EXPECT_TRUE(face.intersects(intersectingPlane));

    // Plane intersecting the face but just in a vertex
    Plane vertexIntersectingPlane({0, -1, 1}, Direction(0, -1, 0));
    EXPECT_TRUE(face.intersects(vertexIntersectingPlane));

    // Plane intersecting the face but just in an edge
    Plane edgeIntersectingPlane({0, 0, 0}, Direction(-1, 0, 0));
    EXPECT_TRUE(face.intersects(edgeIntersectingPlane));

    // Plane not intersecting the face
    Plane nonIntersectingPlane({0, 0, 2}, Direction(0, 0, 1));
    EXPECT_FALSE(face.intersects(nonIntersectingPlane));

    // Another plane not intersecting the face
    Plane anotherNonIntersectingPlane({0, 5, 0}, Direction(0, 1, 0));
    EXPECT_FALSE(face.intersects(anotherNonIntersectingPlane));
}
#endif
