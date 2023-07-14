ShaderManager::ShaderManager() : success(), infoLog() {
    std::string vertexPath = PROJECT_SOURCE_DIR + std::string(SHADER_PATH) + VERT_SHADER;
    vertexShaderSource = FileManager::readFile(vertexPath);
    Logger::get().success("Shader file read successfully: " + vertexPath);
    
    std::string fragmentPath = PROJECT_SOURCE_DIR + std::string(SHADER_PATH) + FRAG_SHADER;
    fragmentShaderSource = FileManager::readFile(fragmentPath);
    Logger::get().success("Shader file read successfully: " + fragmentPath);
    
    loadVertexShader();
    loadFragmentShader();
    createShaderProgram();
    
    clean();
}

ShaderManager::~ShaderManager() {
    glDeleteProgram(shaderProgram);
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

void ShaderManager::clean() {
    
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

