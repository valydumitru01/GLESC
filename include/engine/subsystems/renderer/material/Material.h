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
         * @brief The ambient color of the material
         */
        Vec3D ambientColor;
        /**
         * @brief The diffuse color of the material
         */
        Vec3D diffuseColor;
        /**
         * @brief The specular color of the material
         */
        Vec3D specularColor;
        /**
         * @brief The shininess of the material
         */
        float shininess;
        /**
         * @brief The texture of the material
         */
        
        /**
         * @brief Default constructor
         */
        Material() = default;
        
        /**
         * @brief Constructor
         * @param ambientColorParam The ambient color of the material
         * @param diffuseColorParam The diffuse color of the material
         * @param specularColorParam The specular color of the material
         * @param shininessParam The shininess of the material
         */
        Material(Vec3D ambientColorParam,
                 Vec3D diffuseColorParam,
                 Vec3D specularColorParam,
                 float shininessParam)
                :
                ambientColor(std::move(ambientColorParam)), diffuseColor(
                std::move(diffuseColorParam)),
                specularColor(std::move(specularColorParam)), shininess(shininessParam) {}
        
        /**
         * @brief Equality operator
         * @param other The other material
         * @return True if the materials are equal, false otherwise
         */
        bool operator==(const Material &other) const {
            return ambientColor == other.ambientColor && diffuseColor == other.diffuseColor &&
                   specularColor == other.specularColor && shininess == other.shininess;
        }
        
        void setAmbientColor(const Vec3D &ambientColorParam) {
            ambientColor = ambientColorParam;
        }
        
        void setDiffuseColor(const Vec3D &diffuseColorParam) {
            diffuseColor = diffuseColorParam;
        }
        
        void setSpecularColor(const Vec3D &specularColorParam) {
            specularColor = specularColorParam;
        }
        
    }; // class Material
} // namespace GLESC