/**************************************************************************************************
 * @file   STCGameOverHUD.h
 * @author Valentin Dumitru
 * @date   13/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"

class STCGameOverHUD : public GLESC::InGameWindow {
public:
    STCGameOverHUD();
private:
    void windowContent(float timeOfFrame) override;
}; // class ChickenKillCountHUD
