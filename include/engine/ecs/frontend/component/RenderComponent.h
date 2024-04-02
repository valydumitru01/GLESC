/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <variant>
#include "IComponent.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"

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
    };
}

// Hash
template <>
struct std::hash<GLESC::ECS::RenderComponent> {
    std::size_t operator()(const GLESC::ECS::RenderComponent& renderComponent) const noexcept {
        std::size_t hash = std::hash<GLESC::Render::ColorMesh>()(renderComponent.mesh);
        GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::Material>()(renderComponent.material));
        return hash;
    }
};
