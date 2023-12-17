/******************************************************************************
 * @file   FaceTests.cpp
 * @author Valentin Dumitru
 * @date   2023-12-14
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
 

#include <gtest/gtest.h>
#include <engine/core/math/Math.h>
#include <engine/core/math/geometry/GeometryTypes.h>
#include <engine/core/math/geometry/Face.h>

TEST(FaceTests, Constructor) {
    using namespace GLESC::Math;
    std::vector<Point> vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face face({0, 1, 2}, vertices);
    
    // Test if face normal is correct
    Direction expectedNormal(0, 0, 1); // Assuming a CCW winding order
    EXPECT_EQ(face.getNormal(), expectedNormal);
    
    // Test if face's vertices are set correctly
    const auto& faceVertices = face.getPolyhedronVertices();
    EXPECT_EQ(faceVertices, vertices);
}

TEST(FaceTests, IntersectsPoint) {
    using namespace GLESC::Math;
    
    // Define a face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face face({0, 1, 2}, vertices);
    
    // Point inside the face
    Vec3D pointInside(0.1, 0.1, 0);
    EXPECT_TRUE(face.intersects(pointInside));
    
    // Point outside the face
    Vec3D pointOutside(1, 1, 0);
    EXPECT_FALSE(face.intersects(pointOutside));
    
    
    
    // Degenerate cases
    Points verticesForDegenerateCases = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face faceForDegenerateCases({0, 1, 2}, verticesForDegenerateCases);
    
    // Point on the edge of the face
    Vec3D pointOnEdge(0.5, 0.5, 0);
    EXPECT_TRUE(faceForDegenerateCases.intersects(pointOnEdge));
    
    // Point at a vertex of the face
    Vec3D pointOnVertex(0, 0, 0);
    EXPECT_TRUE(faceForDegenerateCases.intersects(pointOnVertex));
}

TEST(FaceTests, IntersectsFace) {
    using namespace GLESC::Math;
    
    // Define vertices for a triangular face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face face({0, 1, 2}, vertices);
    
    // Face intersecting the face
    Face intersectingFace({0, 1, 2}, vertices);
    EXPECT_TRUE(face.intersects(intersectingFace));
    
    // Face not intersecting the face (above the original face)
    Face nonIntersectingFace({0, 1, 2}, {{0, 0, 1}, {1, 0, 1}, {0, 1, 1}});
    EXPECT_FALSE(face.intersects(nonIntersectingFace));
    
    // Coplanar face, not intersecting
    Face coplanarNonIntersectingFace({0, 1, 2}, {{2, 0, 0}, {3, 0, 0}, {2, 1, 0}});
    EXPECT_FALSE(face.intersects(coplanarNonIntersectingFace));
    
    // Edge-touching face
    Face edgeTouchingFace({0, 1, 2}, {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}});
    EXPECT_TRUE(face.intersects(edgeTouchingFace));
    
    // Vertex-touching face
    Face vertexTouchingFace({0, 1, 2}, {{1, 0, 0}, {2, -1, 0}, {2, 1, 0}});
    EXPECT_TRUE(face.intersects(vertexTouchingFace));
}

TEST(FaceTests, IntersectsLine) {
    using namespace GLESC::Math;
    
    // Define a face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face face({0, 1, 2}, vertices);
    
    // Line intersecting the face
    Line lineIntersecting(Vec3D(0.5, 0.5, -1), Vec3D(0, 0, 1));
    EXPECT_TRUE(face.intersects(lineIntersecting));
    
    // Line not intersecting the face
    Line lineNotIntersecting(Vec3D(2, 2, -1), Vec3D(0, 0, 1));
    EXPECT_FALSE(face.intersects(lineNotIntersecting));
    
    
    // Degenerate cases
    Points verticesForDegenerateCases = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face faceForDegenerateCases({0, 1, 2}, verticesForDegenerateCases);
    
    // Line parallel to an edge of the face
    Line lineParallel(Vec3D(0, 0, -1), Vec3D(1, -1, 0));
    EXPECT_FALSE(faceForDegenerateCases.intersects(lineParallel));
    
    // Line coplanar with the face but not intersecting
    Line lineCoplanar(Vec3D(2, 2, 0), Vec3D(1, 1, 0));
    EXPECT_FALSE(faceForDegenerateCases.intersects(lineCoplanar));
}



TEST(FaceTests, IntersectsPlane) {
    using namespace GLESC::Math;
    
    // Define vertices for a triangular face
    Points vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    Face face({0, 1, 2}, vertices);
    
    // Plane intersecting the face
    Plane intersectingPlane({0, 0, 1}, Direction(0, 0, 1));
    EXPECT_TRUE(face.intersects(intersectingPlane));
    
    // Plane not intersecting the face
    Plane nonIntersectingPlane({0, 0, 2}, Direction(0, 0, 1));
    EXPECT_FALSE(face.intersects(nonIntersectingPlane));
}
