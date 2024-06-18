/******************************************************************************
 * @file   CameraSystem.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/renderer/Renderer.h"

namespace GLESC::ECS {
    class CameraSystem : public System {
    public:
        explicit CameraSystem(Render::Renderer& renderer, WindowManager& windowManager, ECSCoordinator& ecs);

        void update() override;

    private:
        Render::Renderer& renderer;
        WindowManager& windowManager;
    };
}
