/**************************************************************************************************
 * @file   MeshFactory.h
 * @author Valentin Dumitru
 * @date   10/12/2023
 * @brief  Add description of this file if needed @TODO
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
        static ColorMesh cube(const ColorRgba &color, const Math::Distance& radius = 1.0);

        static ColorMesh sphere(int numSlices, int numStacks, float radius, const ColorRgba &color);

        static ColorMesh cuboid(double width, double height, double depth, const ColorRgba &color);

        static ColorMesh pyramid(double width, double height, double depth, const ColorRgba &color);

        static ColorMesh tris(const ColorRgba &color);

        static ColorMesh plane(const ColorRgba &color);
    }; // class ColorMeshFactory
} // namespace GLESC
