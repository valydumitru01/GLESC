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

bool HalfEdgeVertex::operator==(const HalfEdgeVertex &other) const {return vertex == other.vertex;}

HalfEdgeEdge::HalfEdgeEdge(const Edge &edge) : edge(edge) {}

HalfEdgeEdge::HalfEdgeEdge(const Edge &&edge) : edge(edge) {}

bool HalfEdgeEdge::operator==(const HalfEdgeEdge &other) const {return edge == other.edge;}

HalfEdgeFace::HalfEdgeFace(const Face &face) : face(face) {}

HalfEdgeFace::HalfEdgeFace(const Face &&face) : face(face) {}

bool HalfEdgeFace::operator==(const HalfEdgeFace &other) const {return face == other.face;}