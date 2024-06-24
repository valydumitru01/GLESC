/**************************************************************************************************
 * @file   MeshFactory.h
 * @author Valentin Dumitru
 * @date   10/12/2023
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "Mesh.h"

namespace GLESC::Render {
    /**
     * @brief Factory class for creating meshes
     * @details This is a utily class that helps create predefined meshes such as cube, sphere and so on.
     * For now this class is the building block for the mesh class as you are not able to import meshes and building
     * meshes by hand is pretty hard.
     */
    class MeshFactory {
    public:
        /**
         * @brief Creates a cube mesh given a color and a radius
         * @details All the faces will have the same color, and the vertices will be at the same distance from the
         * center (at the radius distance)
         * @param color The color of all the vertices
         * @param radius The radius of the cube
         * @return A mesh of a cube
         */
        static ColorMesh cube(const ColorRgba& color, const Math::Distance& radius = 1.0);

        /**
         * @brief Creates a sphere mesh given a number of slices, stacks, a radius and a color
         * @details The sphere is created by creating a number of slices and stacks, and then connecting the vertices
         * to create the sphere. The sphere will have the same color on all the vertices.
         * @param numSlices The number of slices of the sphere
         * @param numStacks The number of stacks of the sphere
         * @param radius The radius of the sphere
         * @param color The color of the sphere
         * @return A mesh of a sphere
         */
        static ColorMesh sphere(int numSlices, int numStacks, float radius, const ColorRgba& color);

        /**
         * @brief Creates a cuboid mesh given a width, height, depth and a color
         * @details A cuboid is a 3D shape with 6 faces, all of them are rectangles.
         * @param width The width of the cuboid (x axis)
         * @param height The height of the cuboid (y axis)
         * @param depth The depth of the cuboid (z axis)
         * @param color The color of the cuboid
         * @return A mesh of a cuboid
         */
        static ColorMesh cuboid(double width, double height, double depth, const ColorRgba& color);

        /**
         * @todo Doesnt work
         * @param width
         * @param height
         * @param depth
         * @param color
         * @return
         */
        static ColorMesh pyramid(double width, double height, double depth, const ColorRgba& color);

        /**
         * @details Simply creates a tris (2d triangle) mesh with the given color
         * @param color The color of the tris
         * @return A mesh of a tris
         */
        static ColorMesh tris(const ColorRgba& color);

        /**
         * @details Simply creates a plane mesh with the given color
         * @param color The color of the plane
         * @return A mesh of a plane
         */
        static ColorMesh plane(const ColorRgba& color);
    }; // class ColorMeshFactory
} // namespace GLESC
