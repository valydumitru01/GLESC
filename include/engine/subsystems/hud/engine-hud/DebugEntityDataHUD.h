/**************************************************************************************************
 * @file   DebugEntityDataHUD.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  HUD for the debug entity data.
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#ifndef NDEBUG_GLESC
#include "engine/subsystems/hud/InGameWindow.h"

namespace GLESC::HUD {
    /**
     * @brief Class to encapsulate the logic of the debug entity data HUD.
     * @details The debug entity data HUD is a window that displays debug information.
     * Allows visualizing the data that is associated with a selected entity.
     */
    class DebugEntityData : public InGameWindow {
    public:
        DebugEntityData();

    private:
        void windowContent(float timeOfFrame) override;
    }; // class EntityDebugDataInterface
} // namespace GLESC::HUD
#endif
