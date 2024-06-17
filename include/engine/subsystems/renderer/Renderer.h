/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <mutex>

#include "engine/core/counter/Counter.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "engine/core/window/WindowManager.h"

#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/Skybox.h"
#include "engine/subsystems/renderer/camera/CameraPerspective.h"
#include "engine/subsystems/renderer/fog/Fog.h"
#include "engine/subsystems/renderer/lighting/GlobalAmbienLight.h"
#include "engine/subsystems/renderer/lighting/GlobalSun.h"
#include "engine/subsystems/renderer/lighting/LightSpot.h"
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
            const GlobalAmbienLight* ambientLight = nullptr;
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


        void remove(const ColorMesh& mesh, const Transform::Transform& transform);

        void sendLightSpot(const LightSpot& lightSpot, const Transform::Transform& transform);
        void sendMeshData(const ColorMesh& mesh, const Material& material, const Transform::Transform& transform);
        void setCamera(const CameraPerspective& cameraPerspective, const Transform::Transform& transform);
        void setSun(const GlobalSun& sun, const GlobalAmbienLight& ambientLight, const Transform::Transform& transform);
        void setFog(const Fog& fogParam, const Transform::Transform& transform);

        void clearMeshData();
        void clearLightData();
    private:
        void start(double timeOfFrame);
        void render(double timeOfFrame);
        void swapBuffers() const;

        using MeshIndex = size_t;
        using MeshTransformIndex = size_t;
        using LightTransformIndex = size_t;

        void renderLights(const std::vector<const LightSpot*>& lights,
                          const std::vector<const Transform::Transform*>& lightTransforms,
                          double timeOfFrame) const;
        static void applyTransform(const MV& MVMat, const MVP& MVPMat, const NormalMat& normalMat);
        static void applyAmbientLight(const GlobalAmbienLight& ambientLight);
        static void applyFog(const FogData& fogParam, const Position& cameraPosition);
        static void applySkybox(const Skybox& skyboxParam, const View& view, const Projection& projection);
        static void applySun(const Sun& sunParam);
        static void applyMaterial(const Material& material);

        static void renderMesh(const ColorMesh& mesh);
        static void renderInstances(MeshIndex adaptedInstances);


        static Projection createProjectionMatrix(const CameraPerspective& camera);
        static View createViewMatrix(const Transform::Transform& transform);

        WindowManager& windowManager;

        std::vector<const ColorMesh*> meshesToRender;
        std::vector<const Material*> meshMaterials;
        std::vector<const Transform::Transform*> meshTransforms;

        std::unordered_map<const ColorMesh*, std::vector<MeshTransformIndex>> instances;

        std::vector<const LightSpot*> lights;
        std::vector<const Transform::Transform*> lightTransforms;

        mutable std::unordered_map<const Transform::Transform*, Transform::Interpolator> interpolationTransforms;

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
        GlobalAmbienLight ambientLight;

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
