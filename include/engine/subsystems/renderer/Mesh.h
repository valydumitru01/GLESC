/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <vector>
#include <string>
#include "engine/core/math/Vector.h"

namespace GLESC {
    /*
    using VertexIndex = unsigned int;
    class Mesh {
    public:
        class Point {
        public:
            Point(float xParam, float yParam, float zParam, float uParam, float vParam) :
                    x(xParam), y(yParam), z(zParam), u(uParam), v(vParam) {}
            
            // 3D coordinates.
            float x;
            float y;
            float z;
            // Texture coordinates.
            float u;
            float v;
        };
        
        class Face {
        public:
            Face(VertexIndex index1, VertexIndex index2, VertexIndex index3) : vertices{index1, index2, index3} {}
            
            Face(VertexIndex index1, VertexIndex index2, VertexIndex index3, VertexIndex index4) : vertices{index1,
                                                                                                            index2,
                                                                                                            index3,
                                                                                                            index4} {}
            
            std::vector<VertexIndex> vertices;
        };
        
        Mesh() = default;
        
        VertexIndex addVertex(GLESC::Mesh::Point &&point);
        
        void addFace(VertexIndex &point1, VertexIndex &point2, VertexIndex &point3);
        
        void addFace(VertexIndex &point1, VertexIndex &point2, VertexIndex &point3, VertexIndex &point4);
        
        std::string toString() {
            std::string result = "\n\tVertices: ";
            for (auto const &vertex : vertices) {
                result += "\n\t\t" + std::to_string(vertex.x)
                          + ", " + std::to_string(vertex.y)
                          + ", " + std::to_string(vertex.z);
            }
            result += "\n\tFaces: ";
            for (auto &face : faces) {
                result += "\n\t\t" + std::to_string(face.vertices[0]) + ", " + std::to_string(face.vertices[1]) + ", " +
                          std::to_string(face.vertices[2]);
            }
            return result;
        }
    
    private:
        std::vector<GLESC::Mesh::Point> vertices;
        std::vector<GLESC::Mesh::Face> faces;
        
    }; // class Mesh
    */
    class HalfEdge;
    
    class Vertex {
    public:
        inline static const Vector3F defaultVertexColor = Vector3F(0, 0, 0);
        inline static const Vector2F defaultVertexUv = Vector2F(0, 0);
        
        explicit Vertex(Vector3F position, Vector3F color, Vector2F uv);
        
        explicit Vertex(Vector3F position);
        
        explicit Vertex(Vector3F position, Vector3F color);
        
        explicit Vertex(Vector3F position, Vector2F uv);
        
        HalfEdge *halfEdge{};  // Pointer to one of the outgoing half-edges from this vertex
        Vector3F position;
        Vector3F normal;
        Vector3F color;
        Vector2F uv;
    };
    
    class Face {
    public:
        HalfEdge *halfEdge;  // Pointer to one of the half-edges that bound this face
        Face() : halfEdge(nullptr) {}
    };
    
    class HalfEdge {
    public:
        HalfEdge *opposite;
        HalfEdge *next;
        HalfEdge *prev;
        Vertex *vertex;
        Face *face;
        // Additional member functions
    };
    
    class Mesh {
    public:
        std::vector<HalfEdge *> halfEdges;
        std::vector<Vertex *> vertices;
        std::vector<Face *> faces;
        
        Mesh() = default;
        
        // Constructor with pre-constructed vectors
        Mesh(std::vector<HalfEdge *> &halfEdges,
             std::vector<Vertex *> &vertices,
             std::vector<Face *> &faces);
        
        // Constructor with raw data
        Mesh(const std::vector<Vector3F> &vertexPositions,
             const std::vector<std::vector<int>> &faceIndices);
    };
}// namespace GLESC