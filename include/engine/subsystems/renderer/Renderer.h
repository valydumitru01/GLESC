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
        explicit Renderer(WindowManager &windowManager, GLESC_RENDER_API &graphicsInterface) :
                graphicsInterface(graphicsInterface), windowManager(windowManager), shaderManager(
                graphicsInterface), textureManager(graphicsInterface) {
            
            // Set the projection matrix
            projection = calculateProjectionMatrix(45.0f, 0.1f, 100.0f,
                                                   static_cast<float>(windowManager.getWidth()),
                                                   static_cast<float>( windowManager.getHeight()));
        }
        
        ~Renderer() {
            graphicsInterface.deleteContext();
        }
        
        void start() {
            graphicsInterface.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                                     GAPIValues::ClearBitsStencil});
            graphicsInterface.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        }
        
        void end() {
            swapBuffers();
        }
        
        void transformMesh(GLESC::Mesh &mesh,
                           const Vec3D &position,
                           const Vec3D &rotation,
                           const Vec3D &scale) {
            Matrix4D transform = calculateTransformMatrix(position, rotation, scale);
            // Apply transformations to vertices
            for (auto &vertex : mesh.getVertices()) {
                Vec4D pos = Vec4D(vertex.getPosition().x(), vertex.getPosition().y(),
                                  vertex.getPosition().z(), 1.0f);
                pos = transform * pos;
                Vec3D newPos = Vec3D(pos.x(), pos.y(), pos.z());
                vertex.setPosition(newPos);
            }
        }
        
        void renderMesh(GLESC::Mesh const &mesh) {
            
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
        [[nodiscard]] Matrix4D getProjection() const {
            return projection;
        }
        
        /**
         * @brief Gets the view matrix
         * @return view matrix
         */
        [[nodiscard]] Matrix4D getView() const {
            return view;
        }
        
        /**
         * @brief Sets the projection matrix
         * @param projection projection matrix
         */
        void setProjection(const Matrix4D &projectionParam) {
            Renderer::projection = projectionParam;
        }
        
        /**
         * @brief Sets the view matrix
         * @param view view matrix
         */
        void setView(const Matrix4D &viewParam) {
            Renderer::view = viewParam;
        }
        
        /**
         * @brief Creates a projection matrix from a camera component
         * @details uses the perspective function from glm
         * @param camera component
         * @return projection matrix
         */
        static Matrix4D calculateProjectionMatrix(float fov,
                                                  float nearPlane,
                                                  float farPlane,
                                                  float viewWidth,
                                                  float viewHeight) {
            if (viewHeight == 0.0f)
                throw EngineException("Unable to make projection matrix: viewHeight is 0");
            if (viewWidth == 0.0f)
                throw EngineException("Unable to make projection matrix: viewWidth is 0");
            
            float aspectRatio = viewWidth / viewHeight;
            return GLESC::Math::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
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
        static Matrix4D
        calculateViewMatrix(const Vec3D &position, const Vec3D &rotation, const Vec3D &scale) {
            Matrix4D model = calculateTransformMatrix(position, rotation, scale);
            return model.inverse();
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
        calculateTransformMatrix(const Vec3D &position, const Vec3D &rotation, const Vec3D &scale) {
            
            Matrix4D model = Matrix4D(1.0).translate(position);
            
            model = model.rotate(rotation);
            
            model = model.scale(scale);
            
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
        Matrix4D projection{};
        /**
         * @brief View matrix
         * @details This matrix converts
         * @see https://learnopengl.com/Getting-started/Coordinate-Systems
         */
        Matrix4D view{};
    }; // class Renderer
    
} // namespace GLESC