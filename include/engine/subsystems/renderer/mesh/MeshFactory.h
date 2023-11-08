/******************************************************************************
 * @file   MeshFactory.h
 * @author Valentin Dumitru
 * @date   2023-10-02
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "Mesh.h"

namespace GLESC {
    class MeshFactory {
    public:
        static inline GLESC::Mesh cube(double radius) {
            GLESC::Mesh mesh;
            
            // Define cube vertices using addVertices
            auto cubeVertices = mesh.addVertices({{-radius, -radius, -radius},
                                                  {-radius, -radius, radius},
                                                  {-radius, radius,  -radius},
                                                  {-radius, radius,  radius},
                                                  {radius,  -radius, -radius},
                                                  {radius,  -radius, radius},
                                                  {radius,  radius,  -radius},
                                                  {radius,  radius,  radius}});
            
            // Define faces using addFaces and initializer list
            // Faces are triangles
            mesh.addFaces({{cubeVertices[0], cubeVertices[1], cubeVertices[2]},
                           {cubeVertices[1], cubeVertices[2], cubeVertices[3]},
                           {cubeVertices[0], cubeVertices[1], cubeVertices[4]},
                           {cubeVertices[1], cubeVertices[4], cubeVertices[5]},
                           {cubeVertices[0], cubeVertices[2], cubeVertices[4]},
                           {cubeVertices[2], cubeVertices[4], cubeVertices[6]},
                           {cubeVertices[1], cubeVertices[3], cubeVertices[5]},
                           {cubeVertices[3], cubeVertices[5], cubeVertices[7]},
                           {cubeVertices[2], cubeVertices[3], cubeVertices[6]},
                           {cubeVertices[3], cubeVertices[6], cubeVertices[7]},
                           {cubeVertices[4], cubeVertices[5], cubeVertices[6]},
                           {cubeVertices[5], cubeVertices[6], cubeVertices[7]}});
            
            return mesh;
        }
        
        static inline GLESC::Mesh
        rectangularPrism(double width, double height, double depth) {
            GLESC::Mesh mesh;
            
            // Define rectangular prism vertices using addVertices
            auto vertices = mesh.addVertices(
                    {{-width / 2, -height / 2, -depth / 2},
                     {-width / 2, -height / 2, depth / 2},
                     {-width / 2, height / 2,  -depth / 2},
                     {-width / 2, height / 2,  depth / 2},
                     {width / 2,  -height / 2, -depth / 2},
                     {width / 2,  -height / 2, depth / 2},
                     {width / 2,  height / 2,  -depth / 2},
                     {width / 2,  height / 2,  depth / 2}});
            
            // Define faces using addFaces and initializer list
            // Faces are triangles
            mesh.addFaces(
                    {{vertices[0], vertices[1], vertices[2]},
                     {vertices[1], vertices[2], vertices[3]},
                     {vertices[0], vertices[1], vertices[4]},
                     {vertices[1], vertices[4], vertices[5]},
                     {vertices[0], vertices[2], vertices[4]},
                     {vertices[2], vertices[4], vertices[6]},
                     {vertices[1], vertices[3], vertices[5]},
                     {vertices[3], vertices[5], vertices[7]},
                     {vertices[2], vertices[3], vertices[6]},
                     {vertices[3], vertices[6], vertices[7]},
                     {vertices[4], vertices[5], vertices[6]},
                     {vertices[5], vertices[6], vertices[7]}});
        }
        
        static inline GLESC::Mesh tetrahedron(double radius) {
            GLESC::Mesh mesh;
            
            // Define tetrahedron vertices using addVertices
            auto vertices = mesh.addVertices({{0,       0,      -radius},
                                              {0,       radius, 0},
                                              {-radius, 0,      0},
                                              {radius,  0,      0}});
            
            // Define faces using addFaces and initializer list
            mesh.addFaces(
                    {{vertices[0], vertices[1], vertices[2]},
                     {vertices[0], vertices[1], vertices[3]},
                     {vertices[0], vertices[2], vertices[3]},
                     {vertices[1], vertices[2], vertices[3]}});
            
            return mesh;
        }
        
        static inline GLESC::Mesh octahedron(double radius) {
            GLESC::Mesh mesh;
            
            // Define octahedron vertices using addVertices
            auto vertices =
                    mesh.addVertices({{0,       0,       -radius},
                                      {0,       0,       radius},
                                      {0,       -radius, 0},
                                      {0,       radius,  0},
                                      {-radius, 0,       0},
                                      {radius,  0,       0}});
            
            // Define faces using addFaces and initializer list
            mesh.addFaces(
                    {{vertices[0], vertices[2], vertices[3]},
                     {vertices[0], vertices[3], vertices[4]},
                     {vertices[0], vertices[4], vertices[2]},
                     {vertices[1], vertices[2], vertices[3]},
                     {vertices[1], vertices[3], vertices[4]},
                     {vertices[1], vertices[4], vertices[2]}});
            
            return mesh;
        }
        
        static inline GLESC::Mesh sphere(double radius, int slices, int stacks) {
            GLESC::Mesh mesh;
            // Generated with trigonometric functions
            // https://en.wikipedia.org/wiki/Sphere#Cartesian_coordinates
            for (int i = 0; i < slices; i++) {
                for (int j = 0; j < stacks; j++) {
                    // The following code is used to generate the vertices
                    auto theta = 2.0 * GLESC::Math::PI * i / slices;
                    auto phi = GLESC::Math::PI * static_cast<float>(j / stacks);
                    auto x = radius * sin(phi) * cos(theta);
                    auto y = radius * sin(phi) * sin(theta);
                    auto z = radius * cos(phi);
                    mesh.addVertex({x, y, z});
                }
            }
            
            // The following code is used to generate the faces
            for (int i = 0; i < slices; i++) {
                for (int j = 0; j < stacks; j++) {
                    auto vert1 = i * stacks + j;
                    auto vert2 = (i + 1) * stacks + j;
                    auto vert3 = i * stacks + (j + 1);
                    auto vert4 = (i + 1) * stacks + (j + 1);
                    mesh.addFace({mesh.getVertex(vert1),
                                  mesh.getVertex(vert2),
                                  mesh.getVertex(vert3)});
                    mesh.addFace({mesh.getVertex(vert2),
                                  mesh.getVertex(vert4),
                                  mesh.getVertex(vert3)});
                }
            }
            
            
            return mesh;
        }
    };
}