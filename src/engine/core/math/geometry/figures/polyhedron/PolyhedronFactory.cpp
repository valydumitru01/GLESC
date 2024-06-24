/**************************************************************************************************
 * @file   PolyhedronFactory.cpp
 * @author Valentin Dumitru
 * @date   2023-12-25
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <algorithm>
#include "engine/core/math/geometry/PolyhedronFactory.h"


using namespace GLESC::Math;

namespace GLESC::PolyhedronFactory::Regular {
    Polyhedron tetra() {
        Polyhedron tetrahedron;
        double sqrt2_3 = sqrt(2.0 / 3.0);
        double sqrt3_3 = sqrt(1.0 / 3.0);
        double sqrt6_3 = sqrt(2.0 / 9.0);

        // Vertices
        tetrahedron.addVertex(Point{0, 0, sqrt2_3});
        tetrahedron.addVertex(Point{2.0 / 3.0 * sqrt3_3, 0, -1 * sqrt6_3});
        tetrahedron.addVertex(Point{-sqrt3_3 / 3.0, 1 / sqrt3_3, -1 * sqrt6_3});
        tetrahedron.addVertex(Point{-sqrt3_3 / 3.0, -1 / sqrt3_3, -1 * sqrt6_3});

        // Faces
        tetrahedron.addFace({0, 1, 2});
        tetrahedron.addFace({0, 1, 3});
        tetrahedron.addFace({0, 2, 3});
        tetrahedron.addFace({1, 2, 3});
        return tetrahedron;
    }

    Polyhedron cube() {
        return Common::rectangularCuboid(1, 1, 1);
    }

    Polyhedron octa() {
        Polyhedron octahedron;

        // Vertices
        octahedron.addVertex(Point{0, 0, 1});
        octahedron.addVertex(Point{0, 0, -1});
        octahedron.addVertex(Point{1, 0, 0});
        octahedron.addVertex(Point{-1, 0, 0});
        octahedron.addVertex(Point{0, 1, 0});
        octahedron.addVertex(Point{0, -1, 0});

        // Faces
        octahedron.addFace({0, 2, 4});
        octahedron.addFace({0, 4, 3});
        octahedron.addFace({0, 3, 5});
        octahedron.addFace({0, 5, 2});
        octahedron.addFace({1, 2, 5});
        octahedron.addFace({1, 5, 3});
        octahedron.addFace({1, 3, 4});
        octahedron.addFace({1, 4, 2});
        return octahedron;
    }

    Polyhedron dodeca() {
        Polyhedron dodecahedron;
        [[maybe_unused]] double phi = (1.0 + sqrt(5.0)) / 2.0;

        return dodecahedron;
    }

    Polyhedron icos() {
        Polyhedron icosahedron;
        double phi = (1.0 + sqrt(5.0)) / 2.0;
        icosahedron.addVertex(Point{0, 1, phi});
        icosahedron.addVertex(Point{0, 1, -phi});
        icosahedron.addVertex(Point{0, -1, phi});
        icosahedron.addVertex(Point{0, -1, -phi});
        icosahedron.addVertex(Point{1, phi, 0});
        icosahedron.addVertex(Point{1, -phi, 0});
        icosahedron.addVertex(Point{-1, phi, 0});
        icosahedron.addVertex(Point{-1, -phi, 0});
        icosahedron.addVertex(Point{phi, 0, 1});
        icosahedron.addVertex(Point{phi, 0, -1});
        icosahedron.addVertex(Point{-phi, 0, 1});
        icosahedron.addVertex(Point{-phi, 0, -1});

        icosahedron.addFace({0, 4, 8});
        icosahedron.addFace({0, 4, 10});
        icosahedron.addFace({0, 5, 11});
        icosahedron.addFace({0, 5, 9});
        icosahedron.addFace({1, 6, 8});
        icosahedron.addFace({1, 6, 10});
        icosahedron.addFace({1, 7, 9});
        icosahedron.addFace({1, 7, 11});
        icosahedron.addFace({2, 4, 8});
        icosahedron.addFace({2, 4, 10});
        icosahedron.addFace({2, 5, 9});
        icosahedron.addFace({2, 5, 11});
        icosahedron.addFace({3, 6, 8});
        icosahedron.addFace({3, 6, 10});
        icosahedron.addFace({3, 7, 9});
        icosahedron.addFace({3, 7, 11});
        icosahedron.addFace({4, 8, 10});
        icosahedron.addFace({5, 9, 11});
        icosahedron.addFace({6, 8, 10});
        icosahedron.addFace({7, 9, 11});
        return icosahedron;
    }
}

namespace GLESC::PolyhedronFactory::Common {
    Polyhedron pyramid([[maybe_unused]] double radius, [[maybe_unused]] double height,
                       [[maybe_unused]] unsigned int baseSides) {
        Polyhedron pyramid;
        return pyramid;
    }

    Polyhedron rectangularCuboid(double width, double height, double depth) {
        Polyhedron cuboid;
        // Front and back face vertices
        cuboid.addVertex(Point{-width / 2, -height / 2, depth / 2}); // 0
        cuboid.addVertex(Point{width / 2, -height / 2, depth / 2}); // 1
        cuboid.addVertex(Point{width / 2, height / 2, depth / 2}); // 2
        cuboid.addVertex(Point{-width / 2, height / 2, depth / 2}); // 3
        cuboid.addVertex(Point{-width / 2, -height / 2, -depth / 2}); // 4
        cuboid.addVertex(Point{width / 2, -height / 2, -depth / 2}); // 5
        cuboid.addVertex(Point{width / 2, height / 2, -depth / 2}); // 6
        cuboid.addVertex(Point{-width / 2, height / 2, -depth / 2}); // 7
        // Faces

        return cuboid;
    }

    Polyhedron prism([[maybe_unused]] double radius, [[maybe_unused]] double height, unsigned int sides) {
        Polyhedron prism;
        [[maybe_unused]] double angle = 2.0 * pi<double>() / sides;
        return prism;
    }

    Polyhedron icosphere([[maybe_unused]] int subdivisions) {
        Polyhedron sphere;
        return sphere;
    }
}
