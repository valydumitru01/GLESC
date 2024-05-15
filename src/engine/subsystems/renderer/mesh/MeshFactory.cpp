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

ColorMesh MeshFactory::cube(const ColorRgba &color, const Math::Distance& radius) {
    return cuboid(radius, radius, radius, color);
}

ColorMesh MeshFactory::sphere(int numSlices, int numStacks, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();

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
        // Top cap triangles
        mesh.addTris(
            {Position(0, 1, 0), color},
            {topP1, color},
            {topP2, color}
        );

        // Bottom cap triangles
        mesh.addTris(
            {Position(0, -1, 0), color},
            {bottomP2, color},
            {bottomP1, color}
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


            mesh.addQuad(
                {p1, color},
                {p2, color},
                {p3, color},
                {p4, color}
            );
        }
    }
    mesh.finishBuilding();
    return mesh;
}

ColorMesh MeshFactory::cuboid(const double width, const double height, const double depth, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();
    double w = width / 2.0, h = height / 2.0, d = depth / 2.0;

    mesh.addQuad({Position(-w, -h, -d), color},
                 {Position(w, -h, -d), color},
                 {Position(w, -h, d), color},
                 {Position(-w, -h, d), color});

    mesh.addQuad({Position(-w, h, -d), color},
                 {Position(-w, h, d), color},
                 {Position(w, h, d), color},
                 {Position(w, h, -d), color});

    mesh.addQuad({Position(-w, -h, d), color},
                 {Position(w, -h, d), color},
                 {Position(w, h, d), color},
                 {Position(-w, h, d), color});

    mesh.addQuad({Position(-w, -h, -d), color},
                 {Position(-w, h, -d), color},
                 {Position(w, h, -d), color},
                 {Position(w, -h, -d), color});

    mesh.addQuad({Position(-w, -h, -d), color},
                 {Position(-w, -h, d), color},
                 {Position(-w, h, d), color},
                 {Position(-w, h, -d), color});

    mesh.addQuad({Position(w, -h, -d), color},
                 {Position(w, h, -d), color},
                 {Position(w, h, d), color},
                 {Position(w, -h, d), color});
    mesh.finishBuilding();
    return mesh;
}

ColorMesh MeshFactory::pyramid(const double width, const double height, const double depth, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();

    double w = width / 2.0, h = height, d = depth / 2.0;

    // Base
    mesh.addQuad(
        {Position(-w, 0, -d), color},
        {Position(w, 0, -d), color},
        {Position(w, 0, d), color},
        {Position(-w, 0, d), color}
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
        mesh.addTris(
            {top, color},
            {corners[i], color},
            {corners[(i + 1) % 4], color}
        );
    }
    mesh.finishBuilding();
    return mesh;
}


ColorMesh MeshFactory::tris(const ColorRgba& color) {
    ColorMesh mesh;
    mesh.addTris(
        {Position(0, 1, 0), color},
        {Position(1, -1, 0), color},
        {Position(-1, -1, 0), color}
    );
    mesh.finishBuilding();
    return mesh;
}

ColorMesh MeshFactory::plane(const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();
    mesh.addQuad(
        {Position(-1, -1, 0), color},
        {Position(1, -1, 0), color},
        {Position(1, 1, 0), color},
        {Position(-1, 1, 0), color}
    );
    mesh.finishBuilding();
    return mesh;
}


