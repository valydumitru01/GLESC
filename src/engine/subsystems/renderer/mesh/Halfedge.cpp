/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/mesh/Halfedge.h"

using namespace GLESC;


void HalfEdgeContainer::addVertex(const Vertex &vertex) {
    vertices.push_back(vertex);
}

void HalfEdgeContainer::addEdge(const Edge &edge) {
    edges.push_back(edge);
}

void HalfEdgeContainer::addFace(const TrisFace &face) {
    faces.push_back(face);
}


std::shared_ptr<Vertex>
HalfEdgeContainer::getVertex(const Vertex &vertex) const {
    auto it = vertices.begin();
    while (it != vertices.end()) {
        if (*it == vertex) {
            return std::make_shared<Vertex>(*it);
        }
        ++it;
    }
}

std::shared_ptr<Edge>
HalfEdgeContainer::getEdge(const Edge &edge) const {
    auto it = edges.begin();
    while (it != edges.end()) {
        if (*it == edge) {
            return std::make_shared<Edge>(*it);
        }
        ++it;
    }
}

std::shared_ptr<TrisFace>
HalfEdgeContainer::getFace(const TrisFace &face) const {
    auto it = faces.begin();
    while (it != faces.end()) {
        if (*it == face) {
            return std::make_shared<TrisFace>(*it);
        }
        ++it;
    }
}






HalfEdgeVertex::HalfEdgeVertex(const Vertex &vertex,
                               HalfEdgeContainer &container) {
    container.addVertex(vertex);
    this->vertex = std::make_shared<Vertex>(vertex);
}


bool HalfEdgeVertex::operator==(const HalfEdgeVertex &other) const {
    return vertex == other.vertex;
}

HalfEdgeEdge::HalfEdgeEdge(const Edge &edge,
                           HalfEdgeContainer &container) {
    container.addEdge(edge);
    this->edge = container.getEdge(edge);
}


bool HalfEdgeEdge::operator==(const HalfEdgeEdge &other) const {
    return edge == other.edge;
}

HalfEdgeFace::HalfEdgeFace(const TrisFace &face, HalfEdgeContainer &container) {
    container.addFace(face);
    this->face = container.getFace(face);
}


bool HalfEdgeFace::operator==(const HalfEdgeFace &other) const {
    return face == other.face;
}

