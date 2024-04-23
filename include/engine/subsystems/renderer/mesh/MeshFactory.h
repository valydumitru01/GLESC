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
    class MeshFactory {
    public:
        static ColorMesh cube(const ColorRgba &color);

        static ColorMesh sphere(int numSlices, int numStacks, const ColorRgba &color);

        static ColorMesh cuboid(double width, double height, double depth, const ColorRgba &color);

        static ColorMesh pyramid(double width, double height, double depth, const ColorRgba &color);

        static ColorMesh tris(const ColorRgba &color);

        static ColorMesh plane(const ColorRgba &color);
    }; // class ColorMeshFactory
} // namespace GLESC
