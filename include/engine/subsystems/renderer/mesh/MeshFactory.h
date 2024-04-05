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
        static ColorMesh cube(const Rgba &color);

        static ColorMesh sphere(int longitudeSubdivisions, int latitudeSubdivisions, const Rgba &color);

        static ColorMesh cuboid(double width, double height, double depth, const Rgba &color);

        static ColorMesh pyramid(double width, double height, double depth, const Rgba &color);

        static ColorMesh tris(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Rgba &color);

        static ColorMesh quad(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Vec3D &v4, const Rgba &color);
    }; // class ColorMeshFactory
} // namespace GLESC
