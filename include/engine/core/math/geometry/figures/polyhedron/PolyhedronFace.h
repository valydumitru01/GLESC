/**************************************************************************************************
 * @file   PolyhedronFace.cpp
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Class that represents a face of a polyhedron.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <array>
#include <utility>
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/math/geometry/figures/line/Line.h"
#include "engine/core/math/geometry/figures/plane/Plane.h"

namespace GLESC::Math {
    class PolyhedronFace {
    public:
        PolyhedronFace(FaceIndices indicesParam, const Points& verticesParam);

        ~PolyhedronFace() = default;

        /**
        * @brief Custom copy constructor.
        *
        * Creates a new PolyhedronFace that refers to the same set of vertices as the other face.
        * This is necessary because the default copy constructor is deleted due to the presence
        * of a reference member.
        *
        * @param other The PolyhedronFace to copy from.
        */
        PolyhedronFace(const PolyhedronFace& other)
            : polyhedronVertices(other.polyhedronVertices), indices(other.indices),
              plane(other.plane) {}

        /**
        * @brief Deleted assignment operator.
        *
        * Assigns this PolyhedronFace to refer to the same set of vertices as the other face.
        * This operator is necessary because the default assignment operator is deleted due to
        * the presence of a reference member. Note that this operator doesn't allow reassignment
        * of the reference itself; it only ensures consistent copying of other assignable members.
        *
        */
        PolyhedronFace& operator=(const PolyhedronFace& other) = delete;

        const Point &getNormal() const { return plane.getNormal(); }

        const std::vector<Point>& getPolyhedronVertices() const { return polyhedronVertices; }

        const FaceIndices& getVertexIndices() const { return indices; }

        const Plane& getPlane() const { return plane; }

        /**
        * @brief Checks if the current face intersects with the given face.
        *
        * This function determines whether the current face intersects with the given face.
        * It checks if any of the edges of the current face intersects with any of the edges
        * of the given face.
        * @details This uses SAT (Separating Axis Theorem) to determine if the faces intersect.
        * @attention This only works for convex polygons.
        * Convex polygons:
        *      https://en.wikipedia.org/wiki/Convex_polygon
        * Convex polyhedrons:
        *     https://en.wikipedia.org/wiki/Concave_polygon
        *
        * @param face The face to check for intersection.
        * @return True if the current face intersects with the given face, false otherwise.
        */
        [[nodiscard]] bool intersects(const PolyhedronFace& face) const;


        bool intersects(const Vec3F& point) const;

        bool intersects(const Line& line) const;

        /**
        * @brief Checks if the face intersects with a given plane.
        *
        * This function determines whether the face intersects with the plane by checking the
        * position of the face's vertices relative to the plane. If some vertices are on one side
        * of the plane and some on the other, it indicates that the face intersects the plane.
        *
        * @param plane The plane to check for intersection with the face.
        * @return True if the face intersects with the plane, false otherwise.
        */
        bool intersects(const Plane& plane) const;

    private:
        /**
        * @brief The indices of the vertices of the face. These indices are used to access the
        *       vertices of the polyhedron that contains this face.
        */
        FaceIndices indices;
        /**
        * @brief The (infinite) plane that contains the face. The plane is defined by its normal
        *       vector and a distance from the origin.
        */
        Plane plane;
        /**
        * @brief Const reference to the vertices of the polyhedron that contains this face.
        */
        const std::vector<Point>& polyhedronVertices;


        // Other methods like area calculation, etc., can be added as needed.
    };
} // namespace GLESC::Math
