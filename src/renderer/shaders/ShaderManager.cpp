#include "renderer/shaders/ShaderManager.h"


ShaderManager::ShaderManager() :
        success(),
        infoLog() {
    vertexShaderSource = readContentFromFile(PROJECT_SOURCE_DIR + std::string(SHADER_PATH) + VERT_SHADER);
    fragmentShaderSource = readContentFromFile(PROJECT_SOURCE_DIR + std::string(SHADER_PATH).append(std::string(FRAG_SHADER)));
    
    vertexShader = loadVertexShader();
    fragmentShader = loadFragmentShader();
    shaderProgram = createShaderProgram();
    
    clean();
}

ShaderManager::~ShaderManager() {
    glDeleteProgram(shaderProgram);
}

std::string ShaderManager::readContentFromFile(const std::string &filePath) {
    std::ifstream fileStream(filePath);
    
    if (!fileStream.is_open()) {
        // Handle the error (for example, throw an exception or return an empty string)
        std::cerr << "Error: Could not open the file: " << filePath << std::endl;
        return "";
    }
    
    std::stringstream contentStream;
    contentStream << fileStream.rdbuf();
    fileStream.close();
    
    Console::success("Shader file read successfully: " + filePath);
    return contentStream.str();
}

GLuint ShaderManager::loadVertexShader() {
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *source = vertexShaderSource.c_str();
    
    glShaderSource(vertex, 1, &source, nullptr);
    glCompileShader(vertex);
    IDNames.emplace(vertex, "VERTEX");
    handleErrorsCompilation(vertex);
    return vertex;
}

GLuint ShaderManager::loadFragmentShader() {
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
    const GLchar *source = fragmentShaderSource.c_str();
    
    glShaderSource(fragment, 1, &source, nullptr);
    glCompileShader(fragment);
    IDNames.emplace(fragment, "FRAGMENT");
    handleErrorsCompilation(fragment);
    
    return fragment;
}

GLuint ShaderManager::createShaderProgram() {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    handleErrorsLinking();
    return program;
}

void ShaderManager::clean() const {
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderManager::handleErrorsLinking() {
    /* Check for shader linking errors */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderManager::handleErrorsCompilation(unsigned int shaderType) {
    /* Check for errors in vertex shader compilation */
    glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderType, 512, nullptr, infoLog);
        std::cout << "\nERROR::SHADER::" << IDNames.at(shaderType) << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


//------------------------------Uniform Setters-----------------------------
void ShaderManager::setBool(const std::string &name, bool value) const {
    /**
     * @brief We get the Uniform by name with glGetUniformLocation and then we change the value with glUniform1i
     * Only for 1 value (not vectors)
     */
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
    glCheckError();
}

void ShaderManager::setInt(const std::string &name, int value) const {
    /**
     * @brief We get the Uniform by name with glGetUniformLocation and then we change the value with glUniform1i
     * (casting the bool value) Only for 1 value (not vectors)
     */
    
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    glCheckError();
}

void ShaderManager::setFloat(const std::string &name, float value) const {
    /**
     * @brief We get the Uniform by name with glGetUniformLocation and then we change the value with glUniform1f
     * Only for 1 value (not vectors)
     */
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    glCheckError();
}

void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    glCheckError();
}

void ShaderManager::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
    glCheckError();
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    glCheckError();
}

void ShaderManager::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
    glCheckError();
}

void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    glCheckError();
}

void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
    glCheckError();
}

void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    glCheckError();
}

void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    glCheckError();
}

void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    glCheckError();
}

void ShaderManager::use() const {
    glUseProgram(shaderProgram);
    glCheckError();
}

