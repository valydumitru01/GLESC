/**************************************************************************************************
 * @file   Renderer.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once


#include <mutex>

#include "engine/core/counter/Counter.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "engine/core/window/WindowManager.h"

#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/Skybox.h"
#include "engine/subsystems/renderer/camera/CameraPerspective.h"
#include "engine/subsystems/renderer/fog/Fog.h"
#include "engine/subsystems/renderer/lighting/GlobalAmbientLight.h"
#include "engine/subsystems/renderer/lighting/GlobalSun.h"
#include "engine/subsystems/renderer/lighting/LightPoint.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/math/Frustum.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/Transform.h"

class MeshRenderingTest;

namespace GLESC {
    class Engine;
}

namespace GLESC::Render {
    /**
     * @brief This is the render engine of the game engine. It is resposable of sending the data to the GPU and render
     * it.
     *
     * @details The public methods are the update side of the renderer (with some exceptions).
     * It must be executed in the update loop of the engine.
     * While the private methods are the render side of the renderer. It must be executed in the render loop of the
     * engine.
     */
    class Renderer {
        friend class GLESC::Engine;
        friend class ::MeshRenderingTest;

        struct Camera {
            const CameraPerspective* camera = nullptr;
            const Transform::Transform* transform = nullptr;
        };

        struct Sun {
            const GlobalSun* sun = nullptr;
            const GlobalAmbientLight* ambientLight = nullptr;
            const Transform::Transform* transform = nullptr;
        };

        struct FogData {
            const Fog* fog = nullptr;
            const Transform::Transform* transform = nullptr;
        };

    public:
        explicit Renderer(WindowManager& windowManager);
        ~Renderer();

        [[nodiscard]] const View& getView() const { return view; }
        void setView(const View& viewParam) { this->view = viewParam; }

        [[nodiscard]] const Projection& getProjection() const { return projection; }
        void setProjection(const Projection& projectionParam) { this->projection = projectionParam; }

        [[nodiscard]] const VP& getViewProjection() const { return viewProjection; }
        bool hasRenderBeenCalledThisFrame() const { return hasRenderBeenCalled; }
        void setRendererUpdated() { hasRenderBeenCalled = false; }

        [[nodiscard]] WindowDimensions getViewportSize() const { return windowManager.getSize(); }
        [[nodiscard]] Camera getCamera() const { return this->camera; }


        [[nodiscard]] Shader& getDefaultShader() { return shader; }
        [[nodiscard]] Frustum& getFrustum() { return frustum; }
        [[nodiscard]] const Frustum& getFrustum() const { return frustum; }
        [[nodiscard]] float getMeshRenderCount() const { return drawCounter.getCount(); }


        /**
         * @brief This will remove the mesh and transform from the renderer data structures.
         * @param mesh
         * @param transform
         */
        void remove(const ColorMesh& mesh, const Transform::Transform& transform);

        /**
         * @brief This sends the light point reference to the renderer so it can be rendered.
         * @param LightPoint
         * @param transform
         */
        void sendLightPoint(const LightPoint& LightPoint, const Transform::Transform& transform);
        /**
         * @brief This sends the mesh data to the renderer so it can be rendered.
         * @param mesh
         * @param material
         * @param transform
         */
        void sendMeshData(const ColorMesh& mesh, const Material& material, const Transform::Transform& transform);
        /**
         * @brief This sets the camera for the renderer.
         * @param cameraPerspective
         * @param transform
         */
        void setCamera(const CameraPerspective& cameraPerspective, const Transform::Transform& transform);
        /**
         * @brief This sets the sun for the renderer.
         * @param sun
         * @param ambientLight
         * @param transform
         */
        void setSun(const GlobalSun& sun, const GlobalAmbientLight& ambientLight, const Transform::Transform& transform);
        /**
         * @brief This seets the fog for the renderer.
         * @param fogParam
         * @param transform
         */
        void setFog(const Fog& fogParam, const Transform::Transform& transform);

        /**
         * @brief This empties all the data from the renderer. Nothing will be rendered.
         */
        void clearMeshData();
        /**
         * @brief This empties all the light data from the renderer. No lights will be rendered.
         */
        void clearLightData();
    private:
        /**
         * @brief This starts the frame of rendering
         * @details This will clear the buffers and prepare the matrices for rendering.
         * @param timeOfFrame The time of the frame in fraction.
         */
        void start(double timeOfFrame);
        /**
         * @brief This renders the frame
         * @details This renders all the elements of the renderer, including meshes, lights, skybox, etc.
         * @param timeOfFrame The time of the frame in fraction, used for interpolation.
         */
        void render(double timeOfFrame);
        /**
         * @brief This ends the frame of rendering
         * @details This will swap the buffers and clean the renderer data structures.
         */
        void swapBuffers() const;

        using MeshIndex = size_t;
        using MeshTransformIndex = size_t;
        using LightTransformIndex = size_t;

        /**
         * @brief This encapsulates the rendering of the lights, setting the uniforms
         * @param lights
         * @param lightTransforms
         * @param timeOfFrame
         */
        void renderLights(const std::vector<const LightPoint*>& lights,
                          const std::vector<const Transform::Transform*>& lightTransforms,
                          double timeOfFrame) const;
        /**
         * @brief This encapsulates the setting of transforms of the transforms of a mesh
         * @param MVMat The model view matrix
         * @param MVPMat The model view projection matrix
         * @param normalMat The normal matrix
         */
        static void applyTransform(const MV& MVMat, const MVP& MVPMat, const NormalMat& normalMat);
        /**
         * @brief This encapsulates the application of the ambient light
         * @param ambientLight The ambient light class
         */
        static void applyAmbientLight(const GlobalAmbientLight& ambientLight);
        /**
         * @brief This encapsulates the application of the fog, setting the uniforms
         * @param fogParam
         * @param cameraPosition
         */
        static void applyFog(const FogData& fogParam, const Position& cameraPosition);
        /**
         * @brief This encapsulates the application of the skybox, calling the skybox draw method
         * @param skyboxParam
         * @param view
         * @param projection
         */
        static void applySkybox(const Skybox& skyboxParam, const View& view, const Projection& projection);
        /**
         * @brief This encapsulates the application of the sun, setting the uniforms
         * @param sunParam
         */
        static void applySun(const Sun& sunParam);
        /**
         * @brief This encapsulates the application of the material, setting all the uniforms of the material
         * shader
         * @param material
         */
        static void applyMaterial(const Material& material);

        /**
         * @brief This encapsulates the rendering of the mesh, calling the draw method from the GAPI with the VAO
         * of the mesh
         * @param mesh
         */
        static void renderMesh(const ColorMesh& mesh);
        static void renderInstances(MeshIndex adaptedInstances);

        /**
         * @brief Static method that creates the projection matrix from a camera
         * @param camera
         * @return
         */
        static Projection createProjectionMatrix(const CameraPerspective& camera);
        /**
         * @brief Static method that creates the view matrix from a transform (transform of the camera)
         * @param transform
         * @return
         */
        static View createViewMatrix(const Transform::Transform& transform);

        WindowManager& windowManager;

        std::vector<const ColorMesh*> meshesToRender;
        std::vector<const Material*> meshMaterials;
        std::vector<const Transform::Transform*> meshTransforms;

        std::unordered_map<const ColorMesh*, std::vector<MeshTransformIndex>> instances;

        std::vector<const LightPoint*> lights;
        std::vector<const Transform::Transform*> lightTransforms;

        /**
         * @brief This is the interpolation data structure. It stores the interpolation data for each transform.
         */
        std::unordered_map<const Transform::Transform*, Transform::Interpolator> interpolationTransforms;

        std::vector<MVP> mvps;
        std::vector<MV> mvs;
        std::vector<NormalMat> normalMats;
        std::vector<bool> isContainedInFrustum;

        bool hasRenderBeenCalled = false;


        Shader shader;
        CameraPerspective defaultCameraPerspective;
        Transform::Transform defaultCameraTransform;
        Skybox skybox;
        FogData fog;
        Sun sun;
        GlobalAmbientLight ambientLight;

        Camera camera;
        Projection projection;
        View view;
        VP viewProjection;
        Frustum frustum;

        static Counter drawCounter;


        mutable std::mutex interpolationMutex{};
        mutable std::mutex mvpMutex{};
        mutable std::mutex mvMutex{};
        mutable std::mutex normalMatMutex{};
        mutable std::mutex frustumMutex{};
    }; // class Renderer
} // namespace GLESC
