/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "engine/ecs/backend/component/Component.h"
#include "engine/subsystems/renderer/Mesh.h"

struct RenderComponent : public Component {
    /**
     * @brief The mesh of the object
     * Contains the vertices and indices of the object.
     */
    GLESC::Mesh mesh;
};


