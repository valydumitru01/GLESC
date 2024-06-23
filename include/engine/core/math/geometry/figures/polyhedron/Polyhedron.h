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
        /**
         * @brief Construct a new Polyhedron object. Default constructor.
         */
        Polyhedron() = default;

        /**
         * @brief Construct a new Polyhedron object.
         * @param vertices The vertices of the polyhedron.
         * @param faces The faces of the polyhedron.
         */
        Polyhedron(Points vertices, const std::vector<FaceIndices> &faces);

        /**
         * @brief Add a vertex to the polyhedron.
         * @param vertex The vertex to add.
         */
        void addVertex(const Point &vertex);

        /**
         * @brief Add a face to the polyhedron. The face is defined by the indices of the vertices.
         * @param faceParam The face to add.
         */
        void addFace(const FaceIndices &faceParam);

        /**
         * @brief Add a quad to the polyhedron. The quad is defined by the indices of the vertices.
         * @details It will create two triangles from the quad.
         * @param faceParam The quad to add.
         */
        void addQuad(const QuadIndices &faceParam);

        /**
         * @brief Clear the polyhedron. Erase all vertices and faces.
         */
        void clear();

        /**
         * @brief Get the center of the polyhedron.
         * @return Point The center of the polyhedron.
         */
        [[nodiscard]] Point getCenter() const;

        /**
         * @brief Get the faces of the polyhedron.
         * @return const std::vector<PolyhedronFace>& The faces of the polyhedron.
         */
        [[nodiscard]] const std::vector<PolyhedronFace> &getFaces() const;

        /**
         * @brief Get the vertices of the polyhedron.
         * @return const std::vector<Point>& The vertices of the polyhedron.
         */
        [[nodiscard]] const std::vector<Point> &getVertices() const;

        /**
         * @brief Get the vertices of the polyhedron.
         * @return std::vector<Point>& The vertices of the polyhedron.
         */
        [[nodiscard]] std::vector<Point>& getVerticesMutable();

        /**
         * @brief Checks if the polyhedron intersects with another polyhedron.
         * @details Uses SAT but for each face of the polyhedron. Iterates through all faces of the polyhedron
         * and applies the SAT algorithm to check for intersection for each face.
         * @param other The polyhedron to check for intersection.
         * @return True if the polyhedron intersects with the other polyhedron, false otherwise.
         */
        [[nodiscard]] bool intersects(const Polyhedron &other) const;

        /**
         * @brief Checks if the polyhedron has any vertex inside another polyhedron.
         * @details Checks if any vertex of the polyhedron is inside the other polyhedron.
         * @param other The polyhedron to check for vertices inside.
         * @return True if the polyhedron has any vertex inside the other polyhedron, false otherwise.
         */
        [[nodiscard]] bool hasAnyVertexInside(const Polyhedron &other) const;

        /**
         * @brief Checks if a point is inside the polyhedron.
         * @param point The point to check.
         * @return True if the point is inside the polyhedron, false otherwise.
         */
        [[nodiscard]] bool hasInside(const Point &point) const;

        /**
         * @brief Checks if a face is inside the polyhedron.
         * @param face The face to check.
         * @return True if the face is inside the polyhedron, false otherwise.
         */
        [[nodiscard]] bool hasInside(const PolyhedronFace &face);

        /**
         * @brief Checks if the polyhedron has any vertex inside another polyhedron.
         * @details Checks if any vertex of the polyhedron is inside the other polyhedron.
         * @param polyhedron The polyhedron to check for vertices inside.
         * @return True if the polyhedron has any vertex inside the other polyhedron, false otherwise.
         */
        [[nodiscard]] bool hasInside(const Polyhedron &polyhedron) const;

        /**
         * @brief Checks if the polyhedron intersects with a line.
         * @param line The line to check for intersection.
         * @return True if the polyhedron intersects with the line, false otherwise.
         */
        [[nodiscard]] bool intersects(const Line &line) const;

        /**
         * @brief Checks if the polyhedron intersects with a point.
         * @param point The point to check for intersection.
         * @return True if the polyhedron intersects with the point, false otherwise.
         */
        [[nodiscard]] bool intersects(const Point &point) const;

        /**
         * @brief Checks if the polyhedron intersects with a plane.
         * @param plane The plane to check for intersection.
         * @return True if the polyhedron intersects with the plane, false otherwise.
         */
        [[nodiscard]] bool intersects(const Plane &plane) const;

        /**
         * @brief Assignment operator.
         * @details It needs to be defined like this because the default doesnt work because PolyhedronFace contains
         * a reference to the vertices of the polyhedron.
         * @param other The polyhedron to assign.
         * @return Polyhedron& The assigned polyhedron.
         */
        Polyhedron& operator=(const Polyhedron &other) {
            vertices = other.vertices;
            return *this;
        }

    private:
        /**
         * @brief Checks if the list of face indices are out of bounds with the current size of the vertices.
         * @details is used to check if the faces are valid when adding them to the polyhedron.
         * @param faces The face indices to check.
         * @return True if the face indices are out of bounds, false otherwise.
         */
        [[nodiscard]] bool isOutOfBounds(const std::vector<FaceIndices>& faces) const;
        /**
         * @brief Checks if the face indices are out of bounds with the current size of the vertices.
         * @details is used to check if the face is valid when adding it to the polyhedron.
         * @param face The face indices to check.
         * @return True if the face indices are out of bounds, false otherwise.
         */
        [[nodiscard]] bool isOutOfBounds(const FaceIndices& face) const;
        std::vector<Vec3F> vertices;
        std::vector<PolyhedronFace> faces;
    }; // class Polyhedron
} // namespace GLESC::Math