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
            /* We declarse the layout of the vertices. 
            We must indicate the information that a vertix stores, in our case it will only be position (aPos) 
            For each attribute, we must specify the index of the attribute, in this case 0
            */
            layout (location = 0) in vec3 aPos;     // the position variable has attribute position 0
            layout (location = 1) in vec3 aColor;   // the color variable has attribute position 1
            uniform vec3 offset;
            out vec3 ourColor; // output a color to the fragment shader

            void main()
            {
                /* Actual position of the vertix inside the GPU.
                There is no processing. */ 
                gl_Position = vec4(aPos.x + offset.x,aPos.y + offset.y,aPos.z + offset.z, 1.0);
                ourColor = aPos; // set ourColor to the input color we got from the vertex data

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

            in vec3 ourColor;
            uniform vec3 colorOffset;
            /* Output of the shader, should always be vec4 because the fragment shader always returns an array of colors*/
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(ourColor.x +colorOffset.x,ourColor.y +colorOffset.y,ourColor.z +colorOffset.z, 1.0f);
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
     * @param shaderType - ID reference of the shader
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
    std::unordered_map<unsigned int, const char*> IDNames;

    /**
     * @brief If there is no errors, success != 0
     * 
     */
    int success;
    /**
     * @brief Error message is stored here
     * 
     */
    char infoLog[512];
    /**
     * @brief Clean the shader loader
     * Once the shaders are linked, they can be cleared as they are 
     * no longer needed. 
     */
    void Clean();

    
};