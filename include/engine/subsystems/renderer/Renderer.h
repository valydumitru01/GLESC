/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <map>
#include <memory>

#include <GL/glew.h>
#include "engine/core/asserts/Asserts.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/texture/TextureManager.h"
#include "engine/core/window/WindowManager.h"
#include "engine/res-mng/textures/TextureLoader.h"
#include "engine/subsystems/renderer/math/RenderMath.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/shaders/Shader.h"

namespace GLESC {
    class Renderer {
    public:
        explicit Renderer(WindowManager &windowManager);
        
        ~Renderer();
        
        void clear() {
            getGAPI().clear({GAPI::ClearBits::Color, GAPI::ClearBits::Depth,
                        GAPI::ClearBits::Stencil});
            getGAPI().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        }
        
        
        template<bool isTextured>
        void transformMesh(GLESC::Mesh &mesh,
                           const Vec3D &position,
                           const Vec3D &rotation,
                           const Vec3D &scale){
            Mat4D transform = RenderMath::calculateTransformMatrix(position, rotation, scale);
            // Apply transformations to vertices
            for (auto &vertex : mesh.getVertices()) {
                Vec4D pos = vertex.getPosition().homogenize();
                pos = transform * pos;
                Vec3D newPos = pos.dehomogenize();
                vertex.setPosition(newPos);
            }
        }
        
        void renderMesh(const std::shared_ptr<GLESC::Mesh>& meshPtr) {
            D_ASSERT_NOT_NULLPTR(meshPtr, "Mesh pointer is null");
            
            GLESC::Mesh& mesh = *meshPtr;
            
            if (mesh.isDirty()) {
                setupMesh(mesh);
                mesh.setClean();
            }
            
            auto found = VAOs.find(meshPtr);
            if (found != VAOs.end()) {
                found->second->bind();
                getGAPI().drawTrianglesIndexed(mesh.getIndices().size());
            }
            // handle the case where the mesh is not found in VAOs
            else {
                VAOs[meshPtr] = nullptr;
            }
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
        
        
        
        void swapBuffers() {
            getGAPI().swapBuffers(windowManager.getWindow());
        }
        
        
    
    private:
        using MeshPtr = std::shared_ptr<Mesh>;
        using VertexArrayPtr = std::shared_ptr<VertexArray>;
        
        // Map from Mesh pointer to VertexArray pointer
        std::unordered_map<MeshPtr, VertexArrayPtr> VAOs;
        void setupMesh(const Mesh& mesh) {/*
            using Vertex = Vertex;
            VertexArray vertexArray;
            VertexBuffer vertexBuffer(mesh.getVertices().data(),
                                      mesh.getVertices().size() * sizeof(Vertex));
            IndexBuffer indexBuffer(mesh.getIndices().size() * sizeof(unsigned int),
                                    mesh.getIndices().data());
            
            VertexBufferLayout layout;
            layout.push(GAPI::Types::Vec3F);
            layout.push(GAPI::Types::Vec3F);
            layout.push(GAPI::Types::Vec2F);
            vertexArray.addBuffer(vertexBuffer, layout);
            
            VAOs[&mesh] = vertexArray;*/
        }
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