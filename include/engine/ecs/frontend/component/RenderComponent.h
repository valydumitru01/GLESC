/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <variant>
#include "IComponent.h"
#include "engine/ecs/frontend/entity/Entity.h"
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

        void setDebuggingValues() override {
            EntityStatsManager::Value diffuseColorValue;
            diffuseColorValue.name = "Diffuse Color";
            diffuseColorValue.data = reinterpret_cast<void*>(&material.getDiffuseColor());
            diffuseColorValue.type = EntityStatsManager::ValueType::VEC3F;
            diffuseColorValue.isModifiable = true;
            diffuseColorValue.usesSlider = true;
            diffuseColorValue.min = 0.0f;
            diffuseColorValue.max = 255.0f;
            values.push_back(diffuseColorValue);

            EntityStatsManager::Value diffuseIntensityValue;
            diffuseIntensityValue.name = "Diffuse Intensity";
            diffuseIntensityValue.data = reinterpret_cast<void*>(&material.getDiffuseIntensity());
            diffuseIntensityValue.type = EntityStatsManager::ValueType::FLOAT;
            diffuseIntensityValue.isModifiable = true;
            diffuseIntensityValue.usesSlider = true;
            diffuseIntensityValue.min = 0.0f;
            diffuseIntensityValue.max = 1.0f;
            values.push_back(diffuseIntensityValue);

            EntityStatsManager::Value specularColorValue;
            specularColorValue.name = "Specular Color";
            specularColorValue.data = reinterpret_cast<void*>(&material.getSpecularColor());
            specularColorValue.type = EntityStatsManager::ValueType::VEC3F;
            specularColorValue.isModifiable = true;
            specularColorValue.usesSlider = true;
            specularColorValue.min = 0.0f;
            specularColorValue.max = 255.0f;
            values.push_back(specularColorValue);

            EntityStatsManager::Value specularIntensityValue;
            specularIntensityValue.name = "Specular Intensity";
            specularIntensityValue.data = reinterpret_cast<void*>(&material.getSpecularIntensity());
            specularIntensityValue.type = EntityStatsManager::ValueType::FLOAT;
            specularIntensityValue.isModifiable = true;
            specularIntensityValue.usesSlider = true;
            specularIntensityValue.min = 0.0f;
            specularIntensityValue.max = 1.0f;
            values.push_back(specularIntensityValue);

            EntityStatsManager::Value emissionColorValue;
            emissionColorValue.name = "Emission Color";
            emissionColorValue.data = reinterpret_cast<void*>(&material.getEmissionColor());
            emissionColorValue.type = EntityStatsManager::ValueType::VEC3F;
            emissionColorValue.isModifiable = true;
            emissionColorValue.usesSlider = true;
            emissionColorValue.min = 0.0f;
            emissionColorValue.max = 255.0f;
            values.push_back(emissionColorValue);

            EntityStatsManager::Value emissionIntensityValue;
            emissionIntensityValue.name = "Emission Intensity";
            emissionIntensityValue.data = reinterpret_cast<void*>(&material.getEmmisionIntensity());
            emissionIntensityValue.type = EntityStatsManager::ValueType::FLOAT;
            emissionIntensityValue.isModifiable = true;
            emissionIntensityValue.usesSlider = true;
            emissionIntensityValue.min = 0.0f;
            emissionIntensityValue.max = 1.0f;
            values.push_back(emissionIntensityValue);

            EntityStatsManager::Value shininessValue;
            shininessValue.name = "Shininess";
            shininessValue.data = reinterpret_cast<void*>(&material.getShininess());
            shininessValue.type = EntityStatsManager::ValueType::FLOAT;
            shininessValue.isModifiable = true;
            shininessValue.usesSlider = true;
            shininessValue.min = 0.0f;
            shininessValue.max = 1.0f;
            values.push_back(shininessValue);
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
