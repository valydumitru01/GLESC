/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "engine/core/exceptions/EngineException.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/texture/TextureManager.h"
#include "engine/core/window/WindowManager.h"
#include "engine/res-mng/textures/TextureLoader.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "engine/core/math/Matrix.h"

namespace GLESC {
    class Renderer {
    public:
        explicit Renderer(WindowManager &windowManager) :
                windowManager(windowManager), shader(Shader("Shader.glsl")) {
            
            // Set the projection matrix
            projection = calculateProjectionMatrix(45.0f, 0.1f, 100.0f,
                                                   static_cast<float>(windowManager
                                                           .getWindowSize().width),
                                                   static_cast<float>(windowManager
                                                           .getWindowSize().height));
        }
        
        ~Renderer() {
            gapi.deleteContext();
        }
        
        void start() {
            gapi.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                        GAPIValues::ClearBitsStencil});
            gapi.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        }
        
        void end() {
            swapBuffers();
        }
        
        void transformMesh(GLESC::Mesh &mesh,
                           const Vec3D &position,
                           const Vec3D &rotation,
                           const Vec3D &scale) {
            Mat4D transform = calculateTransformMatrix(position, rotation, scale);
            // Apply transformations to vertices
            for (auto &vertex : mesh.getVertices()) {
                Vec4D pos = vertex.getPosition().homogenize();
                pos = transform * pos;
                Vec3D newPos = pos.dehomogenize();
                vertex.setPosition(newPos);
            }
        }
        
        void renderMesh(GLESC::Mesh const &mesh) {
            
        }
        
        GLESC::Shader &getDefaultShader() {
            return shader;
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
        [[nodiscard]] Mat4D getProjection() const {
            return projection;
        }
        
        /**
         * @brief Gets the view matrix
         * @return view matrix
         */
        [[nodiscard]] Mat4D getView() const {
            return view;
        }
        
        /**
         * @brief Sets the projection matrix
         * @param projection projection matrix
         */
        void setProjection(const Mat4D &projectionParam) {
            Renderer::projection = projectionParam;
        }
        
        /**
         * @brief Sets the view matrix
         * @param view view matrix
         */
        void setView(const Mat4D &viewParam) {
            Renderer::view = viewParam;
        }
        
        /**
         * @brief Creates a projection matrix from a camera component
         * @details uses the perspective function from glm
         * @param camera component
         * @return projection matrix
         */
        static Mat4D calculateProjectionMatrix(float fov,
                                               float nearPlane,
                                               float farPlane,
                                               float viewWidth,
                                               float viewHeight) {
            if (viewHeight == 0.0f)
                throw EngineException("Unable to make projection matrix: viewHeight is 0");
            if (viewWidth == 0.0f)
                throw EngineException("Unable to make projection matrix: viewWidth is 0");
            
            float aspectRatio = viewWidth / viewHeight;
            return GLESC::Math::perspective(GLESC::Math::radians(fov), aspectRatio, nearPlane,
                                            farPlane);
        }
        
        void swapBuffers() {
            gapi.swapBuffers(windowManager.getWindow());
        }
        
        /**
         * @brief Creates a view matrix from a transform component of the camera
         * @details uses the lookAt function from glm
         * @param transform component of the camera
         * @return view matrix
         */
        static Mat4D
        calculateViewMatrix(const Vec3D &position, const Vec3D &rotation, const Vec3D &scale) {
            Mat4D model = calculateTransformMatrix(position, rotation, scale);
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
        static Mat4D
        calculateTransformMatrix(const Vec3D &position, const Vec3D &rotation, const Vec3D &scale) {
            
            Mat4D model = Mat4D(1.0).translate(position);
            
            model = model.rotate(rotation);
            
            model = model.scale(scale);
            
            return model;
        }
        // Uncomment the below line and comment the above to enable code
        // completion and proper syntax highlighting
        // IGraphicInterface &gapi;
        /**
         * @brief Window manager
         *
         */
        GLESC::WindowManager &windowManager;
        /**
         * @brief Texture manager
         *
         */
        TextureManager textureManager;
        
        GLESC::Shader shader;
        
        /**
         * @brief Projection matrix
         * @details The projection matrix makes the world look like it's in 3D
         * includes field of view, aspect ratio, and near and far planes.
         * Converts global coordinates to normalized device coordinates
         * @see https://learnopengl.com/Getting-started/Coordinate-Systems
         */
        Mat4D projection{};
        /**
         * @brief View matrix
         * @details This matrix converts
         * @see https://learnopengl.com/Getting-started/Coordinate-Systems
         */
        Mat4D view{};
        
    };// class Renderer
    
} // namespace GLESC