/**************************************************************************************************
 * @file   Material.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <utility>

#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    /**
     * @brief Class inspired by the material class from open3D
     */
    class Material {
        using Intensity = Intensity<float>;

    public:
        /**
         * @brief Default constructor
         * @details This is needed to be able to use the material in a map and to construct the render component which
         * is also stored in a map
         */
        Material() :
            diffuseColor(ColorRgb(255, 255, 255)), // Neutral, slightly bright diffuse reflection
            diffuseIntensity(1.0f), // Full intensity of diffuse reflection
            specularColor(ColorRgb(255, 255, 255)), // Bright specular highlights
            specularIntensity(0.5f), // Moderate intensity for specular highlights
            emissionColor(ColorRgb(0, 0, 0)), // No emission by default
            emmisionIntensity(0.0f), // No intensity for emission
            shininess(1) // Moderately shiny;
        {
        }

        Material(ColorRgb  diffuseColor,
                 const Intensity& diffuseIntensity,
                 ColorRgb  specularColor,
                 const Intensity& specularIntensity,
                 ColorRgb  emissionColor,
                 const Intensity& emmisionIntensity,
                 const Intensity& shininess) :
            diffuseColor{std::move(diffuseColor)},
            diffuseIntensity{diffuseIntensity},
            specularColor{std::move(specularColor)},
            specularIntensity{specularIntensity},
            emissionColor{std::move(emissionColor)},
            emmisionIntensity{emmisionIntensity},
            shininess{shininess} {
        }

        [[nodiscard]] const ColorRgb& getDiffuseColor() const { return diffuseColor; }
        [[nodiscard]] float getDiffuseIntensity() const { return diffuseIntensity.get(); }
        [[nodiscard]] const ColorRgb& getSpecularColor() const { return specularColor; }
        [[nodiscard]] float getSpecularIntensity() const { return specularIntensity.get(); }
        [[nodiscard]] const ColorRgb& getEmissionColor() const { return emissionColor; }
        [[nodiscard]] float getEmmisionIntensity() const { return emmisionIntensity.get(); }
        [[nodiscard]] float getShininess() const { return shininess.get(); }

        void setDiffuseColor(const ColorRgb& diffuseColor) { this->diffuseColor = diffuseColor; }
        void setDiffuseIntensity(const float diffuseIntensity) { this->diffuseIntensity.set(diffuseIntensity); }
        void setSpecularColor(const ColorRgb& specularColor) { this->specularColor = specularColor; }
        void setSpecularIntensity(const float specularIntensity) { this->specularIntensity.set(specularIntensity); }
        void setEmissionColor(const ColorRgb& emissionColor) { this->emissionColor = emissionColor; }
        void setEmmisionIntensity(const float emmisionIntensity) { this->emmisionIntensity.set(emmisionIntensity); }
        void setShininess(const float shininess) { this->shininess.set(shininess); }

        [[nodiscard]] bool operator<(const Material& other) const {
            return std::tie(diffuseColor, specularColor, emissionColor, specularIntensity, shininess) <
                std::tie(other.diffuseColor, other.specularColor, other.emissionColor,
                         other.specularIntensity, other.shininess);
        }


        /**
         * @brief Equality operator
         * @param other The other material
         * @return True if the materials are equal, false otherwise
         */
        bool operator==(const Material& other) const {
            return diffuseColor == other.diffuseColor &&
                specularColor == other.specularColor &&
                emissionColor == other.emissionColor &&
                specularIntensity == other.specularIntensity &&
                shininess == other.shininess;
        }
        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues();

        [[nodiscard]] bool& isDirty() const { return dirty; }
        void setClean() const { dirty = false; }

    private:
        /**
         * @brief The diffuse color of the material
         */
        ColorRgb diffuseColor;
        /**
         * @brief The diffuse intensity of the material
         */
        Intensity diffuseIntensity;
        /**
         * @brief The specular color of the material
         */
        ColorRgb specularColor;
        /**
         * @brief The specular intensity of the material
         */
        Intensity specularIntensity;
        /**
         * @brief The emission color of the material
         */
        ColorRgb emissionColor;
        /**
         * @brief The emission intensity of the material
         */
        Intensity emmisionIntensity;

        /**
         * @brief The shininess of the material
         */
        Intensity shininess;
        /**
         * @brief Dirty flag, used to check if we need to resend the data to the GPU
         */
        mutable bool dirty{false};
    }; // class Material
} // namespace GLESC

// Hash
template <>
struct std::hash<GLESC::Render::Material> {
    [[nodiscard]] std::size_t operator()(const GLESC::Render::Material& material) const noexcept {
        std::size_t hash = 0;
        GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::ColorRgb>{}(material.getDiffuseColor()));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(material.getDiffuseIntensity()));
        GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::ColorRgb>{}(material.getSpecularColor()));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(material.getSpecularIntensity()));
        GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::ColorRgb>{}(material.getEmissionColor()));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(material.getEmmisionIntensity()));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(material.getShininess()));
        return hash;
    }
};
