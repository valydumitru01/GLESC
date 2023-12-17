/**************************************************************************************************
 * @file   PolygonFactory.h
 * @author Valentin Dumitru
 * @date   15/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "Polyhedron.h"

namespace PolyhedronFactory {
    namespace Polygons {
        static GLESC::Math::Polyhedron createCube(double radius) {
            GLESC::Math::Polyhedron cube;
            cube.addVertex({-radius, -radius, -radius});
            cube.addVertex({radius, -radius, -radius});
            cube.addVertex({radius, radius, -radius});
            cube.addVertex({-radius, radius, -radius});
            cube.addVertex({-radius, -radius, radius});
            cube.addVertex({radius, -radius, radius});
            cube.addVertex({radius, radius, radius});
            cube.addVertex({-radius, radius, radius});
            cube.addFace({0, 1, 2, 3});
            cube.addFace({4, 5, 6, 7});
            cube.addFace({0, 1, 5, 4});
            cube.addFace({2, 3, 7, 6});
            cube.addFace({0, 3, 7, 4});
            cube.addFace({1, 2, 6, 5});
            return cube;
        }
        
        static GLESC::Math::Polyhedron
        createPrism(double radius, double height, unsigned int sides) {
            GLESC::Math::Polyhedron prism;
            double angle = 2 * GLESC::Math::pi<double>() / sides;
            for (unsigned int i = 0; i < sides; i++) {
                prism.addVertex({radius * cos(angle * i), radius * sin(angle * i), height / 2});
                prism.addVertex({radius * cos(angle * i), radius * sin(angle * i), -height / 2});
            }
            for (unsigned int i = 0; i < sides; i++) {
                prism.addFace(
                        {2 * i, 2 * i + 1, (2 * i + 3) % (2 * sides), (2 * i + 2) % (2 * sides)});
                prism.addFace({2 * i, 2 * i + 1, 2 * i + 3, 2 * i + 2});
            }
            return prism;
        }
        
        static GLESC::Math::Polyhedron createTetrahedron(double radius) {
            GLESC::Math::Polyhedron tetrahedron;
            tetrahedron.addVertex({radius, radius, radius});
            tetrahedron.addVertex({-radius, -radius, radius});
            tetrahedron.addVertex({-radius, radius, -radius});
            tetrahedron.addVertex({radius, -radius, -radius});
            tetrahedron.addFace({0, 1, 2});
            tetrahedron.addFace({0, 1, 3});
            tetrahedron.addFace({0, 2, 3});
            tetrahedron.addFace({1, 2, 3});
            return tetrahedron;
        }
        
        static GLESC::Math::Polyhedron createOctahedron(double radius) {
            GLESC::Math::Polyhedron octahedron;
            octahedron.addVertex({0, 0, radius});
            octahedron.addVertex({0, 0, -radius});
            octahedron.addVertex({radius, 0, 0});
            octahedron.addVertex({-radius, 0, 0});
            octahedron.addVertex({0, radius, 0});
            octahedron.addVertex({0, -radius, 0});
            octahedron.addFace({0, 2, 4});
            octahedron.addFace({0, 2, 5});
            octahedron.addFace({0, 3, 4});
            octahedron.addFace({0, 3, 5});
            octahedron.addFace({1, 2, 4});
            octahedron.addFace({1, 2, 5});
            octahedron.addFace({1, 3, 4});
            octahedron.addFace({1, 3, 5});
            return octahedron;
        }
    }; // class Polygon
}; // class PolygonFactory
