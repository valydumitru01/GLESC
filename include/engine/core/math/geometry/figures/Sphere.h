/**************************************************************************************************
 * @file   Sphere.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/geometry/Figure.h"
#include "engine/core/math/geometry/Polyhedron.h"

namespace GLESC::Math {
    class Sphere : public Figure {
    public:
        /**
         * @brief Creates a sphere with the given center and radius
         * @param center The center of the sphere
         * @param radius The radius of the sphere
         */
        Sphere(Vec3D centerParam, float radiusParam) :
                center(std::move(centerParam)), radius(radiusParam) {}
        
        /**
         * @brief Checks if the sphere intersects with the given plane
         * @param plane The plane to check intersection with
         * @return True if the sphere intersects with the plane, false otherwise
         */
        [[nodiscard]] bool intersects(const Plane &plane) const override {
            return plane.distanceToPoint(center) <= radius;
        }
        
        
        /**
         * @brief Checks if the sphere intersects with the given face.
         * @param face The face to check intersection with.
         * @return True if the sphere intersects with the face, false otherwise.
         */
        [[nodiscard]] bool intersects(const Face &face) const override {
            std::vector<Vec3D> vertices = face.getPolyhedronVertices();
            
            // Check if any vertex of the face is inside the sphere.
            for (const auto &index : face.getVertexIndices()) {
                if (this->intersects(vertices[index])) {
                    return true;
                }
            }
            
            // Check for edge-sphere intersection.
            const auto& indices = face.getVertexIndices();
            for (size_t i = 0; i < indices.size(); ++i) {
                const Point& startPoint = vertices[indices[i]];
                const Point& endPoint = vertices[indices[(i + 1) % indices.size()]];
                if (intersects(startPoint, endPoint)) {
                    return true;
                }
            }
            
            return false;
        }
        
        /**
         * @brief Checks if the sphere intersects with the given figure
         * @param polyhedron The figure to check intersection with
         * @return True if the sphere intersects with the figure, false otherwise
         */
        [[nodiscard]] bool intersects(const Polyhedron &polyhedron) const override {
            for (const auto &face : polyhedron.getFaces()) {
                if (intersects(face)) {
                    return true;
                }
            }
        }
        
        /**
         * @brief Checks if the sphere intersects with the given point
         * @param point The point to check intersection with
         * @return True if the sphere intersects with the point, false otherwise
         */
        [[nodiscard]] bool intersects(const Point &point) const override {
            return (point - center).length() <= radius;
        }
        
        /**
         * @brief Checks if the sphere intersects with an edge defined by two points.
         * @param startPoint The start point of the edge.
         * @param endPoint The end point of the edge.
         * @return True if the sphere intersects with the edge, false otherwise.
         */
        [[nodiscard]] bool intersects(const Point &startPoint, const Point &endPoint) const {
            Vec3D edge = endPoint - startPoint;
            Vec3D startToCenter = center - startPoint;
            double edgeLengthSquared = edge.lengthSquared();
            double t = startToCenter.dot(edge) / edgeLengthSquared;
            t = std::max(0.0, std::min(1.0, t));  // Clamping t to be within [0, 1]
            Vec3D closestPoint = startPoint + edge * t;
            return (closestPoint - center).lengthSquared() <= radius * radius;
        }
    private:
        /**
         * @brief The center of the sphere
         */
        Vec3D center;
        /**
         * @brief The radius of the sphere
         */
        float radius;
    }; // class Sphere
} // namespace GLESC::Math