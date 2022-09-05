#include "common.h"
#include <unordered_map>
class ShaderManager
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
    /**
     * @brief Change boolean value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new boolean value
     */
    void setBool(const std::string &name, bool value) const;
    /**
     * @brief Change int value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new int value
     */
    void setInt(const std::string &name, int value) const;
    /**
     * @brief Change float value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new float value
     */
    void setFloat(const std::string &name, float value) const;

    /**
     * @brief Calls to useProgram with the shader program ID
     *
     */
    void use();

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
            layout (location = 1) in vec3 aColor;
            layout (location = 2) in vec2 aTexCoord;

            out vec3 ourColor;
            out vec2 TexCoord;
            
            uniform mat4 transform;

            void main()
            {
                gl_Position = transform * vec4(aPos, 1.0f);

                ourColor = aColor;
                TexCoord = vec2(aTexCoord.x, aTexCoord.y);
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

            in vec3 ourColor;
            in vec2 TexCoord;

            // texture sampler
            uniform sampler2D texture1;
            uniform sampler2D texture2;

            void main()
            {
                FragColor = mix(texture(texture1, TexCoord), texture(texture2,TexCoord),0.2);
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

    /**
     * @brief Loads the vertex shader
     * Sets the actual coordinates of the vertices in the GPU
     */
    void LoadVertexShader();
    /**
     * @brief Loads the fragment shader
     * Calculates colors of pixels (a fragment is a pixel in OpenGL)
     */
    void LoadFragmentShader();
    /**
     * @brief Links the loaded shaders into the shader program
     *
     */
    void LinkShaders();
    /**
     * @brief ID reference to the shader program
     *
     */
    unsigned int shaderProgram;

    /**
     * @brief Handle shader compilation errors
     *
     * @param shaderType ID reference of the shader
     */
    void HandleErrors_CompileShader(unsigned int shaderType);
    /**
     * @brief Handle shader linking into the shader program
     *
     */
    void HandleErrors_Linking();

    /**
     * @brief Map of names of the shaders and their IDs
     * Once the shader is created, we assign the name to the ID
     * This is used to identify the shader in case of handling an error
     *
     */
    std::unordered_map<unsigned int, const char *> IDNames;

    /**
     * @brief If there is no errors, success != 0
     *
     */
    int success;
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
    void Clean();
};