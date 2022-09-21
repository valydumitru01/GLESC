#include "ShaderManager.h"


ShaderManager::~ShaderManager(){
    glDeleteProgram(shaderProgram);
}
void ShaderManager::LoadAndLinkAll()
{
    LoadVertexShader();
    LoadFragmentShader();
    LinkShaders();
    clean();
}
void ShaderManager::LoadVertexShader()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    IDNames.emplace(std::make_pair(vertexShader, "VERTEX"));
    HandleErrors_CompileShader(vertexShader);
}

void ShaderManager::LoadFragmentShader()
{
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    IDNames.emplace(std::make_pair(fragmentShader, "FRAGMENT"));
    HandleErrors_CompileShader(fragmentShader);
}

void ShaderManager::LinkShaders()
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    HandleErrors_Linking();
}

void ShaderManager::clean()
{
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderManager::HandleErrors_Linking()
{
    /* Check for shader linking errors */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
}
void ShaderManager::HandleErrors_CompileShader(unsigned int shaderType)
{
    /* Check for errors in vertex shader compilation */
    glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderType, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::" << IDNames.at(shaderType) << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
}






//------------------------------Uniform Setters-----------------------------
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
void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void ShaderManager::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}
void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void ShaderManager::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}
void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}
void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderManager::useShaderProgram()
{
    glUseProgram(shaderProgram);
}