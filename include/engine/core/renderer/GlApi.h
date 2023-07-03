#pragma once

#include "GL/glew.h"
#include "RenderDebugger.h"

class GlApi {
public:
    /**
     * @brief Create the vertex attribute
     * @details The vertex attribute is used to tell OpenGL how to read the data from the buffer
     * uses the following function:
     * void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
     *      GLboolean normalized, GLsizei stride, const GLvoid* pointer);
     *
     * index: The index of the generic vertex attribute to be modified.
     *          This corresponds to the location value specified in the vertex shader.
     * size: The number of components per generic vertex attribute.
     *          This can be 1, 2, 3, or 4.
     * type: The data type of each component in the generic vertex attribute.
     *          This can be one of several enumerated values, such as GL_FLOAT, GL_INT, or GL_UNSIGNED_BYTE.
     * normalized: Specifies whether the generic vertex attribute data should be normalized or not.
     *          If GL_TRUE, the data is normalized before being used in OpenGL operations.
     * stride:  The byte offset between consecutive generic vertex attributes.
     *          This value can be used to specify the layout of the data in the buffer.
     * pointer: A pointer to the first component of the first generic vertex attribute in the buffer.
     *          This value is interpreted as an offset from the beginning of the buffer.
     */
    static void createVertexAttribute(unsigned int index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                      const void *offset);
    
    static void storeDataForVertexBuffer(const std::vector <float> &vertexData);
    
    static void storeDataForElementBuffer(const std::vector <unsigned int> &indices);
    
    /**
     * @brief Bind the vertex array object
     * @param VAO The vertex array object
     */
    static void bindVertexArray(GLuint VAO);
    
    /**
     * @brief Bind the vertex buffer object
     * @param VBO The vertex buffer object
     */
    static void bindVertexBuffer(GLuint VBO);
    
    /**
     * @brief Bind the element buffer object
     * @param EBO The element buffer object
     */
    static void bindElementBuffer(GLuint EBO);
    
    /**
     * @brief Unbind the vertex array object
     */
    static void unbindVertexArray();
    
    /**
     * @brief Unbind the vertex buffer object
     */
    static void unbindVertexBuffer();
    
    /**
     * @brief Unbind the element buffer object
     */
    static void unbindElementBuffer();
    
    static void generateVertexArray(GLuint &VAO);
    
    static void generateVertexBuffer(GLuint &VBO);
    
    static void generateElementBuffer(GLuint &EBO);
    
    static void generateBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO);
    
    static void deleteVertexArray(GLuint &VAO);
    
    static void deleteVertexBuffer(GLuint &VBO);
    
    static void deleteElementBuffer(GLuint &EBO);
    
    static void deleteBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO);
    
    static void drawElements(GLsizei count, const void *indice = nullptr, GLenum type=GL_UNSIGNED_INT,
                             GLenum mode=GL_TRIANGLES);

private:
};
