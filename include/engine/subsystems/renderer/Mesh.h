#include <vector>
#include "Renderer.h"

struct VertexAttribute {
    unsigned int location;
    int size;
    GLsizei offset;
};

class Mesh {
    friend class RenderSystem;

public:
    Mesh() = default;
    
    Mesh(const std::vector <float> &vertices, const std::vector <unsigned int> &indices,
         const std::vector <VertexAttribute> &attributes);
    
    void create(const std::vector <float> &vertices, const std::vector <unsigned int> &indices,
                const std::vector <VertexAttribute> &attributes);
    
    static void createVertexAttributes(const std::vector <VertexAttribute> &vertexAttributes);
    
    void destroy();
    
    void addVertexData(const std::vector <float> &vertexDataParam);
    
    [[nodiscard]] size_t getIndexCount() const { return indexCount; }

private:
    /**
     * @brief The vertex array object
     * Contains the information a vertex stores
     */
    GLuint VAO;
    /**
     * @brief The vertex buffer object
     * Contains the vertices of the object
     */
    GLuint VBO;
    /**
     * @brief The element buffer object
     * Contains the indices of the vertices
     */
    GLuint EBO;
    /**
     * @brief The number of indices
     * @details The number of indices is equal to the number of vertices if the vertices are not shared
     * (if the vertices are shared, the number of indices is smaller than the number of vertices)
     * The indices are used to draw the vertices in the correct order
     * The indices are stored in the EBO
     */
    size_t indexCount;
    /**
     * @brief The vertex data
     * Contains different information about the vertices (position, normal, texture coordinates, ...)
     * depending on the components attached to the entity
     */
    std::vector <float> vertexData;
    std::vector <unsigned int> indexData;
    
    
};