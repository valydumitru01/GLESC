/**************************************************************************************************
 * @file   ChickenKillCountHUD.h
 * @author Valentin Dumitru
 * @date   09/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"

class ChickenKillCountHUD : public GLESC::InGameWindow{
public:
    ChickenKillCountHUD();
    void addChickenKill() {
        chickenKillCount++;
    }
private:
    void windowContent() override;
    int chickenKillCount = 0;
}; // class ChickenKillCountHUD
