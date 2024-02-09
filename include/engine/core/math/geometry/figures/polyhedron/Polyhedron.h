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
#include "engine/core/math/geometry/figures/polyhedron/PolyhedronFace.h"

namespace GLESC::Math {
    class Polyhedron {
    public:
        Polyhedron() = default;
        
        Polyhedron(Points vertices, const std::vector<FaceIndices> &faces);
        
        void addVertex(const Point &vertex);
        
        void addFace(const FaceIndices &faceParam);
        
        [[nodiscard]] const std::vector<PolyhedronFace> &getFaces() const;
        
        [[nodiscard]] std::vector<Point> &getVertices();
        
        [[nodiscard]] const std::vector<Point> &getVertices() const;
        
        [[nodiscard]] bool intersects(const Polyhedron &other) const;
        
        [[nodiscard]] bool isInside(const Point &point) const;
        
        [[nodiscard]] bool isInside(const PolyhedronFace &face);
        
        [[nodiscard]] bool isInside(const Polyhedron &polyhedron) const;
        
        [[nodiscard]] bool intersects(const Line &line) const;
        
        [[nodiscard]] bool intersects(const Point &point) const;
        
        [[nodiscard]] bool intersects(const Plane &plane) const;
        
        /**
         * @brief Triangulates the polyhedron.
         * @details This function triangulates the polyhedron by forming triangles from the faces.
         * If the polyhedron is already triangulated, it will do nothing and return the same
         * polyhedron.
         * @attention This function only works for convex polyhedrons. Which is ok because the
         * face class only works for convex polygons.
         * @return The triangulated polyhedron.
         */
        Polyhedron triangulate() const;
    
    private:
        [[nodiscard]] bool isOutOfBounds(const std::vector<FaceIndices>& faces) const;
        [[nodiscard]] bool isOutOfBounds(const FaceIndices& face) const;
        std::vector<Vec3D> vertices;
        std::vector<PolyhedronFace> faces;
    }; // class Polyhedron
} // namespace GLESC::Math