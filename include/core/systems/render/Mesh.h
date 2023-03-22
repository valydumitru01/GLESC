#pragma once

#include "core/renderer/Vertex.h"
#include <vector>
#include <memory>

class Mesh : Component {
private:
	std::vector <Vertex> vertices;
public:
	Mesh(std::vector <Vertex> vertices);

	Mesh();

	~Mesh();

	void addVertex(const Vertex &vertex);

	void addVertices(std::vector <Vertex> vertices);

	void setVertices(const std::vector <Vertex> &newVertices);

	std::unique_ptr <std::vector<Vertex>> getVertices() const;
};
