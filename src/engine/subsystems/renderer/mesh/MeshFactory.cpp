/**************************************************************************************************
 * @file   MeshFactory.cpp
 * @author Valentin Dumitru
 * @date   17/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/mesh/MeshFactory.h"

GLESC::Mesh MeshFactory::cube(double size, RGBA color) {
    GLESC::Mesh mesh;
    GLESC::Vertex v1(Vec3D(-size, -size, -size), color);
    GLESC::Vertex v2(Vec3D(-size, -size, size), color);
    GLESC::Vertex v3(Vec3D(size, -size, size), color);
    GLESC::Vertex v4(Vec3D(size, -size, -size), color);
    GLESC::Vertex v5(Vec3D(-size, size, -size), color);
    GLESC::Vertex v6(Vec3D(-size, size, size), color);
    GLESC::Vertex v7(Vec3D(size, size, size), color);
    GLESC::Vertex v8(Vec3D(size, size, -size), color);
    
    // Bottom
    mesh.addQuad(v1, v2, v3, v4);
    // Top
    mesh.addQuad(v5, v6, v7, v8);
    // Left
    mesh.addQuad(v1, v2, v6, v5);
    // Right
    mesh.addQuad(v4, v3, v7, v8);
}

GLESC::Mesh MeshFactory::sphere(double radius, int subdivisions) {
    
}

GLESC::Mesh MeshFactory::cuboid(const double width, const double height, const double depth) {
    
}

GLESC::Mesh MeshFactory::pyramid(const double width, const double height, const double depth) {
    
}


GLESC::Mesh MeshFactory::tris(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3) {
    
}

GLESC::Mesh MeshFactory::quad(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Vec3D &v4) {
    
}