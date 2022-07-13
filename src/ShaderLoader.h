#include "common.h"
#include <unordered_map>
class ShaderLoader
{
public:
    /**
     * @brief Load and link all the shaders to the shader program
     * 
     */
    void LoadAndLinkAll();
    /**
     * @brief Get the Shader Program ID
     * 
     * @return unsigned int 
     */
    unsigned int getShaderProgramID() { return shaderProgram; }

private:
    /**
     * @brief Soruce of the vertex shader
     * 
     */
    const char *vertexShaderSource =
        R"glsl(
            /* Version of OpenGL */
            #version 430 core
            layout (location = 0) in vec3 aPos;
            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }

        )glsl";
    /**
     * @brief Soruce of the fragment shader
     * 
     */
    const char *fragmentShaderSource =
        R"glsl(
            /* Version of OpenGL */
            #version 430 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }

        )glsl";
    /**
     * @brief ID reference to the vertex shader
     * 
     */
    unsigned int vertexShader;
    /**
     * @brief ID reference to the fragment shader
     * 
     */
    unsigned int fragmentShader;


    void LoadVertexShader();
    void LoadFragmentShader();
    void LinkShaders();
    unsigned int shaderProgram;


    void HandleErrors_CompileShader(unsigned int shaderType);
    void HandleErrors_Linking();

    std::unordered_map<unsigned int, char*> IDNames = {};

    int success;
    char infoLog[512];
    void Clean();

    
};