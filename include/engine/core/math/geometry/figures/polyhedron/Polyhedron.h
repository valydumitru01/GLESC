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

        void addQuad(const QuadIndices &faceParam);

        void clear();

        [[nodiscard]] Point getCenter() const;
        
        [[nodiscard]] const std::vector<PolyhedronFace> &getFaces() const;

        [[nodiscard]] const std::vector<Point> &getVertices() const;
        
        [[nodiscard]] bool intersects(const Polyhedron &other) const;

        [[nodiscard]] bool hasAnyVertexInside(const Polyhedron &other) const;
        
        [[nodiscard]] bool hasInside(const Point &point) const;
        
        [[nodiscard]] bool hasInside(const PolyhedronFace &face);
        
        [[nodiscard]] bool hasInside(const Polyhedron &polyhedron) const;
        
        [[nodiscard]] bool intersects(const Line &line) const;
        
        [[nodiscard]] bool intersects(const Point &point) const;
        
        [[nodiscard]] bool intersects(const Plane &plane) const;

        void operator=(const Polyhedron &other) {
            vertices = other.vertices;
            for (const PolyhedronFace &face : other.faces) {
                this->addFace(face.getVertexIndices());
            }
        }

    private:
        [[nodiscard]] bool isOutOfBounds(const std::vector<FaceIndices>& faces) const;
        [[nodiscard]] bool isOutOfBounds(const FaceIndices& face) const;
        std::vector<Vec3F> vertices;
        std::vector<PolyhedronFace> faces;
    }; // class Polyhedron
} // namespace GLESC::Math