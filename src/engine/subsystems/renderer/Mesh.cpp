/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/Mesh.h"

using namespace GLESC;

void Mesh::addFace(VertexIndex &point1, VertexIndex &point2, VertexIndex &point3) {

}

void Mesh::addFace(VertexIndex &point1, VertexIndex &point2, VertexIndex &point3, VertexIndex &point4) {

}

VertexIndex Mesh::addVertex(GLESC::Mesh::Point &&point) {
    vertices.push_back(point);
    return static_cast<VertexIndex>(vertices.size() - 1); // Return index of the newly added vertex.
}