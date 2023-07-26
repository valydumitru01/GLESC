

void GlApi::generateVertexArray(GLuint &VAO) {
    glGenVertexArrays(1, &VAO);
}

void GlApi::generateVertexBuffer(GLuint &VBO) {
    glGenBuffers(1, &VBO);
}

void GlApi::generateElementBuffer(GLuint &EBO) {
    glGenBuffers(1, &EBO);
}

void GlApi::generateBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO) {
    generateVertexArray(VAO);
    generateVertexBuffer(VBO);
    generateElementBuffer(EBO);
}

void GlApi::deleteVertexArray(GLuint &VAO) {
    glDeleteVertexArrays(1, &VAO);
}

void GlApi::deleteVertexBuffer(GLuint &VBO) {
    glDeleteBuffers(1, &VBO);
}

void GlApi::deleteElementBuffer(GLuint &EBO) {
    glDeleteBuffers(1, &EBO);
}

void GlApi::deleteBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO) {
    deleteVertexArray(VAO);
    deleteVertexBuffer(VBO);
    deleteElementBuffer(EBO);
}


void GlApi::bindVertexArray(GLuint VAO) {
    glBindVertexArray(VAO);
}

void GlApi::bindVertexBuffer(GLuint VBO) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void GlApi::bindElementBuffer(GLuint EBO) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void GlApi::unbindVertexArray() {
    glBindVertexArray(0);
}

void GlApi::unbindVertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GlApi::unbindElementBuffer() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GlApi::createVertexAttribute(unsigned int index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                  const void *offset) {
    // Specify the location and data format of the array of generic vertex
    // attributes at index index to use when rendering
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    // Enable the vertex attribute for the currently bound vertex array object (VAO)
    glEnableVertexAttribArray(index);
}

void GlApi::storeDataForElementBuffer(const std::vector <unsigned int> &indices) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr> (indices.size() * sizeof(unsigned int)),
                 indices.data(), GL_STATIC_DRAW);
}

void GlApi::storeDataForVertexBuffer(const std::vector <float> &vertices) {
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr> (vertices.size() * sizeof(float)), vertices.data(),
                 GL_STATIC_DRAW);
}

void GlApi::drawElements(GLsizei count, const void *indice, GLenum type, GLenum mode) {
    glDrawElements(mode, count, type, indice);
    
}

