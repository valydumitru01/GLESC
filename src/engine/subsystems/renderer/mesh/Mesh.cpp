/******************************************************************************
 * @file   Mesh.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Implementation of the Mesh class
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/core/exceptions/subsystems/MeshException.h"

using namespace GLESC;

Mesh::VertexPtr Mesh::addVertex(const Vertex vertex) {
    vertices.push_back(vertex);
    return std::make_shared<Vertex>(vertices.back());
}

Mesh::VertexPtr Mesh::getVertex(const Vertex vertex) const {
    auto it = vertices.begin();
    while (it != vertices.end()) {
        if (*it == vertex) {
            return std::make_shared<Vertex>(*it);
        }
        ++it;
    }
}

Mesh::VertexPtr Mesh::getVertex(const size_t index) const {
    return std::make_shared<Vertex>(vertices[index]);
}

std::vector<Mesh::VertexPtr>
Mesh::addVertices(const std::initializer_list<Vertex> verticesParam) {
    std::vector<std::shared_ptr<Vertex>> addedVertices;
    for (const auto &vertex : verticesParam) {
        vertices.push_back(vertex);
        addedVertices.push_back(std::make_shared<Vertex>(vertices.back()));
    }
    return addedVertices;
}

void Mesh::addFace(const FaceVertices &faceVertices) {
    if (faceVertices.x->getPosition() == faceVertices.y->getPosition() ||
        faceVertices.x->getPosition() == faceVertices.z->getPosition() ||
        faceVertices.y->getPosition() == faceVertices.z->getPosition()) {
        throw MeshException("Vertices must be unique");
    }
    Face face;
    
    face.calculateData(*faceVertices.x, *faceVertices.y, *faceVertices.z);
    faces.push_back(face);
    
}

void Mesh::addFaces(const std::initializer_list<FaceVertices> &faceVertices) {
    for (const auto &vertex : faceVertices) {
        addFace(vertex);
    }
}

std::vector<Vertex>& Mesh::getVertices() {
    return vertices;
}

std::vector<Face>& Mesh::getFaces() {
    return faces;
}

std::string Mesh::toString() const {
    std::string result = "Mesh: \n";
    result += "Vertices: \n";
    for (const auto &vertex : vertices) {
        result += vertex.toString() + "\n";
    }
    result += "Faces: \n";
    for (const auto &face : faces) {
        result += face.toString() + "\n";
    }
    return result;
}