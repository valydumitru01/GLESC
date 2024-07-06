#include "engine/core/math/geometry/figures/sphere/Sphere.h"

using namespace GLESC::Math;

Sphere::Sphere(Point centerParam, Distance radiusParam) :
        center(std::move(centerParam)), radius(radiusParam) {}


bool Sphere::intersects(const Plane &plane) const {
    return plane.distanceToPoint(center) <= radius;
}


bool Sphere::intersects(const PolyhedronFace &face) const {
    std::vector<Point> vertices = face.getPolyhedronVertices();
    
    // Check if any vertex of the face is inside the sphere.
    for (const auto &index : face.getVertexIndices()) {
        if (this->intersects(vertices[index])) {
            return true;
        }
    }
    
    // Check for edge-sphere intersection.
    const auto &indices = face.getVertexIndices();
    for (size_t i = 0; i < indices.size(); ++i) {
        const Point &startPoint = vertices[indices[i]];
        const Point &endPoint = vertices[indices[(i + 1) % indices.size()]];
        if (intersects(startPoint, endPoint)) {
            return true;
        }
    }
    
    return false;
}

bool Sphere::intersects(const Line& line) const {
    // Find the vector from the line's point to the sphere's center
    Point centerToLine = center - line.getPoint();
    
    // Project this vector onto the line's direction
    Direction projection = centerToLine.project(line.getDirection());
    
    // Find the closest point on the line to the sphere's center
    Point closestPoint = line.getPoint() + projection;
    
    // Check if the closest point is inside the sphere
    return intersects(closestPoint);
}

bool Sphere::intersects(const Polyhedron &polyhedron) const {
    for (const auto &face : polyhedron.getFaces()) {
        if (intersects(face)) {
            return true;
        }
    }
    return false;
}


bool Sphere::intersects(const Point &point) const {
    return (point - center).length() <= radius;
}


bool Sphere::intersects(const Point &startPoint, const Point &endPoint) const {
    Direction edge = endPoint - startPoint;
    Direction startToCenter = center - startPoint;
    Distance edgeLengthSquared = edge.lengthSquared();
    Distance t = startToCenter.dot(edge) / edgeLengthSquared;
    // Clamping t to be within [0, 1]
    t = clamp(t, 0, 1);
    Point closestPoint = startPoint + edge * t;
    return (closestPoint - center).lengthSquared() <= radius * radius;
}