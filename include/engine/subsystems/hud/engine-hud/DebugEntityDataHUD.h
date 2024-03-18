/**************************************************************************************************
 * @file   DebugEntityDataHUD.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"

class DebugEntityDataHUD : public GLESC::InGameWindow {
public:
    DebugEntityDataHUD();

private:
    void windowContent() override;
}; // class EntityDebugDataInterface
