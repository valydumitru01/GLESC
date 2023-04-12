#include "renderer/Mesh.h"

Mesh::Mesh(const std::vector <float> &vertices, const std::vector <unsigned int> &indices) :
        VAO(0), VBO(0), EBO(0), indexCount(static_cast<GLsizei> (indices.size())) {
    GlWrapper::generateBuffers(VAO, VBO, EBO);
    
    
    GlWrapper::bindVertexArray(VAO);
    
    GlWrapper::bindVertexBuffer(VBO);
    GlWrapper::storeDataForVertexBuffer(vertices);
    
    GlWrapper::bindElementBuffer(EBO);
    GlWrapper::storeDataForElementBuffer(indices);
    
    // Position attribute
    GlWrapper::createVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    // Color attribute
    GlWrapper::createVertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    // Texture coordinate attribute
    GlWrapper::createVertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    // Normal attribute
    GlWrapper::createVertexAttribute(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (8 * sizeof(float)));
    
    
    GlWrapper::unbindVertexArray();
}

Mesh::~Mesh() {
    GlWrapper::deleteBuffers(VAO, VBO, EBO);
}


void Mesh::addVertexData(const std::vector <float> &vertexDataParam) {
    
    GlWrapper::bindVertexBuffer(VBO);
    
    vertexData.insert(vertexData.end(), vertexDataParam.begin(), vertexDataParam.end());
    
    // Update the VBO with the new data
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexData.size() * sizeof(float)), vertexData.data(),
                 GL_DYNAMIC_DRAW);
    
}


Mesh::Mesh() : VAO(0), VBO(0), EBO(0), indexCount(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}
