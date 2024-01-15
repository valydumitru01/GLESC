/**************************************************************************************************
 * @file   PolyhedronFace.cpp
 * @author Valentin Dumitru
 * @date   2023-12-24
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/core/math/geometry/figures/polyhedron/PolyhedronFace.h"

using namespace GLESC::Math;

PolyhedronFace::PolyhedronFace(std::initializer_list<Index> indices, const Points &vertices) :
        PolyhedronFace(FaceIndices(indices), vertices) {
}

PolyhedronFace::PolyhedronFace(FaceIndices indicesParam, const Points &verticesParam) :
        indices(std::move(indicesParam)), polyhedronVertices(&verticesParam) {
    D_ASSERT_TRUE(indices.size() >= 3, "Face must have 3 vertices.");
    D_ASSERT_TRUE(polyhedronVertices->size() >= 3, "Polyhedron must have at least 3 vertices.");
    D_ASSERT_FALSE(polyhedronVertices->at(indices[0]).isCollinear({polyhedronVertices->at(indices[1]),
                                                                   polyhedronVertices->at(indices[2])}),
                  "Face must not have collinear vertices.");
    
    // Construct the plane that contains this face with the 3 points constructor
    plane = Plane(polyhedronVertices->at(0), polyhedronVertices->at(1), polyhedronVertices->at(2));
}


[[nodiscard]] bool PolyhedronFace::intersects(const PolyhedronFace &face) const {
    // Get normals of both faces
    const Vec3D thisNormal = getNormal();
    const Vec3D otherNormal = face.getNormal();
    
    // Vector to store all axes to test
    std::vector<Vec3D> axes;
    
    // Add face normals to axes (to handle face-face parallel cases)
    axes.push_back(thisNormal);
    axes.push_back(otherNormal);
    
    // Function to add unique axes from edge cross products
    auto addUniqueAxis = [&axes](const Vec3D &edgeNormal) {
        // Normalize the edge normal
        Vec3D normalized = edgeNormal.normalize();
        // Check if this normal is unique
        for (const auto &axis : axes) {
            if (axis.isParallel(normalized)) {
                return; // Skip if parallel axis already exists
            }
        }
        axes.push_back(normalized); // Add unique axis
    };
    
    // Generate axes from edges of this face
    for (size_t i = 0; i < indices.size(); ++i) {
        size_t next = (i + 1) % indices.size();
        Vec3D edge = polyhedronVertices->at(next) - polyhedronVertices->at(i);
        addUniqueAxis(thisNormal.cross(edge));
    }
    
    // Generate axes from edges of other face
    for (size_t i = 0; i < face.indices.size(); ++i) {
        size_t next = (i + 1) % face.indices.size();
        Vec3D edge = face.polyhedronVertices->at(next) - face.polyhedronVertices->at(i);
        addUniqueAxis(otherNormal.cross(edge));
    }
    
    // Check for overlap on all axes
    for (const auto &axis : axes) {
        double thisMin = std::numeric_limits<double>::max();
        double thisMax = std::numeric_limits<double>::lowest();
        double otherMin = std::numeric_limits<double>::max();
        double otherMax = std::numeric_limits<double>::lowest();
        
        // Project vertices of both faces onto the axis
        for (auto index : indices) {
            double projection = polyhedronVertices->at(index).dot(axis);
            thisMin = std::min(thisMin, projection);
            thisMax = std::max(thisMax, projection);
        }
        for (auto index : face.indices) {
            double projection = face.polyhedronVertices->at(index).dot(axis);
            otherMin = std::min(otherMin, projection);
            otherMax = std::max(otherMax, projection);
        }
        
        // Check for separation on this axis
        if (thisMax < otherMin || otherMax < thisMin) {
            return false; // No overlap, faces do not intersect
        }
    }
    
    return true; // Overlap on all axes, faces intersect
}


bool PolyhedronFace::intersects(const Vec3D &point) const {
    for (size_t i = 0; i < polyhedronVertices->size(); ++i) {
        Vec3D edge = polyhedronVertices->at((i + 1) % polyhedronVertices->size()) - polyhedronVertices->at(i);
        Vec3D toPoint = point - polyhedronVertices->at(i);
        if (getNormal().cross(edge).dot(toPoint) < 0) {
            return false; // Point is outside this edge
        }
    }
    return true; // Point is inside all edges
}

bool PolyhedronFace::intersects(const Line &line) const {
    // Check if the line is parallel to the plane
    double dotProduct = getNormal().dot(line.getDirection());
    if (GLESC::Math::abs(dotProduct) < std::numeric_limits<double>::epsilon()) {
        return false; // Line is parallel to the plane, no intersection
    }
    
    // Find the intersection point with the plane
    double t = -(getNormal().dot(line.getPoint() - polyhedronVertices->at(0)) + plane.getDistance() / dotProduct);
    Vec3D intersectionPoint = line.getPoint() + line.getDirection() * t;
    
    // Check if the intersection point is inside the face
    return intersects(intersectionPoint);
}

bool PolyhedronFace::intersects(const Plane &planeParam) const {
    // Counters for vertices on each side of the plane
    int positive = 0, negative = 0;
    
    for (auto index : indices) {
        // Calculate the signed distance from the vertex to the plane
        double distance = planeParam.distanceToPoint(polyhedronVertices->at(index));
        
        // Count vertices on each side of the plane
        if (distance > 0)
            positive++;
        else if (distance < 0)
            negative++;
        
        // Early exit if vertices on both sides are found
        if (positive > 0 && negative > 0)
            return true;
    }
    
    // If function reaches this point, no intersection is found
    return false;
}



