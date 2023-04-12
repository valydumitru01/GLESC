#include "renderer/GlWrapper.h"

void GlWrapper::generateVertexArray(GLuint &VAO) {
    glGenVertexArrays(1, &VAO);
    glCheckError();
}

void GlWrapper::generateVertexBuffer(GLuint &VBO) {
    glGenBuffers(1, &VBO);
    glCheckError();
}

void GlWrapper::generateElementBuffer(GLuint &EBO) {
    glGenBuffers(1, &EBO);
    glCheckError();
}

void GlWrapper::generateBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO) {
    generateVertexArray(VAO);
    generateVertexBuffer(VBO);
    generateElementBuffer(EBO);
}

void GlWrapper::deleteVertexArray(GLuint &VAO) {
    glDeleteVertexArrays(1, &VAO);
    glCheckError();
}

void GlWrapper::deleteVertexBuffer(GLuint &VBO) {
    glDeleteBuffers(1, &VBO);
    glCheckError();
}

void GlWrapper::deleteElementBuffer(GLuint &EBO) {
    glDeleteBuffers(1, &EBO);
    glCheckError();
}

void GlWrapper::deleteBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO) {
    deleteVertexArray(VAO);
    deleteVertexBuffer(VBO);
    deleteElementBuffer(EBO);
}


void GlWrapper::bindVertexArray(GLuint VAO) {
    glBindVertexArray(VAO);
    glCheckError();
}

void GlWrapper::bindVertexBuffer(GLuint VBO) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();
}

void GlWrapper::bindElementBuffer(GLuint EBO) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glCheckError();
}

void GlWrapper::unbindVertexArray() {
    glBindVertexArray(0);
    glCheckError();
}

void GlWrapper::unbindVertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();
}

void GlWrapper::unbindElementBuffer() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glCheckError();
}

void GlWrapper::createVertexAttribute(unsigned int index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                      const void *offset) {
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glCheckError();
    glEnableVertexArrayAttrib(index, size);
    glCheckError();
}

void GlWrapper::storeDataForElementBuffer(const std::vector <unsigned int> &indices) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr> (indices.size() * sizeof(unsigned int)),
                 indices.data(), GL_STATIC_DRAW);
    glCheckError();
}

void GlWrapper::storeDataForVertexBuffer(const std::vector <float> &vertices) {
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr> (vertices.size() * sizeof(float)), vertices.data(),
                 GL_STATIC_DRAW);
    glCheckError();
}

void GlWrapper::drawElements(GLsizei count, const void *indice, GLenum type, GLenum mode) {
    glDrawElements(mode, count, type, indice);
    glCheckError();
    
}

