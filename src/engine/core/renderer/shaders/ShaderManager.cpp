#include "engine/renderer/shaders/ShaderManager.h"


ShaderManager::ShaderManager() : success(), infoLog() {
    vertexShaderSource = readContentFromFile(PROJECT_SOURCE_DIR + std::string(SHADER_PATH) + VERT_SHADER);
    fragmentShaderSource =
            readContentFromFile(PROJECT_SOURCE_DIR + std::string(SHADER_PATH).append(std::string(FRAG_SHADER)));
    
    loadVertexShader();
    loadFragmentShader();
    createShaderProgram();
    
    clean();
}

ShaderManager::~ShaderManager() {
    glDeleteProgram(shaderProgram);
}

std::string ShaderManager::readContentFromFile(const std::string &filePath) {
    std::ifstream fileStream(filePath);
    
    if (!fileStream.is_open()) {
        // Handle the error (for example, throw an exception or return an empty string)
        throw RenderException("Could not open the file: " + filePath);
    }
    
    std::stringstream contentStream;
    contentStream << fileStream.rdbuf();
    fileStream.close();
    
    Logger::get().success("Shader file read successfully: " + filePath);
    return contentStream.str();
}

void ShaderManager::loadVertexShader() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *source = vertexShaderSource.c_str();
    
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);
    IDNames.emplace(vertexShader, "VERTEX");
    handleErrorsCompilation(vertexShader);
}

void ShaderManager::loadFragmentShader() {
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const GLchar *source = fragmentShaderSource.c_str();
    
    glShaderSource(fragmentShader, 1, &source, nullptr);
    glCompileShader(fragmentShader);
    IDNames.emplace(fragmentShader, "FRAGMENT");
    handleErrorsCompilation(fragmentShader);

}

void ShaderManager::createShaderProgram() {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    handleErrorsLinking();
}

void ShaderManager::clean() const {
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderManager::handleErrorsLinking() {
    /* Check for shader linking errors */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        throw RenderException("ERROR::SHADER::LINKING_FAILED\n" + std::string(infoLog));
    }
}

void ShaderManager::handleErrorsCompilation(unsigned int shaderType) {
    /* Check for errors in vertex shader compilation */
    glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderType, 512, nullptr, infoLog);
        throw RenderException(
                "ERROR::SHADER::" + std::string(IDNames.at(shaderType)) + "::COMPILATION_FAILED\n" + infoLog);
    }
}


//------------------------------Uniform Setters-----------------------------
void ShaderManager::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
}

void ShaderManager::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderManager::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    
}

void ShaderManager::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
    
}

void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    
}

void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
    
}

void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    
}

void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    
}

void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    
}

void ShaderManager::use() const {
    glUseProgram(shaderProgram);
    
}

