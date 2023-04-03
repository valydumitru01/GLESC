#pragma once

#include "glm/glm.hpp"

class Vertex {
public:
    /**
     * @brief Vertex position
     *
     * This vector defines the position of the vector in 3D space
     *
     */
    glm::vec3 pos;
    /**
     * @brief Vertex normal
     *
     * This vector defines the unit surface normal of a vertex.
     * It is used in per-vertex dynamic lighting calculations.
     */
    glm::vec3 normal;
    /**
     * @brief Texture coordinates
     *
     * Texture coordinates allow a two-dimensional bitmap to be “shrink wrapped” onto
     * the surface of the mesh — a process known as texture mapping. A texture
     * coordinate (u, v) describes the location of a particular vertex within the
     * two-dimensional normalized coordinate space of the texture.
     */
    glm::vec2 UV;
};