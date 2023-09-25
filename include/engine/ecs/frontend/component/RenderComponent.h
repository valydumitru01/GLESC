/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "IComponent.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"

struct RenderComponent : public IComponent {
    /**
     * @brief The mesh of the object
     * Contains the vertices and indices of the object.
     */
    GLESC::Mesh mesh;
    
    std::string toString() override {
        return "RenderComponent" + mesh.toString();
    }
};


