/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <vector>
#include <string>

namespace GLESC {
    typedef unsigned int VertexIndex;
    class Mesh {
    public:
        class Point {
        public:
            Point(float x, float y, float z, float u, float v) : x(x), y(y), z(z), u(u), v(v) {}
            float x, y, z; // 3D coordinates.
            float u, v; // Texture coordinates.
        };
        
        class Face {
        public:
            Face(VertexIndex index1, VertexIndex index2, VertexIndex index3) : vertices{index1, index2, index3} {}
            
            Face(VertexIndex index1, VertexIndex index2, VertexIndex index3, VertexIndex index4) : vertices{index1,
                                                                                                            index2,
                                                                                                            index3,
                                                                                                            index4} {}
            
            std::vector <VertexIndex> vertices;
        };
        
        Mesh() = default;
        
        VertexIndex addVertex(GLESC::Mesh::Point &&point);
        
        void addFace(VertexIndex &point1, VertexIndex &point2, VertexIndex &point3);
        
        void addFace(VertexIndex &point1, VertexIndex &point2, VertexIndex &point3, VertexIndex &point4);
        
        std::string toString(){
            std::string result = "\n\tVertices: ";
            for (auto &vertex : vertices) {
                result += "\n\t\t" + std::to_string(vertex.x) + ", " + std::to_string(vertex.y) + ", " + std::to_string(vertex.z);
            }
            result += "\n\tFaces: ";
            for (auto &face : faces) {
                result += "\n\t\t" + std::to_string(face.vertices[0]) + ", " + std::to_string(face.vertices[1]) + ", " + std::to_string(face.vertices[2]);
            }
            return result;
        }
    private:
        std::vector <GLESC::Mesh::Point> vertices;
        std::vector <GLESC::Mesh::Face> faces;
        
    }; // class Mesh
    
} // namespace GLESC