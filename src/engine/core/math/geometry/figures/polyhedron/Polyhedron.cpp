/**************************************************************************************************
 * @file   Polyhedron.cpp
 * @author Valentin Dumitru
 * @date   2023-12-24
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <engine/core/math/algebra/vector/VectorAlgorithms.h>
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"

using namespace GLESC::Math;



Polyhedron::Polyhedron(Points vertices, const std::vector<FaceIndices> &faces) :
        vertices(std::move(vertices)) {
    for (const auto &face : faces) {
        addFace(face);
    }
}

Polyhedron::Polyhedron(const std::initializer_list<Point> &vertices,
                       const std::initializer_list<std::initializer_list<Index>> &faces) {
    for (const auto &vertex : vertices) {
        addVertex(vertex);
    }
    for (const auto &face : faces) {
        addFace(face);
    }
}

void Polyhedron::addVertex(const Point &vertex) {
    vertices.push_back(vertex);
}

void Polyhedron::addFace(std::initializer_list<Index> indices) {
    PolyhedronFace face(indices, vertices);
    faces.push_back(face);
}

void Polyhedron::addFace(const FaceIndices &indices) {
    // Check for degenerate faces
    D_ASSERT_FALSE(indices.size() < 3, "Face must have at least 3 vertices.");
    // Check for repeated vertices
    for (size_t i = 0; i < indices.size(); ++i) {
        for (size_t j = i + 1; j < indices.size(); ++j) {
            D_ASSERT_FALSE(indices[i] == indices[j], "Face must not have repeated vertices.");
        }
    }
    // Check for out of bounds indices
    for (const auto &index : indices) {
        D_ASSERT_FALSE(index >= vertices.size(), "Face must not have out of bounds indices.");
    }
    // Check for degenerate face where vertices are collinear
    if (indices.size() == 3) {
        const Point &a = vertices[indices[0]];
        const Point &b = vertices[indices[1]];
        const Point &c = vertices[indices[2]];
        D_ASSERT_FALSE(a.isCollinear({b, c}), "Face must not have collinear vertices.");
    }
    
    PolyhedronFace face(indices, vertices);
    faces.push_back(face);
}

[[nodiscard]] const std::vector<PolyhedronFace> &Polyhedron::getFaces() const {
    return faces;
}

[[nodiscard]] std::vector<Point> &Polyhedron::getVertices() {
    return vertices;
}

[[nodiscard]] const std::vector<Point> &Polyhedron::getVertices() const {
    return vertices;
}

[[nodiscard]] bool Polyhedron::intersects(const Polyhedron &other) const {
    for (const auto &face : faces) {
        for (const auto &otherFace : other.getFaces()) {
            if (face.intersects(otherFace)) {
                return true;
            }
        }
    }
    return false;
}

[[nodiscard]] bool Polyhedron::isInside(const Point &point) const {
    int intersections = 0;
    Line ray(point, Direction(1, 0, 0)); // Arbitrary ray direction
    
    for (const auto &face : faces) {
        if (face.intersects(ray)) {
            intersections++;
        }
    }
    
    return (intersections % 2) == 1; // Odd number of intersections means inside
}

[[nodiscard]] bool Polyhedron::isInside(const PolyhedronFace &face) {
    for (const auto &vertex : face.getPolyhedronVertices()) {
        if (!isInside(vertex)) {
            return false;
        }
    }
    return true;
}

[[nodiscard]] bool Polyhedron::isInside(const Polyhedron &polyhedron) const {
    for (const auto &vertex : polyhedron.getVertices()) {
        if (!isInside(vertex)) {
            return false;
        }
    }
    return true;
}

[[nodiscard]] bool Polyhedron::intersects(const Line &line) const {
    for (const auto &face : faces) {
        if (face.intersects(line)) {
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool Polyhedron::intersects(const Point &point) const {
    for (const auto &face : faces) {
        if (face.intersects(point)) {
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool Polyhedron::intersects(const Plane &plane) const {
    for (const auto &face : faces) {
        if (face.intersects(plane)) {
            return true;
        }
    }
    return false;
}

Polyhedron Polyhedron::triangulate() const {
    // Copy the polyhedron
    Polyhedron triangulatedPolyhedron(*this);
    
    for (const auto &face : getFaces()) {
        const auto &indices = face.getVertexIndices();
        if (indices.size() < 3)
            continue; // Skip degenerate faces
        
        // Reference vertex for triangulation
        Index refVertex = indices[0];
        
        // Form triangles and add them to the new polyhedron
        for (size_t i = 1; i + 1 < indices.size(); ++i) {
            FaceIndices triangleIndices = {refVertex, indices[i], indices[i + 1]};
            triangulatedPolyhedron.addFace(triangleIndices);
        }
    }
    
    return triangulatedPolyhedron;
}
