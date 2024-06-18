/**************************************************************************************************
 * @file   PolyhedronFactory.h
 * @author Valentin Dumitru
 * @date   15/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"

namespace PolyhedronFactory {
    namespace Regular {
        /**
         * @brief Regular polyhedron with 4 faces (pyramid, all faces are triangles)
         * @return A tetrahedron
         */
        static GLESC::Math::Polyhedron tetra();
        
        /**
         * @brief Regular polyhedron with 6 faces (cube, all faces are squares)
         * @return A cube
         */
        static GLESC::Math::Polyhedron cube();
        
        /**
         * @brief Regular polyhedron with 8 faces (octahedron, all faces are triangles, looks like
         * two pyramids glued together)
         * @return An octahedron
         */
        static GLESC::Math::Polyhedron octa();
        
        /**
         * @brief Regular polyhedron with 12 faces (dodecahedron, all faces are pentagons)
         * @return A dodecahedron
         */
        static GLESC::Math::Polyhedron dodeca();
        
        /**
         * @brief Regular polyhedron with 20 faces (icosahedron, all faces are triangles, looks like
         * a 20 side dice in D&D)
         * @return An icosahedron
         */
        static GLESC::Math::Polyhedron icos();
    }; // namespace Regular
    namespace Common {
        /**
         * @brief A pyramid is a polyhedron formed by connecting a polygonal base and a point,
         * called the apex. Each base edge and apex form a triangle, called a lateral face.
         * @param radius radius of the base
         * @param height height of the pyramid
         * @param baseSides number of sides of the base
         */
        static GLESC::Math::Polyhedron
        pyramid(double radius, double height, unsigned int baseSides);
        
        /**
         * @brief A rectangular cuboid is a polyhedron with 6 rectangular faces. It is also known as
         * a rectangular hexahedron, right rectangular prism, rectangular prism, or rectangular
         * parallelepiped.
         * @param width
         * @param height
         * @param depth
         * @return
         */
        static GLESC::Math::Polyhedron rectangularCuboid(double width, double height, double depth);
        
        /**
         * @brief A prism is a polyhedron with an n-sided polygonal base, a translated copy (not in
         * the same plane as the first), and n other faces (necessarily all parallelograms) joining
         * corresponding sides of the two bases.
         * @param radius radius of the base or the top
         * @param height height of the prism
         * @param sides number of sides of the base
         * @return
         */
        static GLESC::Math::Polyhedron prism(double radius, double height, unsigned int sides);
        
        /**
         * @brief An icosphere is a polyhedron with N faces, all of them triangles. It is a sphere
         * approximated by a polyhedron with N faces.
         * @param subdivisions number of subdivisions of the icosphere. The higher the number, the
         *                    smoother the sphere will be.
         */
        static GLESC::Math::Polyhedron icosphere(int subdivisions);
        
    }

}; // namespace PolygonFactory
