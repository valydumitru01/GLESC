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

#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC {
    /**
     * @brief Class inspired by the material class from open3D
     */
    class Material {
    public:
        /**
         * @brief Default constructor
         * @details This is needed to be able to use the material in a map and to construct the render component which is also
         * stored in a map
         */
        Material() = default;

        Material(const Vec3F& ambientColor, float ambientIntensity, const Vec3F& diffuseColor, float diffuseIntensity,
                 const Vec3F& specularColor, float specularIntensity, const Vec3F& emissionColor,
                 float emmisionIntensity,
                 float shininess)
            : ambientColor{ambientColor},
              ambientIntensity{ambientIntensity},
              diffuseColor{diffuseColor},
              diffuseIntensity{diffuseIntensity},
              specularColor{specularColor},
              specularIntensity{specularIntensity},
              emissionColor{emissionColor},
              emmisionIntensity{emmisionIntensity},
              shininess{shininess} {}

        [[nodiscard]] Vec3F getAmbientColor() const { return ambientColor; }
        [[nodiscard]] float getAmbientIntensity() const { return ambientIntensity; }
        [[nodiscard]] Vec3F getDiffuseColor() const { return diffuseColor; }
        [[nodiscard]] float getDiffuseIntensity() const { return diffuseIntensity; }
        [[nodiscard]] Vec3F getSpecularColor() const { return specularColor; }
        [[nodiscard]] float getSpecularIntensity() const { return specularIntensity; }
        [[nodiscard]] Vec3F getEmissionColor() const { return emissionColor; }
        [[nodiscard]] float getEmmisionIntensity() const { return emmisionIntensity; }
        [[nodiscard]] float getShininess() const { return shininess; }

        void setAmbientColor(const Vec3F& ambientColor) { this->ambientColor = ambientColor; }
        void setAmbientIntensity(const float ambientIntensity) { this->ambientIntensity = ambientIntensity; }
        void setDiffuseColor(const Vec3F& diffuseColor) { this->diffuseColor = diffuseColor; }
        void setDiffuseIntensity(const float diffuseIntensity) { this->diffuseIntensity = diffuseIntensity; }
        void setSpecularColor(const Vec3F& specularColor) { this->specularColor = specularColor; }
        void setSpecularIntensity(const float specularIntensity) { this->specularIntensity = specularIntensity; }
        void setEmissionColor(const Vec3F& emissionColor) { this->emissionColor = emissionColor; }
        void setEmmisionIntensity(const float emmisionIntensity) { this->emmisionIntensity = emmisionIntensity; }
        void setShininess(const float shininess) { this->shininess = shininess; }

        bool operator<(const Material& other) const {
            return std::tie(ambientColor, diffuseColor, specularColor, emissionColor, specularIntensity, shininess) <
                std::tie(other.ambientColor, other.diffuseColor, other.specularColor, other.emissionColor,
                         other.specularIntensity,
                         other.shininess);
        }


        /**
         * @brief Equality operator
         * @param other The other material
         * @return True if the materials are equal, false otherwise
         */
        bool operator==(const Material& other) const {
            return ambientColor == other.ambientColor && diffuseColor == other.diffuseColor &&
                specularColor == other.specularColor && emissionColor == other.emissionColor &&
                specularIntensity == other.specularIntensity && shininess == other.shininess;
        }

    private:
        /**
        * @brief The ambient color of the material
        */
        Vec3F ambientColor;
        /**
         * @brief The ambient intensity of the material
         */
        float ambientIntensity;
        /**
         * @brief The diffuse color of the material
         */
        Vec3F diffuseColor;
        /**
         * @brief The diffuse intensity of the material
         */
        float diffuseIntensity;
        /**
         * @brief The specular color of the material
         */
        Vec3F specularColor;
        /**
         * @brief The specular intensity of the material
         */
        float specularIntensity;
        /**
         * @brief The emission color of the material
         */
        Vec3F emissionColor;
        /**
         * @brief The emission intensity of the material
         */
        float emmisionIntensity;

        /**
         * @brief The shininess of the material
         */
        float shininess;
    }; // class Material
} // namespace GLESC

// Hash
template <>
struct std::hash<GLESC::Material> {
    std::size_t operator()(const GLESC::Material& material) const noexcept {
        return std::hash<Vec3F>()(material.getAmbientColor()) ^
            std::hash<Vec3F>()(material.getDiffuseColor()) ^
            std::hash<Vec3F>()(material.getSpecularColor()) ^
            std::hash<Vec3F>()(material.getEmissionColor()) ^
            std::hash<float>()(material.getSpecularIntensity()) ^
            std::hash<float>()(material.getShininess());
    }
};
