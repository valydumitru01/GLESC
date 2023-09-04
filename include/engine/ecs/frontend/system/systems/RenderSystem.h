/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/component/components/RenderComponent.h"
#include "engine/ecs/backend/component/components/TransformComponent.h"
#include "engine/ecs/frontend/system/System.h"

#include "engine/subsystems/renderer/Renderer.h"

class RenderSystem : public System {
public:
    void update(double timeOfFrame);
    explicit RenderSystem(GLESC::Renderer &renderer, GLESC::ECS& ecs);
private:
    GLESC::Renderer &renderer;
};