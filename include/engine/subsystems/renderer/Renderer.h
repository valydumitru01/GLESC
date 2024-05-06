/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include "Fog.h"
#include "Skybox.h"
#include "engine/core/window/WindowManager.h"
#include "mesh/MeshAdapter.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "../../core/low-level-renderer/shader/Shader.h"
#include "camera/CameraPerspective.h"
#include "engine/core/counter/Counter.h"

#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/Transform.h"

#include "engine/subsystems/renderer/math/Frustum.h"
#include "fog/Fog.h"
#include "lighting/GlobalAmbienLight.h"
#include "lighting/GlobalSun.h"
#include "lighting/LightSpot.h"

namespace GLESC::Render {
    class Renderer {

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
        [[nodiscard]] Camera getCamer() const { return this->camera; }



        [[nodiscard]] Shader& getDefaultShader() { return shader; }
        [[nodiscard]] Frustum& getFrustum() { return frustum; }
        [[nodiscard]] const Frustum& getFrustum() const { return frustum; }
        [[nodiscard]] const float getMeshRenderCount() const { return drawCounter.getCount(); }



        void sendMeshData(const Material& material, ColorMesh& mesh);
        void setCamera(const CameraPerspective& cameraPerspective, const Transform::Transform& transform);
        void setSun(const GlobalSun& sun, const GlobalAmbienLight& ambientLight, const Transform::Transform& transform);
        void setFog(const Fog& fogParam, const Transform::Transform& transform);
        void addLightSpot(const LightSpot& lightSpot, const Transform::Transform& transform);

        void attatchMeshToBatch(ColorMesh& batch, ColorMesh& mesh, const Transform::Transform& transform);


    private:
        void renderMeshes(double timeOfFrame);
        static void clear();
        void swapBuffers() const;

        void applyLighSpots(const std::vector<Light>& lights, double timeOfFrame) const;
        static void applyTransform(const MV& modelView, const MVP& mvp, const NormalMat& normalMat);
        static void applyAmbientLight(const GlobalAmbienLight& ambientLight);
        static void applyFog(const FogData& fogParam);
        static void applySkybox(const Skybox& skyboxParam, const View& view, const Projection& projection);
        static void applySun(const GlobalSun& sun);
        static void applyMaterial(const Material& material);

        static void renderMesh(const AdaptedMesh& mesh);
        static void renderInstances(const AdaptedInstances& adaptedInstances);

        WindowManager& windowManager;

        mutable std::unordered_map<const Transform::Transform*, Transform::Interpolator> interpolationTransforms;

        std::vector<AdaptedMesh> adaptedBatches;

        Shader shader;

        Camera camera;
        Frustum frustum;
        Skybox skybox;
        FogData fog;
        Sun sun;
        GlobalAmbienLight ambientLight;

        std::vector<Light> lights;

        static Counter drawCounter;

        Projection projection;
        View view;
        VP viewProjection;
    }; // class Renderer
} // namespace GLESC
