/**************************************************************************************************
 * @file   PolyhedronFactory.cpp
 * @author Valentin Dumitru
 * @date   2023-12-25
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <algorithm>
#include "engine/core/math/geometry/PolyhedronFactory.h"


using namespace GLESC::Math;
namespace PolyhedronFactory::Regular {
    Polyhedron tetra() {
        GLESC::Math::Polyhedron tetrahedron;
        double sqrt2_3 = sqrt(2.0 / 3.0);
        double sqrt3_3 = sqrt(1.0 / 3.0);
        double sqrt6_3 = sqrt(2.0 / 9.0);
        
        // Vertices
        tetrahedron.addVertex({0, 0, sqrt2_3});
        tetrahedron.addVertex({2.0 / 3.0 * sqrt3_3, 0, -1 * sqrt6_3});
        tetrahedron.addVertex({-sqrt3_3 / 3.0, 1 / sqrt3_3, -1 * sqrt6_3});
        tetrahedron.addVertex({-sqrt3_3 / 3.0, -1 / sqrt3_3, -1 * sqrt6_3});
        
        // Faces
        tetrahedron.addFace({0, 1, 2});
        tetrahedron.addFace({0, 1, 3});
        tetrahedron.addFace({0, 2, 3});
        tetrahedron.addFace({1, 2, 3});
        return tetrahedron;
    }
    
    Polyhedron cube() {
        return PolyhedronFactory::Common::rectangularCuboid(1, 1, 1);
    }
    
    Polyhedron octa() {
        GLESC::Math::Polyhedron octahedron;
        
        // Vertices
        octahedron.addVertex({0, 0, 1});
        octahedron.addVertex({0, 0, -1});
        octahedron.addVertex({1, 0, 0});
        octahedron.addVertex({-1, 0, 0});
        octahedron.addVertex({0, 1, 0});
        octahedron.addVertex({0, -1, 0});
        
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
        GLESC::Math::Polyhedron dodecahedron;
        double phi = (1 + sqrt(5)) / 2;

        return dodecahedron;
    }
    
    Polyhedron icos() {
        GLESC::Math::Polyhedron icosahedron;
        double phi = (1 + sqrt(5)) / 2;
        icosahedron.addVertex({0, 1, phi});
        icosahedron.addVertex({0, 1, -phi});
        icosahedron.addVertex({0, -1, phi});
        icosahedron.addVertex({0, -1, -phi});
        icosahedron.addVertex({1, phi, 0});
        icosahedron.addVertex({1, -phi, 0});
        icosahedron.addVertex({-1, phi, 0});
        icosahedron.addVertex({-1, -phi, 0});
        icosahedron.addVertex({phi, 0, 1});
        icosahedron.addVertex({phi, 0, -1});
        icosahedron.addVertex({-phi, 0, 1});
        icosahedron.addVertex({-phi, 0, -1});
        
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
namespace PolyhedronFactory::Common {
    Polyhedron pyramid(double radius, double height, unsigned int baseSides) {
        GLESC::Math::Polyhedron pyramid;
        return pyramid;
    }
    
    Polyhedron rectangularCuboid(double width, double height, double depth) {
        GLESC::Math::Polyhedron cuboid;
        // Front and back face vertices
        cuboid.addVertex({-width / 2, -height / 2, depth / 2}); // 0
        cuboid.addVertex({width / 2, -height / 2, depth / 2});  // 1
        cuboid.addVertex({width / 2, height / 2, depth / 2});   // 2
        cuboid.addVertex({-width / 2, height / 2, depth / 2});  // 3
        cuboid.addVertex({-width / 2, -height / 2, -depth / 2}); // 4
        cuboid.addVertex({width / 2, -height / 2, -depth / 2});  // 5
        cuboid.addVertex({width / 2, height / 2, -depth / 2});   // 6
        cuboid.addVertex({-width / 2, height / 2, -depth / 2});  // 7
        // Faces

        return cuboid;
    }
    
    Polyhedron prism(double radius, double height, unsigned int sides) {
        GLESC::Math::Polyhedron prism;
        double angle = 2 * GLESC::Math::pi<double>() / sides;
        return prism;
    }
    
    Polyhedron icosphere(int subdivisions) {
        GLESC::Math::Polyhedron sphere;
        
    }
}