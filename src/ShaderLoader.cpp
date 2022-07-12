#include "ShaderLoader.h"

void ShaderLoader::LoadAndLinkAll(){
    LoadVertexShader();
    LoadFragmentShader();
    LinkShaders();
    Clean();
}

void ShaderLoader::LoadVertexShader(){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    HandleErrors_VertexShader();
}
void ShaderLoader::HandleErrors_VertexShader(){
    /* Check for errors in vertex shader compilation */ 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


void ShaderLoader::LoadFragmentShader(){
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    HandleErrors_FragmentShader();
}
void ShaderLoader::HandleErrors_FragmentShader(){
    /* Check for errors in fragment shader compilation */ 
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


void ShaderLoader::HandleErrors_Linking(){
    /* Check for shader linking errors */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }
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
