/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/Mesh.h"

using namespace GLESC;

Vertex::Vertex(Vector3F position, Vector3F color, Vector2F uv) : position(position), color(color), uv(uv) {}

Vertex::Vertex(Vector3F position) : Vertex(position, defaultVertexColor, defaultVertexUv) {}

Vertex::Vertex(Vector3F position, Vector3F color) : Vertex(position, color, defaultVertexUv) {}

Vertex::Vertex(Vector3F position, Vector2F uv) : Vertex(position, defaultVertexColor, uv) {}


// Constructor with pre-constructed vectors
Mesh::Mesh(std::vector<HalfEdge *> &halfEdges, std::vector<Vertex *> &vertices, std::vector<Face *> &faces)
        : halfEdges(halfEdges), vertices(vertices), faces(faces) {}

// Constructor with raw data
Mesh::Mesh(const std::vector<Vector3F> &vertexPositions, const std::vector<std::vector<int>> &faceIndices) {
    // Populate vertices
    for (const auto &position : vertexPositions) {
        vertices.push_back(new Vertex(position));
    }
    
    // Populate faces and halfEdges based on faceIndices
    for (const auto &faceIndex : faceIndices) {
        if (faceIndex.size() != 3) {
            //std::cerr << "Only triangular faces are supported." << std::endl;
            continue;
        }
        
        // Create HalfEdges and Face
        auto *newFace = new Face();
        faces.push_back(newFace);
        
        auto *he1 = new HalfEdge();
        auto *he2 = new HalfEdge();
        auto *he3 = new HalfEdge();
        
        he1->vertex = vertices[faceIndex[0]];
        he2->vertex = vertices[faceIndex[1]];
        he3->vertex = vertices[faceIndex[2]];
        
        he1->next = he2;
        he2->next = he3;
        he3->next = he1;
        
        he1->face = newFace;
        he2->face = newFace;
        he3->face = newFace;
        
        newFace->halfEdge = he1;
        
        halfEdges.push_back(he1);
        halfEdges.push_back(he2);
        halfEdges.push_back(he3);
    }
}