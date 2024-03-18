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
using namespace GLESC;
ColorMesh MeshFactory::cube(const RGBA& color) {
    ColorMesh mesh;
    Vec4F rgba = Vec4F(color.r, color.g, color.b, color.a);

    // Define vertices with position, color, and normal
    // Front face
    ColorMesh::Vertex v1(Vec3D(-1, -1, -1), rgba, Vec3F(0, 0, -1));
    ColorMesh::Vertex v2(Vec3D(1, -1, -1), rgba, Vec3F(0, 0, -1));
    ColorMesh::Vertex v3(Vec3D(1, 1, -1), rgba, Vec3F(0, 0, -1));
    ColorMesh::Vertex v4(Vec3D(-1, 1, -1), rgba, Vec3F(0, 0, -1));
    // Back face
    ColorMesh::Vertex v5(Vec3D(-1, -1, 1), rgba, Vec3F(0, 0, 1));
    ColorMesh::Vertex v6(Vec3D(1, -1, 1), rgba, Vec3F(0, 0, 1));
    ColorMesh::Vertex v7(Vec3D(1, 1, 1), rgba, Vec3F(0, 0, 1));
    ColorMesh::Vertex v8(Vec3D(-1, 1, 1), rgba, Vec3F(0, 0, 1));

    // Front face
    mesh.addTris(v1, v2, v3);
    mesh.addTris(v3, v4, v1);
    // Back face
    mesh.addTris(v6, v5, v8);
    mesh.addTris(v8, v7, v6);
    // Right face
    mesh.addTris(v2, v6, v7);
    mesh.addTris(v7, v3, v2);
    // Left face
    mesh.addTris(v5, v1, v4);
    mesh.addTris(v4, v8, v5);
    // Top face
    mesh.addTris(v4, v3, v7);
    mesh.addTris(v7, v8, v4);
    // Bottom face
    mesh.addTris(v5, v6, v2);
    mesh.addTris(v2, v1, v5);

    return mesh;
}
ColorMesh MeshFactory::sphere(int subdivisions) {
    
}

ColorMesh MeshFactory::cuboid(const double width, const double height, const double depth) {
    
}

ColorMesh MeshFactory::pyramid(const double width, const double height, const double depth) {
    
}


ColorMesh MeshFactory::tris(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3) {
    
}

ColorMesh MeshFactory::quad(const Vec3D &v1, const Vec3D &v2, const Vec3D &v3, const Vec3D &v4) {
    
}