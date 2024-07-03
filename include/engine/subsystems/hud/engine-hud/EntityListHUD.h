/**************************************************************************************************
 * @file   EntityListHUD.h
 * @author Valentin Dumitru
 * @date   28/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"
#ifndef NDEBUG_GLESC

namespace GLESC::HUD {
    /**
     * @brief A class that encapsulates the HUD for the entity list.
     * @details Allows visualizing the list of entities in the scene. Also, it allows selecting an entity
     * to then be able to display in the debug entity data HUD.
     */
    class EntityListHUD : public InGameWindow {
    public:
        EntityListHUD();
    private:
        void windowContent(float timeOfFrame) override;
    }; // class EntityListHUD
}

#endif
