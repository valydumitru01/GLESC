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

ColorMesh MeshFactory::cube(const ColorRgba &color) {
    return cuboid(1, 1, 1, color);
}

ColorMesh MeshFactory::sphere(int numSlices, int numStacks, const ColorRgba &color) {
    ColorMesh mesh;
    Color rgba = color.getRGBAVec4FNormalized();

    auto pi_f = Math::pi<float>();
    // Create the top and bottom cap
    for (int i = 0; i < numSlices; ++i) {
        float theta1 = 2 * pi_f * float(i) / float(numSlices);
        float theta2 = 2 * pi_f * float(i + 1) / float(numSlices);
        auto stacks = static_cast<float>(numStacks);

        Position topP1(Math::cos(theta2) * Math::sin(pi_f / stacks),
                       Math::cos(pi_f / stacks),
                       Math::sin(theta2) * Math::sin(pi_f / stacks));
        Position topP2(Math::cos(theta1) * Math::sin(pi_f / stacks),
                       Math::cos(pi_f / stacks),
                       Math::sin(theta1) * Math::sin(pi_f / stacks));

        Position bottomP1(Math::cos(theta2) * Math::sin(pi_f - pi_f / stacks),
                          Math::cos(pi_f - pi_f / stacks),
                          Math::sin(theta2) * Math::sin(pi_f - pi_f / stacks));
        Position bottomP2(Math::cos(theta1) * Math::sin(pi_f - pi_f / stacks),
                          Math::cos(pi_f - pi_f / stacks),
                          Math::sin(theta1) * Math::sin(pi_f - pi_f / stacks));

        Normal topTrisNormal = (Normal(0, 1, 0) + topP1.normalize() + topP2.normalize()) / 3.0f;
        // Top cap triangles
        mesh.addTris(
            ColorMesh::Vertex(Position(0, 1, 0), rgba, topTrisNormal),
            ColorMesh::Vertex(topP1, rgba, topTrisNormal),
            ColorMesh::Vertex(topP2, rgba, topTrisNormal)
        );

        Normal bottomTrisNormal = (Normal(0, -1, 0) + bottomP1.normalize() + bottomP2.normalize()) / 3.0f;

        // Bottom cap triangles
        mesh.addTris(
            ColorMesh::Vertex(Position(0, -1, 0), rgba, bottomTrisNormal),
            ColorMesh::Vertex(bottomP2, rgba, bottomTrisNormal),
            ColorMesh::Vertex(bottomP1, rgba, bottomTrisNormal)
        );
    }

    // Create the middle quads
    for (int j = 1; j < numStacks - 1; ++j) {
        for (int i = 0; i < numSlices; ++i) {
            float theta1 = 2 * pi_f * float(i) / float(numSlices);
            float theta2 = 2 * pi_f * float(i + 1) / float(numSlices);
            float phi1 = pi_f * float(j) / float(numStacks);
            float phi2 = pi_f * float(j + 1) / float(numStacks);

            Position p1(Math::cos(theta1) * Math::sin(phi1), Math::cos(phi1), Math::sin(theta1) * Math::sin(phi1));
            Position p2(Math::cos(theta2) * Math::sin(phi1), Math::cos(phi1), Math::sin(theta2) * Math::sin(phi1));
            Position p3(Math::cos(theta2) * Math::sin(phi2), Math::cos(phi2), Math::sin(theta2) * Math::sin(phi2));
            Position p4(Math::cos(theta1) * Math::sin(phi2), Math::cos(phi2), Math::sin(theta1) * Math::sin(phi2));

            Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;

            mesh.addQuad(
                ColorMesh::Vertex(p1, rgba, faceNormal),
                ColorMesh::Vertex(p2, rgba, faceNormal),
                ColorMesh::Vertex(p3, rgba, faceNormal),
                ColorMesh::Vertex(p4, rgba, faceNormal)
            );
        }
    }

    return mesh;
}

ColorMesh MeshFactory::cuboid(const double width, const double height, const double depth, const ColorRgba &color) {
    ColorMesh mesh;
    Color rgba = color.getRGBAVec4FNormalized();

    double w = width / 2.0, h = height / 2.0, d = depth / 2.0;

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, -d), rgba, Normal(0, -1, 0)),
                 ColorMesh::Vertex(Position(w, -h, -d), rgba, Normal(0, -1, 0)),
                 ColorMesh::Vertex(Position(w, -h, d), rgba, Normal(0, -1, 0)),
                 ColorMesh::Vertex(Position(-w, -h, d), rgba, Normal(0, -1, 0)));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, h, -d), rgba, Normal(0, 1, 0)),
                 ColorMesh::Vertex(Position(-w, h, d), rgba, Normal(0, 1, 0)),
                 ColorMesh::Vertex(Position(w, h, d), rgba, Normal(0, 1, 0)),
                 ColorMesh::Vertex(Position(w, h, -d), rgba, Normal(0, 1, 0)));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, d), rgba, Normal(0, 0, 1)),
                 ColorMesh::Vertex(Position(w, -h, d), rgba, Normal(0, 0, 1)),
                 ColorMesh::Vertex(Position(w, h, d), rgba, Normal(0, 0, 1)),
                 ColorMesh::Vertex(Position(-w, h, d), rgba, Normal(0, 0, 1)));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, -d), rgba, Normal(0, 0, -1)),
                 ColorMesh::Vertex(Position(-w, h, -d), rgba, Normal(0, 0, -1)),
                 ColorMesh::Vertex(Position(w, h, -d), rgba, Normal(0, 0, -1)),
                 ColorMesh::Vertex(Position(w, -h, -d), rgba, Normal(0, 0, -1)));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, -d), rgba, Normal(-1, 0, 0)),
                 ColorMesh::Vertex(Position(-w, -h, d), rgba, Normal(-1, 0, 0)),
                 ColorMesh::Vertex(Position(-w, h, d), rgba, Normal(-1, 0, 0)),
                 ColorMesh::Vertex(Position(-w, h, -d), rgba, Normal(-1, 0, 0)));

    mesh.addQuad(ColorMesh::Vertex(Position(w, -h, -d), rgba, Normal(1, 0, 0)),
                 ColorMesh::Vertex(Position(w, h, -d), rgba, Normal(1, 0, 0)),
                 ColorMesh::Vertex(Position(w, h, d), rgba, Normal(1, 0, 0)),
                 ColorMesh::Vertex(Position(w, -h, d), rgba, Normal(1, 0, 0)));

    return mesh;
}

ColorMesh MeshFactory::pyramid(const double width, const double height, const double depth, const ColorRgba &color) {
}


ColorMesh MeshFactory::tris(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const ColorRgba &color) {
}

ColorMesh MeshFactory::quad(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Vec3D &v4, const ColorRgba &color) {
}
