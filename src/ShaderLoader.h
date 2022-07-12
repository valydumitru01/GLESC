#include "common.h"
class ShaderLoader
{
public:
    void LoadAndLinkAll();
    unsigned int getShaderProgramID() { return shaderProgram; }

private:
    const char *vertexShaderSource =
        R"glsl(

            #version 430 core
            layout (location = 0) in vec3 aPos;\n
            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }

        )glsl";

    const char *fragmentShaderSource =
        R"glsl(

            #version 430 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }

        )glsl";

    unsigned int vertexShader;
    unsigned int fragmentShader;


    void LoadVertexShader();
    void LoadFragmentShader();
    void LinkShaders();
    unsigned int shaderProgram;


    void HandleErrors_VertexShader();
    void HandleErrors_FragmentShader();
    void HandleErrors_Linking();
    int success;
    char infoLog[512];


    void Clean();

    
};