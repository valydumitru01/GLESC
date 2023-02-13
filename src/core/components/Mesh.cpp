#include "core/renderer/Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices)
{
    this->vertices=vertices;
}

Mesh::~Mesh()
{
}
void Mesh::setVertices(const std::vector<Vertex>& newVertices)
{
    vertices = newVertices;
}
void Mesh::addVertex(const Vertex& vertex)
{
    vertices.push_back(vertex);
}
std::vector<Vertex> Mesh::getVertices() const
{
    return vertices;
}