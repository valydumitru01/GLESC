#include "engine/core/math/geometry/figures/polyhedron/PolyhedronFace.h"

using namespace GLESC::Math;



PolyhedronFace::PolyhedronFace(FaceIndices indicesParam, const Points &verticesParam) :
        indices(indicesParam), polyhedronVertices(verticesParam) {
    D_ASSERT_TRUE(polyhedronVertices.size() >= 3, "Polyhedron must have at least 3 vertices.");
    D_ASSERT_FALSE(polyhedronVertices.at(indices[0]).isCollinear({polyhedronVertices.at(indices[1]),
        polyhedronVertices.at(indices[2])}),
                  "Face must not have collinear vertices.");

    // Construct the plane that contains this face with the 3 points constructor
    plane = Plane(polyhedronVertices.at(0), polyhedronVertices.at(1), polyhedronVertices.at(2));
}


[[nodiscard]] bool PolyhedronFace::intersects(const PolyhedronFace &face) const {
    D_ASSERT_FALSE(polyhedronVertices.empty(), "Polyhedron vertices must not be empty.");
    // Get normals of both faces
    const Direction& thisNormal = getNormal();
    const Direction& otherNormal = face.getNormal();

    // Vector to store all axes to test
    std::vector<Direction> axes;

    // Add face normals to axes (to handle face-face parallel cases)
    axes.push_back(thisNormal);
    axes.push_back(otherNormal);

    // Function to add unique axes from edge cross products
    auto addUniqueAxis = [&axes](const Direction &edgeNormal) {
        // Normalize the edge normal
        Direction normalized = edgeNormal.normalize();
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
        Direction edge = polyhedronVertices.at(next) - polyhedronVertices.at(i);
        addUniqueAxis(thisNormal.cross(edge));
    }

    // Generate axes from edges of other face
    for (size_t i = 0; i < face.indices.size(); ++i) {
        size_t next = (i + 1) % face.indices.size();
        Direction edge = face.polyhedronVertices.at(next) - face.polyhedronVertices.at(i);
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
            double projection = polyhedronVertices.at(index).dot(axis);
            thisMin = min(thisMin, projection);
            thisMax = max(thisMax, projection);
        }
        for (auto index : face.indices) {
            double projection = face.polyhedronVertices.at(index).dot(axis);
            otherMin = min(otherMin, projection);
            otherMax = max(otherMax, projection);
        }

        // Check for separation on this axis
        if (thisMax < otherMin || otherMax < thisMin) {
            return false; // No overlap, faces do not intersect
        }
    }

    return true; // Overlap on all axes, faces intersect
}


bool PolyhedronFace::intersects(const Point &point) const {
    D_ASSERT_FALSE(polyhedronVertices.empty(), "Polyhedron vertices must not be empty.");
    for (size_t i = 0; i < polyhedronVertices.size(); ++i) {
        Direction edge = polyhedronVertices.at((i + 1) % polyhedronVertices.size()) - polyhedronVertices.at(i);
        Direction toPoint = point - polyhedronVertices.at(i);
        if (getNormal().cross(edge).dot(toPoint) < 0) {
            return false; // Point is outside this edge
        }
    }
    return true; // Point is inside all edges
}

bool PolyhedronFace::intersects(const Line &line) const {
    D_ASSERT_FALSE(polyhedronVertices.empty(), "Polyhedron vertices must not be empty.");
    // Check if the line is parallel to the plane
    Distance dotProduct = getNormal().dot(line.getDirection());
    if (Math::eq(Math::abs(dotProduct),0)) {
        return false; // Line is parallel to the plane, no intersection
    }

    // Find the intersection point with the plane
    float t = -(getNormal().dot(line.getPoint() - polyhedronVertices.at(0)) + plane.getDistance() / dotProduct);
    Direction intersectionPoint = line.getPoint() + line.getDirection() * t;

    // Check if the intersection point is inside the face
    return intersects(intersectionPoint);
}

bool PolyhedronFace::intersects(const Plane &planeParam) const {
    D_ASSERT_FALSE(polyhedronVertices.empty(), "Polyhedron vertices must not be empty.");
    // Counters for vertices on each side of the plane and on the plane
    int positive = 0, negative = 0, onPlane = 0;

    for (auto index : indices) {
        // Calculate the signed distance from the vertex to the plane
        Distance distance = planeParam.distanceToPoint(polyhedronVertices.at(index));

        const Distance intersectsEpsilon = 0.0001;

        // Count vertices on each side of the plane and on the plane
        if(eq(distance, 0, intersectsEpsilon)) onPlane++;
        else if (distance > 0) positive++;
        else if (distance < 0) negative++;


        // Check for early exit conditions
        if (positive > 0 && negative > 0) return true; // Vertices on both sides
        if (onPlane > 0 && (positive > 0 || negative > 0)) return true; // An edge or vertex on the plane
    }

    // Check if any edge lies entirely on the plane
    if (onPlane >= 2) return true;

    // No intersection found
    return false;
}


