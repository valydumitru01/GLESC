#pragma once

#include <memory>
#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "TextureManager.h"
#include "RenderDebugger.h"

#include "engine/core/renderer/shaders/ShaderManager.h"
#include "engine/plat-independence/window/WindowManager.h"
#include "engine/exceptions/EngineException.h"
#include "engine/plat-independence/graphics-device-interface/GraphicsInterface.h"

#include "GlApi.h"
#include "Mesh.h"


class Renderer {
public:
    explicit Renderer(const std::shared_ptr <WindowManager> &windowManager,
                      const std::shared_ptr <GraphicsInterface> &graphicsInterface);
    
    ~Renderer();
    
    
    void renderMesh(Mesh &mesh, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    
    /**
     * @brief Get the shader manager object
     * @return ShaderManager& The shader manager object
     */
    [[nodiscard]] ShaderManager &getShaderManager();
    
    /**
     * @brief Get the Window Manager object
     * @return WindowManager& The Window Manager object
     */
    [[nodiscard]] shared_ptr <WindowManager> &getWindowManager();
    
    /**
     * @brief Get the Texture Manager object
     * @return TextureManager& The Texture Manager object
     */
    [[nodiscard]] TextureManager &getTextureManager();
    
    
    [[nodiscard]] SDL_GLContext &getContext();
    
    /**
     * @brief Gets the projection matrix
     * @return projection matrix
     */
    [[nodiscard]] glm::mat4 getProjection() const;
    
    /**
     * @brief Gets the view matrix
     * @return view matrix
     */
    [[nodiscard]] glm::mat4 getView() const;
    
    /**
     * @brief Sets the projection matrix
     * @param projection projection matrix
     */
    void setProjection(const glm::mat4 &projection);
    
    /**
     * @brief Sets the view matrix
     * @param view view matrix
     */
    void setView(const glm::mat4 &view);
    
    /**
     * @brief Creates a projection matrix from a camera component
     * @details uses the perspective function from glm
     * @param camera component
     * @return projection matrix
     */
    static glm::mat4
    makeProjectionMatrix(float fov, float nearPlane, float farPlane, float viewWidth, float viewHeight);
    
    /**
     * @brief Creates a view matrix from a transform component of the camera
     * @details uses the lookAt function from glm
     * @param transform component of the camera
     * @return view matrix
     */
    static glm::mat4 makeViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    
    /**
     * @brief Calculate the model matrix for a given position, rotation, and scale
     * @details Given the position, rotation, and scale, this method calculates the model matrix
     * @param position The position vector
     * @param rotation The rotation vector
     * @param scale The scale vector
     * @return The model matrix
     */
    static glm::mat4 calculateModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

private:
    /**
     * @brief Shader manager
     *
     */
    unique_ptr <ShaderManager> shaderManager;
    /**
     * @brief Window manager
     *
     */
    shared_ptr <WindowManager> windowManager;
    /**
     * @brief Texture manager
     *
     */
    TextureManager textureManager;
    /**
     * @brief Render debugger
     *
     */
    RenderDebugger debugger;
    /**
     * @brief OpenGL context
     *
     */
    SDL_GLContext context;
    
    /**
     * @brief Projection matrix
     * @details The projection matrix makes the world look like it's in 3D
     * includes field of view, aspect ratio, and near and far planes. Converts global
     * coordinates to normalized device coordinates
     * @see https://learnopengl.com/Getting-started/Coordinate-Systems
     */
    glm::mat4 projection;
    /**
     * @brief View matrix
     * @details This matrix converts
     * @see https://learnopengl.com/Getting-started/Coordinate-Systems
     */
    glm::mat4 view;
};