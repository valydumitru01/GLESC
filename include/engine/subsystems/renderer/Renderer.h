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
#include "engine/subsystems/renderer/mesh/MeshAdapter.h"
#include "engine/subsystems/transform/Transform.h"

class MeshRenderingTest;

namespace GLESC {
    class Engine;
}

namespace GLESC::Render {
    class Renderer {
        friend class GLESC::Engine;
        friend class ::MeshRenderingTest;

        struct Light {
            const LightSpot* light = nullptr;
            const Transform::Transform* transform = nullptr;
        };

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

        [[nodiscard]] View getView() const { return view; }
        void setView(const View& viewParam) { this->view = viewParam; }

        [[nodiscard]] Projection getProjection() const { return projection; }
        void setProjection(const Projection& projectionParam) { this->projection = projectionParam; }

        [[nodiscard]] WindowDimensions getViewportSize() const { return windowManager.getSize(); }
        [[nodiscard]] Camera getCamera() const { return this->camera; }


        [[nodiscard]] Shader& getDefaultShader() { return shader; }
        [[nodiscard]] Frustum& getFrustum() { return frustum; }
        [[nodiscard]] const Frustum& getFrustum() const { return frustum; }
        [[nodiscard]] const float getMeshRenderCount() const { return drawCounter.getCount(); }


        void sendMeshData(const ColorMesh& mesh, const Material& material, const Transform::Transform& transform);
        void setCamera(const CameraPerspective& cameraPerspective, const Transform::Transform& transform);
        void setSun(const GlobalSun& sun, const GlobalAmbienLight& ambientLight, const Transform::Transform& transform);
        void setFog(const Fog& fogParam, const Transform::Transform& transform);
        void addLightSpot(const LightSpot& lightSpot, const Transform::Transform& transform);

    private:
        void renderMeshes(double timeOfFrame);
        void start();
        void swapBuffers() const;

        void applyLighSpots(const std::vector<Light>& lights, double timeOfFrame) const;
        static void applyTransform(const MV& MVMat, const MVP& MVPMat, const NormalMat& normalMat);
        static void applyAmbientLight(const GlobalAmbienLight& ambientLight);
        static void applyFog(const FogData& fogParam, const Position& cameraPosition);
        static void applySkybox(const Skybox& skyboxParam, const View& view, const Projection& projection);
        static void applySun(const Sun& sunParam);
        static void applyMaterial(const Material& material);

        static void renderMesh(const AdaptedMesh& mesh);
        static void renderInstances(const AdaptedInstances& adaptedInstances);

        WindowManager& windowManager;

        mutable std::unordered_map<const Transform::Transform*, Transform::Interpolator> interpolationTransforms;
        mutable std::mutex interpolationMutex{};

        std::unordered_map<AdaptedMesh*, MVP> mvps;
        std::mutex mvpMutex{};
        std::unordered_map<AdaptedMesh*, MV> mvs;
        std::mutex mvMutex{};
        std::unordered_map<AdaptedMesh*, NormalMat> normalMats;
        std::mutex normalMatMutex{};
        std::unordered_map<AdaptedMesh*, bool> isContainedInFrustum;
        std::mutex frustumMutex{};

        std::vector<AdaptedMesh> adaptedMeshes;

        Shader shader;

        Camera camera;
        CameraPerspective defaultCameraPerspective;
        Transform::Transform defaultCameraTransform;
        Skybox skybox;
        FogData fog;
        Sun sun;
        GlobalAmbienLight ambientLight;

        std::vector<Light> lights;

        static Counter drawCounter;

        Projection projection;
        View view;
        VP viewProjection;
        Frustum frustum;
        static Projection createProjectionMatrix(const CameraPerspective& camera);
        static View createViewMatrix(const Transform::Transform& transform);
    }; // class Renderer
} // namespace GLESC
