/**************************************************************************************************
 * @file   RenderComponent.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once
#include "engine/ecs/frontend/entity/Entity.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/ecs/backend/component/IComponent.h"

namespace GLESC::ECS {
    struct RenderComponent : IComponent {
        std::string toString() const override {
            return "RenderComponent:\n" + mesh.toString();
        }

        std::string getName() const override {
            return "RenderComponent";
        }

#ifndef NDEBUG_GLESC
        void setDebuggingValues() override {
            for (auto& value : material.getDebuggingValues()) {
                values.push_back(value);
            }
            for (auto& value : mesh.getDebuggingValues()) {
                values.push_back(value);
            }
        }

        void setUpdatedDebuggingValues() override {
            for (auto& value : mesh.getUpdatedDebuggingValues()) {
                updatedValues.push_back(value);
            }
        }
#endif


        void copyMesh(const Render::ColorMesh& mesh) {
            this->mesh = mesh;
        }

        void moveMesh(Render::ColorMesh& mesh) {
            this->mesh = std::move(mesh);
        }

        void moveMesh(Render::ColorMesh&& mesh) {
            this->mesh = std::move(mesh);
        }

        void copyMaterial(const Render::Material& material) {
            this->material = material;
        }

        void moveMaterial(Render::Material&& material) {
            this->material = std::move(material);
        }

        Render::ColorMesh& getMesh() {
            return mesh;
        }

        Render::Material& getMaterial() {
            return material;
        }

    private:
        /**
         * @brief The mesh of the object
         * Contains the vertices and indices of the object.
         */
        Render::ColorMesh mesh;

        /**
         * @brief The material of the object
         * Contains the color and texture of the object.
         */
        Render::Material material;
    }; // struct RenderComponent
} // namespace GLESC::ECS
