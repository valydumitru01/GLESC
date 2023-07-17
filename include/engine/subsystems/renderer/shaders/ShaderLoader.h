#pragma once
#define SHADER_PATH "/src/renderer/shaders/"
#define VERT_SHADER "VertexShader.vert"
#define FRAG_SHADER "FragmentShader.frag"

class ShaderLoader {
public:
private:
    const char *glslVersion = "#version 430";
    /**
     * @brief Source of the vertex shader
     *
     */
    std::string vertexShaderSource;
    /**
     * @brief Source of the fragment shader
     *
     */
    std::string fragmentShaderSource;
    /**
     * @brief ID reference to the vertex shader
     *
     */
    GLuint vertexShader;
    /**
     * @brief ID reference to the fragment shader
     *
     */
    GLuint fragmentShader;
    
    /**
     * @brief Loads the vertex shader
     * Sets the actual coordinates of the vertices in the GPU
     */
    void loadVertexShader();
    
    /**
     * @brief Loads the fragment shader
     * Calculates colors of pixels (a fragment is a pixel in OpenGL)
     */
    void loadFragmentShader();
    
    /**
     * @brief Links the loaded shaders into the shader program
     *
     */
    void createShaderProgram();
    
    /**
     * @brief ID reference to the shader program
     *
     */
    static GLuint shaderProgram;
    
    /**
     * @brief Handle shader compilation errors
     *
     * @param shaderType ID reference of the shader
     */
    void handleErrorsCompilation(unsigned int shaderType);
    
    /**
     * @brief Handle shader linking into the shader program
     *
     */
    void handleErrorsLinking();
    
    /**
     * @brief Map of names of the shaders and their IDs
     * Once the shader is created, we assign the name to the ID
     * This is used to identify the shader in case of handling an error
     *
     */
    std::unordered_map <unsigned int, const char *> IDNames;
    
    /**
     * @brief If there is no errors, success != 0
     *
     */
    GLint success;
    /**
     * @brief Error message is stored here
     *
     */
    GLchar infoLog[512];
    
    /**
     * @brief Clean the shader loader
     * Once the shaders are linked, they can be cleared as they are
     * no longer needed.
     */
    void clean() const;
};
