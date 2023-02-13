#pragma once
#include "core/renderer/Vertex.h"
#include "core/components/Component.h"
#include <vector>
class Mesh : Component
{
private:
    std::vector<Vertex> vertices;
public:
    Mesh(std::vector<Vertex> vertices);
    Mesh();
    ~Mesh();
    void addVertex(const Vertex& vertex);
    void addVertices(std::vector<Vertex> vertices);
    void setVertices(const std::vector<Vertex>& newVertices);
    std::vector<Vertex> Mesh::getVertices() const;
};
