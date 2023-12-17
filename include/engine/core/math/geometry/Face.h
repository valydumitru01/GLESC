/**************************************************************************************************
 * @file   Face.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <array>
#include <utility>
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/core/math/Vector.h"
#include "Line.h"
#include "Plane.h"

namespace GLESC::Math {
    class Face {
    public:
        Face(std::initializer_list<Index> indices, const Points &vertices) :
                Face(FaceIndices(indices), vertices) {
        }
        
        Face(FaceIndices indicesParam, const Points &verticesParam) :
                indices(std::move(indicesParam)), verticesRef(verticesParam) {
            D_ASSERT_TRUE(indices.size() >= 3, "Face must have 3 vertices.");
            
            Vec3D normal = calculateNormal();
            double distance = -normal.dot(verticesRef[0]);
            plane = Plane(normal, distance);
        }
        
        ~Face() = default;
        
        
        const Vec3D &getNormal() const {
            return plane.getNormal();
        }
        
        const std::vector<Point> &getPolyhedronVertices() const {
            return verticesRef;
        }
        
        const std::vector<Index> &getVertexIndices() const {
            return indices;
        }
        
        Plane getPlane() const {
            return plane;
        }
        
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
        [[nodiscard]] bool intersects(const Face &face) const {
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
                Vec3D edge = verticesRef[next] - verticesRef[i];
                addUniqueAxis(thisNormal.cross(edge));
            }
            
            // Generate axes from edges of other face
            for (size_t i = 0; i < face.indices.size(); ++i) {
                size_t next = (i + 1) % face.indices.size();
                Vec3D edge = face.verticesRef[next] - face.verticesRef[i];
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
                    double projection = verticesRef[index].dot(axis);
                    thisMin = std::min(thisMin, projection);
                    thisMax = std::max(thisMax, projection);
                }
                for (auto index : face.indices) {
                    double projection = face.verticesRef[index].dot(axis);
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
        
        
        bool intersects(const Vec3D &point) const {
            for (size_t i = 0; i < verticesRef.size(); ++i) {
                Vec3D edge = verticesRef[(i + 1) % verticesRef.size()] - verticesRef[i];
                Vec3D toPoint = point - verticesRef[i];
                if (getNormal().cross(edge).dot(toPoint) < 0) {
                    return false; // Point is outside this edge
                }
            }
            return true; // Point is inside all edges
        }
        
        bool intersects(const Line &line) const {
            // Check if the line is parallel to the plane
            double dotProduct = getNormal().dot(line.direction);
            if (std::abs(dotProduct) < std::numeric_limits<double>::epsilon()) {
                return false; // Line is parallel to the plane, no intersection
            }
            
            // Find the intersection point with the plane
            double t = -(getNormal().dot(line.point - verticesRef[0]) +
                         plane.getDistance() / dotProduct);
            Vec3D intersectionPoint = line.point + line.direction * t;
            
            // Check if the intersection point is inside the face
            return intersects(intersectionPoint);
        }
        
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
        bool intersects(const Plane &plane) const {
            // Counters for vertices on each side of the plane
            int positive = 0, negative = 0;
            
            for (auto index : indices) {
                // Calculate the signed distance from the vertex to the plane
                double distance = plane.distanceToPoint(verticesRef[index]);
                
                // Count vertices on each side of the plane
                if (distance > 0) positive++;
                else if (distance < 0) negative++;
                
                // Early exit if vertices on both sides are found
                if (positive > 0 && negative > 0) return true;
            }
            
            // If function reaches this point, no intersection is found
            return false;
        }
        
    
    private:
        Direction calculateNormal() {
            Direction normal = Vec3D(0, 0, 0);
            for (size_t i = 0; i < indices.size(); ++i) {
                // Retrieve the current vertex using the index from 'indices'.
                const Vec3D &current = verticesRef[indices[i]];
                
                // Retrieve the next vertex in the sequence. If 'i' is the last index,
                // this will loop back to the first vertex using modulo operation.
                const Vec3D &next = verticesRef[indices[(i + 1) % indices.size()]];
                
                // Calculate the cross product of the current edge's vector and the vector
                // of the next edge. The cross product of two adjacent edge vectors gives
                // a vector perpendicular to the face's surface.
                // Accumulate these cross products to account for all edges of the face.
                normal += current.cross(next);
            }
            
            // Finally, normalize the accumulated normal to get the average normal.
            return normal.normalize();
        }
        
        /**
         * @brief The normal vector of the face.
         * @details The normal vector is typically calculated based on the vertices
         *          of the face and is perpendicular to the face's surface. It is
         *          used for various calculations such as lighting in graphics.
         */
        FaceIndices indices;
        mutable Plane plane;
        /**
         * @brief Const reference to the vertices of the polyhedron that contains this face.
         */
        const std::vector<Point> &verticesRef;
        
        
        
        // Other methods like area calculation, etc., can be added as needed.
    };
} // namespace GLESC::Math