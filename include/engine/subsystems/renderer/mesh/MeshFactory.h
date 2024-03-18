/**************************************************************************************************
 * @file   ColorMeshFactory.h
 * @author Valentin Dumitru
 * @date   10/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "Mesh.h"

namespace GLESC {
    class MeshFactory {
    public:
        static ColorMesh cube(const RGBA& color);
        static ColorMesh sphere(int subdivisions);
        static ColorMesh cuboid(const double width, const double height, const double depth);
        static ColorMesh pyramid(const double width, const double height, const double depth);
        static ColorMesh tris(const Vec3D& v1, const Vec3D& v2, const Vec3D& v3);
        static ColorMesh quad(const Vec3D& v1, const Vec3D& v2, const Vec3D& v3, const Vec3D& v4);
    }; // class ColorMeshFactory
} // namespace GLESC
