#include "renderer/Mesh.h"

Mesh::Mesh(const std::vector <float> &vertices, const std::vector <unsigned int> &indices,
           const std::vector <VertexAttribute> &attributes) {
    create(vertices, indices, attributes);
}

void Mesh::create(const std::vector <float> &vertices, const std::vector <unsigned int> &indices,
                  const std::vector <VertexAttribute> &attributes) {
    indexCount = static_cast<GLsizei>(indices.size());
    
    GlApi::generateBuffers(VAO, VBO, EBO);
    
    
    GlApi::bindVertexArray(VAO);
    
    GlApi::bindVertexBuffer(VBO);
    GlApi::storeDataForVertexBuffer(vertices);
    
    GlApi::bindElementBuffer(EBO);
    GlApi::storeDataForElementBuffer(indices);
    
    // Create custom vertex attributes
    createVertexAttributes(attributes);
    
    GlApi::unbindVertexArray();
};

void Mesh::createVertexAttributes(const std::vector <VertexAttribute> &attributes) {
    size_t stride = 0;
    for (const auto &attr: attributes) {
        stride += attr.size * sizeof(float);
    }
    
    for (const auto &attr: attributes) {
        GlApi::createVertexAttribute(attr.location, attr.size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride),
                                     (void *) (attr.offset * sizeof(float)));
    }
}

void Mesh::destroy() {
    GlApi::deleteBuffers(VAO, VBO, EBO);
}

void Mesh::addVertexData(const std::vector <float> &vertexDataParam) {
    
    GlApi::bindVertexBuffer(VBO);
    
    vertexData.insert(vertexData.end(), vertexDataParam.begin(), vertexDataParam.end());
    
    // Update the VBO with the new data
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexData.size() * sizeof(float)), vertexData.data(),
                 GL_DYNAMIC_DRAW);
    
}
