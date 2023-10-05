/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/core/exceptions/EngineException.h"
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/texture/TextureManager.h"
#include "engine/core/window/WindowManager.h"
#include "engine/res-mng/textures/TextureLoader.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/shaders/ShaderManager.h"
#include "engine/core/math/Matrix.h"

namespace GLESC {
    class Renderer {
    public:
        explicit Renderer(WindowManager &windowManager,
                          GLESC_RENDER_API &graphicsInterface) :
                windowManager(windowManager),
                shaderManager(graphicsInterface),
                textureManager(graphicsInterface),
                graphicsInterface(graphicsInterface) {
            
            // Set the projection matrix
            projection = calculateProjectionMatrix(45.0f, 0.1f, 100.0f,
                                                   (float) windowManager
                                                           .getWidth(),
                                                   (float) windowManager
                                                           .getHeight());
        }
        
        ~Renderer() {
            graphicsInterface.deleteContext();
        }
        
        void start() {
            graphicsInterface.clear(
                    {GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                     GAPIValues::ClearBitsStencil});
            graphicsInterface.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        }
        
        void end() {
            swapBuffers();
        }
        
        void transformMesh(GLESC::Mesh &mesh,
                           const Vector3D &position,
                           const Vector3D &rotation,
                           const Vector3D &scale) {
            Matrix4D transform =
                    calculateTransformMatrix(position, rotation, scale);
            // Apply transformations to vertices
            for (auto &vertex : mesh.getVertices()) {
                Vector4D pos = Vector4D(vertex.getPosition().getX(),
                                        vertex.getPosition().getY(),
                                        vertex.getPosition().getZ(), 1.0f);
                pos = transform * pos;
                Vector3D newPos = Vector3D(pos.getX(), pos.getY(), pos.getZ());
                vertex.setPosition(newPos);
            }
        }
        
        void
        renderMesh(GLESC::Mesh const &mesh) {
            
        }
        
        
        /**
         * @brief Get the shader manager object
         * @return ShaderManager& The shader manager object
         */
        [[nodiscard]] ShaderManager &getShaderManager() {
            return shaderManager;
        }
        
        /**
         * @brief Get the Texture Manager object
         * @return TextureManager& The Texture Manager object
         */
        [[nodiscard]] TextureManager &getTextureManager() {
            return textureManager;
        }
        
        /**
         * @brief Gets the projection matrix
         * @return projection matrix
         */
        [[nodiscard]] glm::mat4 getProjection() const {
            return projection;
        }
        
        /**
         * @brief Gets the view matrix
         * @return view matrix
         */
        [[nodiscard]] glm::mat4 getView() const {
            return view;
        }
        
        /**
         * @brief Sets the projection matrix
         * @param projection projection matrix
         */
        void setProjection(const glm::mat4 &projectionParam) {
            Renderer::projection = projectionParam;
        }
        
        /**
         * @brief Sets the view matrix
         * @param view view matrix
         */
        void setView(const glm::mat4 &viewParam) {
            Renderer::view = viewParam;
        }
        
        /**
         * @brief Creates a projection matrix from a camera component
         * @details uses the perspective function from glm
         * @param camera component
         * @return projection matrix
         */
        static glm::mat4
        calculateProjectionMatrix(float fov,
                                  float nearPlane,
                                  float farPlane,
                                  float viewWidth,
                                  float viewHeight) {
            if (viewHeight == 0.0f)
                throw EngineException(
                        "Unable to make projection matrix: viewHeight is 0");
            if (viewWidth == 0.0f)
                throw EngineException(
                        "Unable to make projection matrix: viewWidth is 0");
            
            float aspectRatio = viewWidth / viewHeight;
            return glm::perspective(glm::radians(fov), aspectRatio, nearPlane,
                                    farPlane);
        }
        
        void swapBuffers() {
            graphicsInterface.getSwapBuffersFunc()(windowManager.getWindow());
        }
        
        /**
         * @brief Creates a view matrix from a transform component of the camera
         * @details uses the lookAt function from glm
         * @param transform component of the camera
         * @return view matrix
         */
        static glm::mat4
        calculateViewMatrix(const glm::vec3 &position,
                            const glm::vec3 &rotation,
                            const glm::vec3 &scale) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
            model = glm::rotate(model, glm::radians(rotation.x),
                                glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation.y),
                                glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation.z),
                                glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, scale);
            return glm::inverse(model);
        }
    
    private:
        
        /**
         * @brief Calculates transform matrix
         * @details Given the position, rotation, and scale, this method
         * calculates the transform matrix
         * @param position The position vector
         * @param rotation The rotation vector
         * @param scale The scale vector
         * @return The model matrix
         */
        static Matrix4D
        calculateTransformMatrix(const Vector3D &position,
                                 const Vector3D &rotation,
                                 const Vector3D &scale) {
            
            Matrix4D model = Matrix4D(1.0).translate(position);
            
            model = model.rotate( rotation.getX(),
                                glm::vec3(1.0f, 0.0f, 0.0f));
            
            model = glm::rotate(model, glm::radians(rotation.y),
                                glm::vec3(0.0f, 1.0f, 0.0f));
            
            model = glm::rotate(model, glm::radians(rotation.z),
                                glm::vec3(0.0f, 0.0f, 1.0f));
            
            model = glm::scale(model, scale);
            return model;
        }
        
        GLESC_RENDER_API &graphicsInterface;
        // Uncomment the below line and comment the above to enable code
        // completion and proper syntax highlighting
        // IGraphicInterface &graphicsInterface;
        /**
         * @brief Window manager
         *
         */
        GLESC::WindowManager &windowManager;
        /**
         * @brief Shader manager
         *
         */
        ShaderManager shaderManager;
        /**
         * @brief Texture manager
         *
         */
        TextureManager textureManager;
        
        /**
         * @brief Projection matrix
         * @details The projection matrix makes the world look like it's in 3D
         * includes field of view, aspect ratio, and near and far planes.
         * Converts global coordinates to normalized device coordinates
         * @see https://learnopengl.com/Getting-started/Coordinate-Systems
         */
        glm::mat4 projection{};
        /**
         * @brief View matrix
         * @details This matrix converts
         * @see https://learnopengl.com/Getting-started/Coordinate-Systems
         */
        glm::mat4 view{};
    }; // class Renderer
    
} // namespace GLESC