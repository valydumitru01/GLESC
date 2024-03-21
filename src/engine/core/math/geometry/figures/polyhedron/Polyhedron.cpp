/**************************************************************************************************
 * @file   Polyhedron.cpp
 * @author Valentin Dumitru
 * @date   2023-12-24
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <engine/core/math/algebra/vector/VectorMixedAlgorithms.h>
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"

using namespace GLESC::Math;


Polyhedron::Polyhedron(Points vertices, const std::vector<FaceIndices>& faces) :
    vertices(std::move(vertices)) {
    for (const auto& face : faces) {
        addFace(face);
    }
}

void Polyhedron::addVertex(const Point& vertex) {
    vertices.push_back(vertex);
}

void Polyhedron::clear() {
    vertices = std::vector<Vec3D>();
    faces = std::vector<PolyhedronFace>();
}


void Polyhedron::addFace(const FaceIndices& faceParam) {
    // Check for repeated vertices
    for (size_t i = 0; i < faceParam.size(); ++i) {
        for (size_t j = i + 1; j < faceParam.size(); ++j) {
            D_ASSERT_FALSE(faceParam[i] == faceParam[j], "Face must not have repeated vertices.");
        }
    }
    // Check for out of bounds indices
    D_ASSERT_FALSE(this->isOutOfBounds(faceParam), "Face must not have out of bounds indices.");

    PolyhedronFace face(faceParam, vertices);
    faces.push_back(face);
}

[[nodiscard]] const std::vector<PolyhedronFace>& Polyhedron::getFaces() const {
    return faces;
}

[[nodiscard]] std::vector<Point>& Polyhedron::getVerticesMutable() {
    return vertices;
}

[[nodiscard]] const std::vector<Point>& Polyhedron::getVertices() const {
    return vertices;
}

[[nodiscard]] bool Polyhedron::intersects(const Polyhedron& other) const {
    for (const auto& face : faces) {
        for (const auto& otherFace : other.getFaces()) {
            if (face.intersects(otherFace)) {
                return true;
            }
        }
    }
    return false;
}

[[nodiscard]] bool Polyhedron::isInside(const Point& point) const {
    int intersections = 0;
    Line ray(point, Direction(1, 0, 0)); // Arbitrary ray direction

    for (const auto& face : faces) {
        if (face.intersects(ray)) {
            intersections++;
        }
    }

    return (intersections % 2) == 1; // Odd number of intersections means inside
}

[[nodiscard]] bool Polyhedron::isInside(const PolyhedronFace& face) {
    for (const auto& vertex : face.getPolyhedronVertices()) {
        if (!isInside(vertex)) {
            return false;
        }
    }
    return true;
}

[[nodiscard]] bool Polyhedron::isInside(const Polyhedron& polyhedron) const {
    for (const auto& vertex : polyhedron.getVertices()) {
        if (!isInside(vertex)) {
            return false;
        }
    }
    return true;
}

[[nodiscard]] bool Polyhedron::intersects(const Line& line) const {
    for (const auto& face : faces) {
        if (face.intersects(line)) {
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool Polyhedron::intersects(const Point& point) const {
    for (const auto& face : faces) {
        if (face.intersects(point)) {
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool Polyhedron::intersects(const Plane& plane) const {
    for (const auto& face : faces) {
        if (face.intersects(plane)) {
            return true;
        }
    }
    return false;
}



bool Polyhedron::isOutOfBounds(const std::vector<FaceIndices>& faces) const {
    for (const auto& face : faces) {
        if (isOutOfBounds(face)) {
            return true;
        }
    }
    return false;
}

bool Polyhedron::isOutOfBounds(const FaceIndices& face) const {
    for (const auto& index : face) {
        if (index >= vertices.size()) {
            return true;
        }
    }
    return false;
}