/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/System.h"

#include "engine/subsystems/renderer/Renderer.h"

class RenderSystem : public System {
public:
    void update(double timeOfFrame);
    explicit RenderSystem(GLESC::Renderer &renderer, GLESC::ECS& ecs);
private:
    GLESC::Renderer &renderer;
};