#include "ShaderManager.h"

void ShaderManager::LoadAndLinkAll(){
    LoadVertexShader();
    LoadFragmentShader();
    LinkShaders();
    Clean();
}

void ShaderManager::LoadVertexShader(){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    IDNames.emplace(std::make_pair(vertexShader, "VERTEX"));
    HandleErrors_CompileShader(vertexShader);
}

void ShaderManager::LoadFragmentShader(){
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    IDNames.emplace(std::make_pair(vertexShader, "FRAGMENT"));
    HandleErrors_CompileShader(vertexShader);
}

void ShaderManager::LinkShaders(){
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    HandleErrors_Linking();
}
void ShaderManager::Clean(){
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}



void ShaderManager::HandleErrors_Linking(){
    /* Check for shader linking errors */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }
}
void ShaderManager::HandleErrors_CompileShader(unsigned int shaderType){
    /* Check for errors in vertex shader compilation */ 
    glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderType, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"<< IDNames.at(shaderType) <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
void ShaderManager::setBool(const std::string &name, bool value) const
{
    /**
     * @brief We get the Uniform by name with glGetUniformLocation and then we change the value with glUniform1i
     * Only for 1 value (not vectors)
     */
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}
void ShaderManager::setInt(const std::string &name, int value) const
{
    /**
     * @brief We get the Uniform by name with glGetUniformLocation and then we change the value with glUniform1i (casting the bool value)
     * Only for 1 value (not vectors)
     */
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}
void ShaderManager::setFloat(const std::string &name, float value) const
{
    /**
     * @brief We get the Uniform by name with glGetUniformLocation and then we change the value with glUniform1f
     * Only for 1 value (not vectors)
     */
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void ShaderManager::use() 
{ 
    glUseProgram(shaderProgram);
}  