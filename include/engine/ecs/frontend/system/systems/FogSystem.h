/**************************************************************************************************
 * @file   FogSystem.h
 * @author Valentin Dumitru
 * @date   05/05/2024
 * @brief  System that updates the fog in the scene
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/renderer/Renderer.h"

namespace GLESC::ECS {
    class FogComponent;

    class FogSystem : public System {
    public:
        explicit FogSystem(Render::Renderer& renderer, ECSCoordinator& ecs);
        void update() override;
    private:
        Render::Renderer& renderer;
    }; // class FogSystem
} // namespace GLESC::ECS
