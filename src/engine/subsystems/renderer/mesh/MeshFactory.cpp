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

ColorMesh MeshFactory::cube(const ColorRgba& color) {
    return cuboid(1, 1, 1, color);
}

ColorMesh MeshFactory::sphere(int numSlices, int numStacks, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();
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
            ColorMesh::Vertex(Position(0, 1, 0), topTrisNormal, color),
            ColorMesh::Vertex(topP1, topTrisNormal, color),
            ColorMesh::Vertex(topP2, topTrisNormal, color)
        );

        Normal bottomTrisNormal = (Normal(0, -1, 0) + bottomP1.normalize() + bottomP2.normalize()) / 3.0f;

        // Bottom cap triangles
        mesh.addTris(
            ColorMesh::Vertex(Position(0, -1, 0), bottomTrisNormal, color),
            ColorMesh::Vertex(bottomP2, bottomTrisNormal, color),
            ColorMesh::Vertex(bottomP1, bottomTrisNormal, color)
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
                ColorMesh::Vertex(p1, faceNormal, color),
                ColorMesh::Vertex(p2, faceNormal, color),
                ColorMesh::Vertex(p3, faceNormal, color),
                ColorMesh::Vertex(p4, faceNormal, color)
            );
        }
    }
    mesh.finishBuilding();
    return mesh;
}

ColorMesh MeshFactory::cuboid(const double width, const double height, const double depth, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();
    Color rgba = color.getRGBAVec4FNormalized();

    double w = width / 2.0, h = height / 2.0, d = depth / 2.0;

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, -d), Normal(0, -1, 0), color),
                 ColorMesh::Vertex(Position(w, -h, -d), Normal(0, -1, 0), color),
                 ColorMesh::Vertex(Position(w, -h, d), Normal(0, -1, 0), color),
                 ColorMesh::Vertex(Position(-w, -h, d), Normal(0, -1, 0), color));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, h, -d), Normal(0, 1, 0), color),
                 ColorMesh::Vertex(Position(-w, h, d), Normal(0, 1, 0), color),
                 ColorMesh::Vertex(Position(w, h, d), Normal(0, 1, 0), color),
                 ColorMesh::Vertex(Position(w, h, -d), Normal(0, 1, 0), color));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, d), Normal(0, 0, 1), color),
                 ColorMesh::Vertex(Position(w, -h, d), Normal(0, 0, 1), color),
                 ColorMesh::Vertex(Position(w, h, d), Normal(0, 0, 1), color),
                 ColorMesh::Vertex(Position(-w, h, d), Normal(0, 0, 1), color));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, -d), Normal(0, 0, -1), color),
                 ColorMesh::Vertex(Position(-w, h, -d), Normal(0, 0, -1), color),
                 ColorMesh::Vertex(Position(w, h, -d), Normal(0, 0, -1), color),
                 ColorMesh::Vertex(Position(w, -h, -d), Normal(0, 0, -1), color));

    mesh.addQuad(ColorMesh::Vertex(Position(-w, -h, -d), Normal(-1, 0, 0), color),
                 ColorMesh::Vertex(Position(-w, -h, d), Normal(-1, 0, 0), color),
                 ColorMesh::Vertex(Position(-w, h, d), Normal(-1, 0, 0), color),
                 ColorMesh::Vertex(Position(-w, h, -d), Normal(-1, 0, 0), color));

    mesh.addQuad(ColorMesh::Vertex(Position(w, -h, -d), Normal(1, 0, 0), color),
                 ColorMesh::Vertex(Position(w, h, -d), Normal(1, 0, 0), color),
                 ColorMesh::Vertex(Position(w, h, d), Normal(1, 0, 0), color),
                 ColorMesh::Vertex(Position(w, -h, d), Normal(1, 0, 0), color));
    mesh.finishBuilding();
    return mesh;
}

ColorMesh MeshFactory::pyramid(const double width, const double height, const double depth, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();

    double w = width / 2.0, h = height, d = depth / 2.0;

    // Base
    mesh.addQuad(
        ColorMesh::Vertex(Position(-w, 0, -d), Normal(0, -1, 0), color),
        ColorMesh::Vertex(Position(w, 0, -d), Normal(0, -1, 0), color),
        ColorMesh::Vertex(Position(w, 0, d), Normal(0, -1, 0), color),
        ColorMesh::Vertex(Position(-w, 0, d), Normal(0, -1, 0), color)
    );

    // Sides
    Position top(0, h, 0);
    Position corners[4] = {
        Position(-w, 0, -d),
        Position(w, 0, -d),
        Position(w, 0, d),
        Position(-w, 0, d)
    };

    for (int i = 0; i < 4; ++i) {
        Normal normal = (corners[(i + 1) % 4] - top).cross(corners[i] - top).normalize();
        mesh.addTris(
            ColorMesh::Vertex(top, normal, color),
            ColorMesh::Vertex(corners[i], normal, color),
            ColorMesh::Vertex(corners[(i + 1) % 4], normal, color)
        );
    }
    mesh.finishBuilding();
    return mesh;
}


ColorMesh MeshFactory::tris(const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();
    mesh.addTris(
        ColorMesh::Vertex(Position(0, 1, 0), Normal(0, 1, 0), color),
        ColorMesh::Vertex(Position(1, -1, 0), Normal(1, -1, 0), color),
        ColorMesh::Vertex(Position(-1, -1, 0), Normal(-1, -1, 0), color)
    );
    mesh.finishBuilding();
    return mesh;
}

ColorMesh MeshFactory::plane(const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();
    Color rgba = color.getRGBAVec4FNormalized();
    mesh.addQuad(
        ColorMesh::Vertex(Position(-1, -1, 0), Normal(0, 0, 1), color),
        ColorMesh::Vertex(Position(1, -1, 0), Normal(0, 0, 1), color),
        ColorMesh::Vertex(Position(1, 1, 0), Normal(0, 0, 1), color),
        ColorMesh::Vertex(Position(-1, 1, 0), Normal(0, 0, 1), color)
    );
    mesh.finishBuilding();
    return mesh;
}
