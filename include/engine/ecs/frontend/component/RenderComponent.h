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

struct RenderComponent : public IComponent {
    /**
     * @brief The mesh of the object
     * Contains the vertices and indices of the object.
     */
    GLESC::Mesh mesh;
    
    /**
     * @brief The material of the object
     * Contains the color and texture of the object.
     */
    GLESC::Material material;
    
    std::string toString() override {
        return "RenderComponent:\n" + mesh.toString();
    }
};


