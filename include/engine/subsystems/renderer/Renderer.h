/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>

#include "engine/core/asserts/Asserts.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/texture/TextureManager.h"
#include "engine/core/window/WindowManager.h"
#include "engine/res-mng/textures/TextureLoader.h"
#include "engine/subsystems/renderer/MeshAdapter.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/mesh/BatchMeshes.h"
#include "engine/subsystems/renderer/mesh/BatchMeshes.h"
#include "engine/subsystems/renderer/mesh/BatchMeshes.h"
#include "engine/subsystems/renderer/mesh/DynamicMeshes.h"
#include "engine/subsystems/renderer/mesh/InstanceMeshes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "engine/subsystems/transform/Transform.h"
#include "math/Frustum.h"

namespace GLESC {
    class Renderer {
    public:
        explicit Renderer(WindowManager &windowManager);

        ~Renderer();

        [[nodiscard]] View getView() const { return view; }
        void setView(const View &viewParam) { this->view = viewParam; }

        [[nodiscard]] Projection getProjection() const { return projection; }
        void setProjection(const Projection &projectionParam) { this->projection = projectionParam; }

        [[nodiscard]] Transform getCameraTrasnform() const {
            return this->cameraTransform;
        }
        void setCameraTransform(Transform cameraTransformParam) {
            this->cameraTransform = cameraTransformParam;
        }

        [[nodiscard]] Shader &getDefaultShader() { return shader; }
        [[nodiscard]] Frustum &getFrustum() { return frustum; }
        [[nodiscard]] const Frustum &getFrustum() const { return frustum; }


        void clear() const;

        void applyMaterial(const Material &material) const;
        void applyTransform(ColorMesh &mesh, const Transform &transform) const;
        void transformMeshCPU(ColorMesh &mesh, const Transform &transform);

        void renderMesh(const ColorMesh &mesh);


        void renderInstances(const ColorMesh &mesh,
                             const std::vector<MeshInstanceData> &instances);



        void setData(const Material &material,
                     ColorMesh &mesh,
                     const Transform &transform);

        void renderMeshes(double timeOfFrame);

        void swapBuffers() const;

    private:
        void cacheMesh(const ColorMesh &mesh,
                       AdaptedMesh adaptedMesh);

        void cacheMesh(const ColorMesh &mesh,
                       AdaptedInstances adaptedInstancesParam);

        [[nodiscard]] bool isMeshNotCached(const ColorMesh &mesh) const;

        WindowManager &windowManager;

        std::unordered_map<const ColorMesh *, AdaptedMesh> adaptedMeshes;
        std::unordered_map<const ColorMesh *, AdaptedInstances> adaptedInstances;

        Shader shader;
        InstanceMeshes meshInstances;
        MeshBatches meshBatches;
        DynamicMeshes dynamicMeshes;
        Frustum frustum;

        Projection projection;
        View view;
        Transform cameraTransform;
    }; // class Renderer
} // namespace GLESC
