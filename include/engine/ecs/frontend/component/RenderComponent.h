/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "engine/ecs/frontend/entity/Entity.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/ecs/backend/component/IComponent.h"

namespace GLESC::ECS {
    struct RenderComponent : IComponent {
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

        std::string toString() const override {
            return "RenderComponent:\n" + mesh.toString();
        }

        std::string getName() const override {
            return "RenderComponent";
        }

        void setDebuggingValues() override {
            for (auto& value : material.getDebuggingValues()) {
                values.push_back(value);
            }
        }
    }; // struct RenderComponent
} // namespace GLESC::ECS