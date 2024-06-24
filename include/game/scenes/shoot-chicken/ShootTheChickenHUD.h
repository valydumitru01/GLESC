/**************************************************************************************************
 * @file   ShootTheChickenHUD.h
 * @author Valentin Dumitru
 * @date   09/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"

class ShootTheChickenHUD : public GLESC::InGameWindow{
public:
    ShootTheChickenHUD();
    void resetChickenKillCount() {
        chickenKillCount = 0;
    }
    void addChickenKill() {
        chickenKillCount++;
    }
    void setAmmunition(int ammunition) {
        this->ammunition = ammunition;
    }
    void addAmmunition(int ammunition = 1) {
        this->ammunition += ammunition;
    }
    void removeAmmunition(int ammunition = 1) {
        this->ammunition -= ammunition;
    }
    [[nodiscard]] int getChickenKillCount() const {
        return chickenKillCount;
    }
    [[nodiscard]] int getAmmunition() const {
        return ammunition;
    }

private:
    void windowContent(float timeOfFrame) override;
    int chickenKillCount = 0;
    int ammunition = 0;
}; // class ChickenKillCountHUD
