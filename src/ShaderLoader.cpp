#include "ShaderLoader.h"

void ShaderLoader::LoadAndLinkAll(){
    LoadVertexShader();
    LoadFragmentShader();
    LinkShaders();
    Clean();
}

void ShaderLoader::LoadVertexShader(){
    /* TODO: The code to load the shader can be factorized*/
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    IDNames.emplace(std::make_pair(vertexShader, "VERTEX"));
    HandleErrors_CompileShader(vertexShader);
}

void ShaderLoader::LoadFragmentShader(){
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    IDNames.emplace(std::make_pair(vertexShader, "FRAGMENT"));
    HandleErrors_CompileShader(vertexShader);
}

void ShaderLoader::LinkShaders(){
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    HandleErrors_Linking();
}
void ShaderLoader::Clean(){
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}



void ShaderLoader::HandleErrors_Linking(){
    /* Check for shader linking errors */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }
}
void ShaderLoader::HandleErrors_CompileShader(unsigned int shaderType){
    /* Check for errors in vertex shader compilation */ 
    glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderType, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"<< IDNames.at(shaderType) <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
