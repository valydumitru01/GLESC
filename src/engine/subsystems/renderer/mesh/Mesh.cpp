/**************************************************************************************************
 * @file   Mesh.cpp
 * @author Valentin Dumitru
 * @date   17/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/mesh/Mesh.h"

using namespace GLESC;

void Mesh::addTris(const Vertex& a, const Vertex& b, const Vertex& c) {
    addVertex(a); addVertex(b); addVertex(c);
    dirtyFlag = true;
}

void Mesh::addQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d) {
    addVertex(a); addVertex(b); addVertex(c); addVertex(d);
    dirtyFlag = true;
}

std::string Mesh::toString() const {
    std::string result = "Mesh\n";
    result += "Vertices (first 10):\n";
    for (size_t i = 0; i < 10 && i < vertices.size(); ++i) {
        result += vertices[i].toString() + "\n";
    }
    result += "Indices (first 10):\n";
    for (size_t i = 0; i < 10 && i < indices.size(); ++i) {
        result += std::to_string(indices[i]) + "\n";
    }
    return result;
}
void Mesh::addVertex(const Vertex& vertex) {
    // Attempt to insert the vertex with its index into the map.
    // The insert operation does not overwrite existing entries and returns a pair.
    // The first element of the pair is an iterator to the existing or inserted element,
    // and the second element is a boolean that is true if the insertion was successful.
    auto result = vertexToIndexMap.insert({vertex, static_cast<Index>(vertices.size())});
    
    // If the vertex was not already in the map (i.e., insertion was successful),
    // then add the vertex to the vertices vector.
    if (result.second) {
        vertices.push_back(vertex);
        topology.addVertex(vertex.getPosition());
    } else{
    }
    
    // Regardless of whether the vertex was just inserted or already existed,
    // add its index to the indices vector.
    // result.first is an iterator to the pair in the map, and .second accesses the index.
    indices.push_back(result.first->second);
}