/**************************************************************************************************
 * @file   MeshFactory.cpp
 * @author Valentin Dumitru
 * @date   17/12/2023
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/mesh/MeshFactory.h"

using namespace GLESC::Render;

ColorMesh MeshFactory::cube(const ColorRgba& color, const Math::Distance& radius) {
    return cuboid(radius, radius, radius, color);
}

ColorMesh MeshFactory::sphere(const int numSlices, const int numStacks, const float radius, const ColorRgba& color) {
    ColorMesh mesh;
    mesh.startBuilding();

    constexpr auto piF = Math::pi<float>();
    // Create the top and bottom cap
    for (int i = 0; i < numSlices; ++i) {
        float theta1 = 2 * piF * static_cast<float>(i) / static_cast<float>(numSlices);
        float theta2 = 2 * piF * static_cast<float>(i + 1) / static_cast<float>(numSlices);
        const auto stacks = static_cast<float>(numStacks);

        Position topP1(Math::cos(theta2) * Math::sin(piF / stacks),
                       Math::cos(piF / stacks),
                       Math::sin(theta2) * Math::sin(piF / stacks));
        Position topP2(Math::cos(theta1) * Math::sin(piF / stacks),
                       Math::cos(piF / stacks),
                       Math::sin(theta1) * Math::sin(piF / stacks));

        Position bottomP1(Math::cos(theta2) * Math::sin(piF - piF / stacks),
                          Math::cos(piF - piF / stacks),
                          Math::sin(theta2) * Math::sin(piF - piF / stacks));
        Position bottomP2(Math::cos(theta1) * Math::sin(piF - piF / stacks),
                          Math::cos(piF - piF / stacks),
                          Math::sin(theta1) * Math::sin(piF - piF / stacks));
        // Top cap triangles
        mesh.addTris(
            {Position(0, radius, 0), color},
            {topP1 * radius, color},
            {topP2 * radius, color}
        );

        // Bottom cap triangles
        mesh.addTris(
            {Position(0, -radius, 0), color},
            {bottomP2 * radius, color},
            {bottomP1 * radius, color}
        );
    }

    // Create the middle quads
    for (int j = 1; j < numStacks - 1; ++j) {
        for (int i = 0; i < numSlices; ++i) {
            float theta1 = 2 * piF * static_cast<float>(i) / static_cast<float>(numSlices);
            float theta2 = 2 * piF * static_cast<float>(i + 1) / static_cast<float>(numSlices);
            float phi1 = piF * static_cast<float>(j) / static_cast<float>(numStacks);
            float phi2 = piF * static_cast<float>(j + 1) / static_cast<float>(numStacks);

            Position p1(Math::cos(theta1) * Math::sin(phi1), Math::cos(phi1), Math::sin(theta1) * Math::sin(phi1));
            Position p2(Math::cos(theta2) * Math::sin(phi1), Math::cos(phi1), Math::sin(theta2) * Math::sin(phi1));
            Position p3(Math::cos(theta2) * Math::sin(phi2), Math::cos(phi2), Math::sin(theta2) * Math::sin(phi2));
            Position p4(Math::cos(theta1) * Math::sin(phi2), Math::cos(phi2), Math::sin(theta1) * Math::sin(phi2));


            mesh.addQuad(
                {p1 * radius, color},
                {p2 * radius, color},
                {p3 * radius, color},
                {p4 * radius, color}
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
