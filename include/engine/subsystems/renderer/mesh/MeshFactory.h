/**************************************************************************************************
 * @file   GLESC::MeshFactory.h
 * @author Valentin Dumitru
 * @date   10/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <filesystem>
#include "Mesh.h"

class MeshFactory {
public:
    static GLESC::Mesh cube(double size, RGBA color);
    
    static GLESC::Mesh sphere(double radius, int subdivisions);
    
    static GLESC::Mesh cuboid(const double width, const double height, const double depth);
    
    static GLESC::Mesh pyramid(const double width, const double height, const double depth);

    
    static GLESC::Mesh tris(const Vec3D& v1, const Vec3D& v2, const Vec3D& v3);
    
    static GLESC::Mesh quad(const Vec3D& v1, const Vec3D& v2, const Vec3D& v3, const Vec3D& v4);
    

}; // class GLESC::MeshFactory
