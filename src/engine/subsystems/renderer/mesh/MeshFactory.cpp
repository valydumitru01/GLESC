/**************************************************************************************************
 * @file   MeshFactory.cpp
 * @author Valentin Dumitru
 * @date   17/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/mesh/MeshFactory.h"

using namespace GLESC::Render;

ColorMesh MeshFactory::cube(const Rgba &color) {
    return cuboid(1, 1, 1, color);
}

ColorMesh MeshFactory::sphere(int longitudeSubdivisions, int latitudeSubdivisions, const Rgba &color) {
    ColorMesh mesh;
    Color rgba = color.getRGBAVec4FNormalized();

    for (int latitude = 0; latitude <= latitudeSubdivisions; ++latitude) {
        auto lat = static_cast<float>(latitude);
        float theta = lat * Math::pi<float>() / static_cast<float>(latitudeSubdivisions);
        float sinTheta = Math::sin(theta);
        float cosTheta = Math::cos(theta);

        for (int longitude = 0; longitude <= longitudeSubdivisions; ++longitude) {
            auto lon = static_cast<float>(longitude);
            float phi = lon * 2 * Math::pi<float>() / static_cast<float>(latitudeSubdivisions);
            float sinPhi = Math::sin(phi);
            float cosPhi = Math::cos(phi);

            Position pos;
            Normal normal;
            normal.x() = pos.x() = cosPhi * sinTheta;
            normal.y() = pos.y() = cosTheta;
            normal.z() = pos.z() = sinPhi * sinTheta;

            // Normalize normal
            normal = normal.normalize();

            mesh.addVertex(ColorMesh::Vertex(pos, rgba, normal));
        }

    }
    // Generate the indices for the sphere's triangles
    for (int lat = 0; lat <= latitudeSubdivisions; ++lat) {
        for (int lon = 0; lon <= longitudeSubdivisions; ++lon) {
            int first = (lat * (longitudeSubdivisions + 1)) + lon;
            int second = first + longitudeSubdivisions + 1;
            first %= static_cast<int>(mesh.getVertices().size()-1);
            second %= static_cast<int>(mesh.getVertices().size()-1);

            mesh.addFace(first, second, first + 1);
            mesh.addFace(second, second + 1, first + 1);
        }
    }

    return mesh;
}

ColorMesh MeshFactory::cuboid(const double width, const double height, const double depth, const Rgba &color) {
    ColorMesh mesh;
    Color rgba = color.getRGBAVec4FNormalized();

    double w = width / 2.0, h = height / 2.0, d = depth / 2.0;
    ColorMesh::Vertex v1(Position(-w, -h, -d), rgba, Normal(0, 0, -1));
    ColorMesh::Vertex v2(Position(w, -h, -d), rgba, Normal(0, 0, -1));
    ColorMesh::Vertex v3(Position(w, h, -d), rgba, Normal(0, 0, -1));
    ColorMesh::Vertex v4(Position(-w, h, -d), rgba, Normal(0, 0, -1));

    ColorMesh::Vertex v5(Position(-w, -h, d), rgba, Normal(0, 0, 1));
    ColorMesh::Vertex v6(Position(w, -h, d), rgba, Normal(0, 0, 1));
    ColorMesh::Vertex v7(Position(w, h, d), rgba, Normal(0, 0, 1));
    ColorMesh::Vertex v8(Position(-w, h, d), rgba, Normal(0, 0, 1));

    mesh.addTris(v1, v2, v3);
    mesh.addTris(v3, v4, v1);
    // Back face
    mesh.addTris(v6, v5, v8);
    mesh.addTris(v8, v7, v6);
    // Right face
    mesh.addTris(v2, v6, v7);
    mesh.addTris(v7, v3, v2);
    // Left face
    mesh.addTris(v5, v1, v4);
    mesh.addTris(v4, v8, v5);
    // Top face
    mesh.addTris(v4, v3, v7);
    mesh.addTris(v7, v8, v4);
    // Bottom face
    mesh.addTris(v5, v6, v2);
    mesh.addTris(v2, v1, v5);

    return mesh;
}

ColorMesh MeshFactory::pyramid(const double width, const double height, const double depth, const Rgba &color) {
}


ColorMesh MeshFactory::tris(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Rgba &color) {
}

ColorMesh MeshFactory::quad(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Vec3D &v4, const Rgba &color) {
}
