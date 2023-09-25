/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/mesh/Halfedge.h"

using namespace GLESC;



HalfEdgeVertex::HalfEdgeVertex(const Vertex &vertex) : vertex(vertex) {}

HalfEdgeVertex::HalfEdgeVertex(const Vertex &&vertex) : vertex(vertex) {}



Mesh::Mesh(const Vertex &vertex1Param,
           const Edge &edge1Param,
           const Vertex &vertex2Param,
           const Edge &edge2Param,
           const Vertex &vertex3Param,
           const Edge &edge3Param,
           std::optional<Face> faceParam) {
    // ------------- initialization --------------
    // Creating the half-edges
    auto halfEdge1 = std::make_shared<HalfEdge>();
    auto halfEdge2 = std::make_shared<HalfEdge>();
    auto halfEdge3 = std::make_shared<HalfEdge>();
    
    auto halfEdge4 = std::make_shared<HalfEdge>();
    auto halfEdge5 = std::make_shared<HalfEdge>();
    auto halfEdge6 = std::make_shared<HalfEdge>();
    
    // Creating the edge data pointers
    auto edge1 = std::make_shared<HalfEdgeEdge>(HalfEdgeEdge(edge1Param));
    auto edge2 = std::make_shared<HalfEdgeEdge>(HalfEdgeEdge(edge2Param));
    auto edge3 = std::make_shared<HalfEdgeEdge>(HalfEdgeEdge(edge3Param));
    
    // Creating the vertex data pointers
    auto vertex1 = std::make_shared<HalfEdgeVertex>(HalfEdgeVertex(vertex1Param));
    auto vertex2 = std::make_shared<HalfEdgeVertex>(HalfEdgeVertex(vertex2Param));
    auto vertex3 = std::make_shared<HalfEdgeVertex>(HalfEdgeVertex(vertex3Param));
    
    // Creating the face data pointer if there is one
    std::shared_ptr<HalfEdgeFace> newFace;
    if (faceParam.has_value())
        newFace= std::make_shared<HalfEdgeFace>(HalfEdgeFace(faceParam.value()));
    
    // ---------- half-edge navigation -----------
    // Setting the next pointers of the circular half-edges
    // its important that it must be circular, otherwise the mesh will not be manifold
    
    // halfEdge1 -> halfEdge2 -> halfEdge3 -> halfEdge1
    halfEdge1->next = halfEdge2;
    halfEdge2->next = halfEdge3;
    halfEdge3->next = halfEdge1;
    
    // halfEdge4 -> halfEdge5 -> halfEdge6 -> halfEdge4
    halfEdge4->next = halfEdge5;
    halfEdge5->next = halfEdge6;
    halfEdge6->next = halfEdge4;
    
    // Setting the twin pointers of the half-edges
    halfEdge1->twin = halfEdge4;
    halfEdge2->twin = halfEdge5;
    halfEdge3->twin = halfEdge6;
    
    // ------------- half-edge data --------------
    // Setting the vertices data of the half-edges
    halfEdge1->vertex = vertex1;
    halfEdge2->vertex = vertex2;
    halfEdge3->vertex = vertex3;
    halfEdge4->vertex = vertex3;
    halfEdge5->vertex = vertex2;
    halfEdge6->vertex = vertex1;
    
    // Setting the face data of the half-edges, if there is one (if not, it will be nullopt)
    halfEdge1->face = newFace;
    halfEdge2->face = newFace;
    halfEdge3->face = newFace;
    halfEdge4->face = newFace;
    halfEdge5->face = newFace;
    halfEdge6->face = newFace;
    
    // Setting the edge data of the half-edges
    halfEdge1->edge = edge1;
    halfEdge2->edge = edge2;
    halfEdge3->edge = edge3;
    halfEdge4->edge = edge3;
    halfEdge5->edge = edge2;
    halfEdge6->edge = edge1;
    
    // ------------- data linking to half-edge --------------
    // Setting the half-edge data of the vertices
    vertex1->halfEdge = halfEdge1;
    vertex2->halfEdge = halfEdge2;
    vertex3->halfEdge = halfEdge3;
    vertex3->halfEdge = halfEdge4;
    vertex2->halfEdge = halfEdge5;
    vertex1->halfEdge = halfEdge6;
    
    // Setting the half-edge data of the edges
    edge1->halfEdge = halfEdge1;
    edge2->halfEdge = halfEdge2;
    edge3->halfEdge = halfEdge3;
    edge3->halfEdge = halfEdge4;
    edge2->halfEdge = halfEdge5;
    edge1->halfEdge = halfEdge6;
    
    // Setting the half-edge data of the face
    newFace->halfEdge = halfEdge1;
    
    // ------------- data linking to mesh --------------
    // inserting the vertices
    halfEdgeVertices.push_back(vertex1);
    halfEdgeVertices.push_back(vertex2);
    halfEdgeVertices.push_back(vertex3);
    
    // inserting the edges
    halfEdgeEdges.push_back(edge1);
    halfEdgeEdges.push_back(edge2);
    halfEdgeEdges.push_back(edge3);
    
    // inserting the face, if there is one
    if (faceParam.has_value())
        halfEdgeFaces.push_back(newFace);
    
    // inserting the half-edges
    halfEdges.push_back(halfEdge1);
    halfEdges.push_back(halfEdge2);
    halfEdges.push_back(halfEdge3);
    
}

HalfEdgeVertexPtr Mesh::addVertex(const Vertex &vertex,
                                  VertexIndex &vertexIndex1,
                                  Edge &edgeData1,
                                  VertexIndex &vertexIndex2,
                                  Edge &edgeData2) {
    // ------------- initialization --------------
    // Creating the half-edges
    auto halfEdge1 = std::make_shared<HalfEdge>();
    auto halfEdge2 = std::make_shared<HalfEdge>();
    auto halfEdge3 = std::make_shared<HalfEdge>();
    auto halfEdge4 = std::make_shared<HalfEdge>();
    auto halfEdge5 = halfEdgeVertices[vertexIndex1]->halfEdge;
    auto halfEdge6 = halfEdgeVertices[vertexIndex2]->halfEdge;
    
    // Creating the edge data pointers
    auto edge1 = std::make_shared<HalfEdgeEdge>(HalfEdgeEdge(edgeData1));
    auto edge2 = std::make_shared<HalfEdgeEdge>(HalfEdgeEdge(edgeData2));
    
    // Creating the vertex data pointers
    auto vertex1 = std::make_shared<HalfEdgeVertex>(HalfEdgeVertex(vertex));
    auto vertex2 = std::make_shared<HalfEdgeVertex>(HalfEdgeVertex(vertex));
    
    // ---------- half-edge navigation -----------
    halfEdge1->next = halfEdge2;
    halfEdge2->next = halfEdge3;
    halfEdge3->next = halfEdge1;
    
}

HalfEdgeVertexPtr Mesh::addVertex(const Vertex &vertex,
                                  VertexIndex &vertexIndex1,
                                  Edge edgeData1,
                                  VertexIndex &vertexIndex2,
                                  Edge edgeData2,
                                  Face &face) {
    
}