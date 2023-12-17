/**************************************************************************************************
 * @file   Polyhedron.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/geometry/GeometryTypes.h"
#include "Face.h"

namespace GLESC::Math {
    class Polyhedron {
    public:
        Polyhedron() = default;
        
        Polyhedron(const Points &vertices) : vertices(vertices) {}
        
        Polyhedron(const Points &vertices, const std::vector<FaceIndices> &faces)
        : vertices(vertices){
            for (const auto &face : faces) {
                addFace(face);
            }
        }
        
        Polyhedron(const std::initializer_list<Point> &vertices) : vertices(vertices) {}
        
        Polyhedron(const std::initializer_list<Point> &vertices,
                   const std::initializer_list<std::initializer_list<Index>> &faces) {
            for (const auto &vertex : vertices) {
                addVertex(vertex);
            }
            for (const auto &face : faces) {
                addFace(face);
            }
        }
        
        void addVertex(const Point &vertex) {
            vertices.push_back(vertex);
        }
        
        void addFace(std::initializer_list<Index> indices) {
            Face face(indices, vertices);
            faces.push_back(face);
        }
        
        void addFace(const FaceIndices &indices) {
            Face face(indices, vertices);
            faces.push_back(face);
        }
        
        [[nodiscard]] const std::vector<Face> &getFaces() const {
            return faces;
        }
        
        [[nodiscard]] std::vector<Point> &getVertices() {
            return vertices;
        }
        
        [[nodiscard]] const std::vector<Point> &getVertices() const {
            return vertices;
        }
        
        [[nodiscard]] bool intersects(const Polyhedron &other) const {
            for (const auto &face : faces) {
                for (const auto &otherFace : other.getFaces()) {
                    if (face.intersects(otherFace)) {
                        return true;
                    }
                }
            }
            return false;
        }
        
        [[nodiscard]] bool isInside(const Point &point) const {
            int intersections = 0;
            Line ray(point, Direction(1, 0, 0)); // Arbitrary ray direction
            
            for (const auto &face : faces) {
                if (face.intersects(ray)) {
                    intersections++;
                }
            }
            
            return (intersections % 2) == 1; // Odd number of intersections means inside
        }
        
        [[nodiscard]] bool isInside(const Face &face) {
            for (const auto &vertex : face.getPolyhedronVertices()) {
                if (!isInside(vertex)) {
                    return false;
                }
            }
            return true;
        }
        
        [[nodiscard]] bool isInside(const Polyhedron &polyhedron) const {
            for (const auto &vertex : polyhedron.getVertices()) {
                if (!isInside(vertex)) {
                    return false;
                }
            }
            return true;
        }
        
        [[nodiscard]] bool intersects(const Line &line) const {
            for (const auto &face : faces) {
                if (face.intersects(line)) {
                    return true;
                }
            }
            return false;
        }
        
        [[nodiscard]] bool intersects(const Point &point) const {
            for (const auto &face : faces) {
                if (face.intersects(point)) {
                    return true;
                }
            }
            return false;
        }
        
        [[nodiscard]] bool intersects(const Plane &plane) const {
            for (const auto &face : faces) {
                if (face.intersects(plane)) {
                    return true;
                }
            }
            return false;
        }
        /**
         * @brief Triangulates the polyhedron.
         * @details This function triangulates the polyhedron by forming triangles from the faces.
         * @attention This function only works for convex polyhedrons. Which is ok because the
         * face class only works for convex polygons.
         * @return The triangulated polyhedron.
         */
        Polyhedron triangulate() const {
            Polyhedron triangulatedPolyhedron(getVertices());
            
            for (const auto& face : getFaces()) {
                const auto& indices = face.getVertexIndices();
                if (indices.size() < 3) continue; // Skip degenerate faces
                
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
    
    private:
        std::vector<Vec3D> vertices;
        std::vector<Face> faces;
    }; // class Polyhedron
} // namespace GLESC::Math