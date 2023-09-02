/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/System.h"
#include "engine/ecs/backend/component/components/CameraComponent.h"
#include "engine/ecs/backend/component/components/TransformComponent.h"
#include "engine/subsystems/renderer/Renderer.h"

class CameraSystem : public System {
public:
    explicit CameraSystem(GLESC::Renderer &renderer);
    
    void update();

private:
    GLESC::Renderer &renderer;
};

