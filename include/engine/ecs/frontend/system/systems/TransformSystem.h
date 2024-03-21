/**************************************************************************************************
 * @file   TransformSystem.h
 * @author Valentin Dumitru
 * @date   2024-03-21
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/ecs/frontend/system/System.h"


namespace GLESC::ECS {
    class TransformSystem : public System {
    public:
        explicit TransformSystem(ECSCoordinator& ecs);
        void update();
    };
} // namespace GLESC::ECS