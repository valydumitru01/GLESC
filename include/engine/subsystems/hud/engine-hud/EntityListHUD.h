/**************************************************************************************************
 * @file   EntityListHUD.h
 * @author Valentin Dumitru
 * @date   28/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"
#ifndef NDEBUG_GLESC

namespace GLESC::HUD {
    class EntityListHUD : public InGameWindow {
    public:
        EntityListHUD();
    private:
        void windowContent(float timeOfFrame) override;
    }; // class EntityListHUD
}

#endif
