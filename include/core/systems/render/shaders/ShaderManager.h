#pragma once
#define SHADER_PATH "core/systems/render/shaders/"
#define VERT_SHADER "VertexShader.vert"
#define FRAG_SHADER "FragmentShader.frag"


#include <iostream>
#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "core/systems/render/RenderSystem.h"


class ShaderManager {
public:
	ShaderManager();

	~ShaderManager();

	/**
	 * @brief Load and link all the shaders to the shader program
	 *
	 */
	void loadAndLinkShaders();

	/**
	 * @brief Get the Shader Program ID
	 *
	 * @return unsigned int
	 */
	unsigned int getShaderProgram() { return shaderProgram; }

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
	 * @brief Change vec2 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param value The new glm::vec2 value
	 */
	void setVec2(const std::string &name, const glm::vec2 &value) const;

	/**
	 * @brief Change vec2 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param x The new x value of vec2
	 * @param y The new y value of vec2
	 */
	void setVec2(const std::string &name, float x, float y) const;

	/**
	 * @brief Change vec3 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param value The new glm::vec3 value
	 */
	void setVec3(const std::string &name, const glm::vec3 &value) const;

	/**
	 * @brief Change vec3 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param x The new x value of vec3
	 * @param y The new y value of vec3
	 * @param z The new z value of vec3
	 */
	void setVec3(const std::string &name, float x, float y, float z) const;

	/**
	 * @brief Change vec4 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param value The new glm::vec4 value
	 */
	void setVec4(const std::string &name, const glm::vec4 &value) const;

	/**
	 * @brief Change vec4 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param x The new x value of vec4
	 * @param y The new y value of vec4
	 * @param z The new z value of vec4
	 * @param w The new w value of vec4
	 */
	void setVec4(const std::string &name, float x, float y, float z, float w) const;

	/**
	 * @brief Change mat2 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param mat The new glm::mat2 value
	 */
	void setMat2(const std::string &name, const glm::mat2 &mat) const;

	/**
	 * @brief Change mat3 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param mat The new glm::mat3 value
	 */
	void setMat3(const std::string &name, const glm::mat3 &mat) const;

	/**
	 * @brief Change mat4 value of Uniform by name
	 *
	 * @param name Name of the Uniform
	 * @param mat The new glm::mat4 value
	 */
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

	/**
	 * @brief Calls to useProgram with the shader program ID
	 *
	 */
	void useShaderProgram() const;

	const GLchar *getGlslVersion() { return glslVersion; };
private:
	const char *glslVersion = "#version 430";

	/**
	 * @brief Reads the content of file and returns it as a GLchar*
	 * @param pathToFile
	 */
	static GLchar *readContentFromFile(const std::string &pathToFile);

	/**
	 * @brief Source of the vertex shader
	 *
	 */
	const GLChar *vertexShaderSource;
	/**
	 * @brief Source of the fragment shader
	 *
	 */
	const GLChar *fragmentShaderSource;
	/**
	 * @brief ID reference to the vertex shader
	 *
	 */
	GLuint vertexShader;
	/**
	 * @brief ID reference to the fragment shader
	 *
	 */
	GLuint fragmentShader;

	/**
	 * @brief Loads the vertex shader
	 * Sets the actual coordinates of the vertices in the GPU
	 */
	GLuint loadVertexShader();

	/**
	 * @brief Loads the fragment shader
	 * Calculates colors of pixels (a fragment is a pixel in OpenGL)
	 */
	GLuint loadFragmentShader();

	/**
	 * @brief Links the loaded shaders into the shader program
	 *
	 */
	GLuint createShaderProgram();

	/**
	 * @brief ID reference to the shader program
	 *
	 */
	GLuint shaderProgram;

	/**
	 * @brief Handle shader compilation errors
	 *
	 * @param shaderType ID reference of the shader
	 */
	void handleErrorsCompilation(unsigned int shaderType);

	/**
	 * @brief Handle shader linking into the shader program
	 *
	 */
	void handleErrorsLinking();

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
	GLint success;
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
	void clean() const;
};