/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/Mesh.h"

using namespace GLESC;

Vertex::Vertex(const Vector3F &position, const Vector3F &color, const Vector2F &uv) :
        position(position), color(color), uv(uv) {}

Vertex::Vertex(const Vector3F &position) : Vertex(position, defaultVertexColor, defaultVertexUv) {}

Vertex::Vertex(const Vector3F &position, const Vector3F &color) : Vertex(position, color, defaultVertexUv) {}

Vertex::Vertex(const Vector3F &position, const Vector2F &uv) : Vertex(position, defaultVertexColor, uv) {}

HalfEdgeVertex::HalfEdgeVertex(const Vertex &vertex) : vertex(vertex) {}

HalfEdgeVertex::HalfEdgeVertex(const Vertex &&vertex) : vertex(vertex) {}

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<EdgeVertixIndices> &edgeIndicesList,
           const std::vector<FaceEdgeIndices> &faceIndicesList) {
    for (auto &vertex : vertices) {
        addVertex(vertex);
    }
    
    for (auto &edgeIndices : edgeIndicesList) {
        addEdge(edgeIndices);
    }
    
    for (auto &faceIndices : faceIndicesList) {
        addFace(faceIndices);
    }
}

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<EdgeVertices> &edgeVerticesList,
           const std::vector<FaceEdges> &faceVerticesList) {
    for (auto &vertex : vertices) {
        addVertex(vertex);
    }
    
    for (auto &edgeVertices : edgeVerticesList) {
        addEdge(edgeVertices);
    }
    
    for (auto &faceVertices : faceVerticesList) {
        addFace(faceVertices);
    }
}

HalfEdgeVertexPtr Mesh::addVertex(const Vertex &vertex) {
    halfEdgeVertices.emplace_back(std::make_shared<HalfEdgeVertex>(HalfEdgeVertex(vertex)));
    
}

HalfEdgeVertexPtr Mesh::addVertex(const Vertex &&vertex) {
    addVertex(vertex);
}

HalfEdgeVertexPtr Mesh::addVertex(const Vertex &vertex, const std::vector<VertexIndex>& endVerticesForEdge) {
    HalfEdgeVertexPtr startVertexPtr = addVertex(vertex);
    
    for (const VertexIndex &endVertexIndex : endVerticesForEdge) {
        HalfEdgeVertexPtr endVertexPtr = halfEdgeVertices[endVertexIndex];
        addEdge({startVertexPtr, endVertexPtr});
    }
    
    return startVertexPtr;
}

void Mesh::addEdge(const EdgeVertixIndices &edgeIndices) {
    addEdge({halfEdgeVertices[edgeIndices.first], halfEdgeVertices[edgeIndices.second]});
}

void Mesh::addEdge(const EdgeVertices &edgeVertices) {
    // Getting the vertices that the edge connects
    auto vert1 = edgeVertices.first;
    auto vert2 = edgeVertices.second;
    
    // Creating the half-edges, one for each direction (or vertex)
    // vert1 -> vert2 and vert2 -> vert1
    auto halfEdge1 = std::make_shared<HalfEdge>();
    auto halfEdge2 = std::make_shared<HalfEdge>();
    
    // Setting the vertices of the half-edges
    halfEdge1->vertex = vert1;
    halfEdge2->vertex = vert2;
    
    // The twins of the half-edges are each other
    halfEdge1->twin = halfEdge2;
    halfEdge2->twin = halfEdge1;
    
    // The half-edges are added to the list of half-edges
    halfEdges.push_back(halfEdge1);
    halfEdges.push_back(halfEdge2);
    
    // Setting the half-edges of the vertices
    // We need to be able to access the half-edges from the vertices
    vert1->halfEdge = halfEdge1;
    vert2->halfEdge = halfEdge2;
    
    // Creating the newly added edge
    auto newEdge = std::make_shared<HalfEdgeEdge>();
    // Setting the half-edge of the edge
    // Only one half-edge is needed, since the other one is the twin
    newEdge->halfEdge = halfEdge1;
    // Setting the edge of the half-edges
    halfEdge1->edge = newEdge;
    halfEdge2->edge = newEdge;
    
    // The edge set-up is complete, so we can add it to the list of edges
    halfEdgeEdges.push_back(newEdge);
    
    //
    if (vert1->halfEdge) {
        auto firstOutgoing = vert1->halfEdge;
        auto firstIncoming = firstOutgoing->twin;
        halfEdge2->next = firstOutgoing;
        firstIncoming->next = halfEdge1;
    }
    
    if (vert2->halfEdge) {
        auto secondOutgoing = vert2->halfEdge;
        auto secondIncoming = secondOutgoing->twin;
        halfEdge1->next = secondOutgoing;
        secondIncoming->next = halfEdge2;
    }
}