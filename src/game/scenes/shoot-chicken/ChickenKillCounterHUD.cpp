/**************************************************************************************************
 * @file   ChickenKillCounterHUD.cpp
 * @author Valentin Dumitru
 * @date   09/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "game/scenes/shoot-chicken/ChickenKillCountHUD.h"


ChickenKillCountHUD::ChickenKillCountHUD() {
    this->setSizeFraction({1.f, 0.5f});
    isVisible = true;
    this->setLayoutPosition(GLESC::LayoutPos::BottomRight);
    this->setCenter(GLESC::WindowCenter::BottomRight);
    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoScrollbar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
    this->addFlag(ImGuiWindowFlags_NoInputs);
    this->addFlag(ImGuiWindowFlags_NoBackground);
}

void ChickenKillCountHUD::windowContent(float timeOfFrame) {
    ImGui::PushFont(HudLookAndFeel::get().getFont(HudLookAndFeel::get().getDefaultFont(), 30));
    // Push text color
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Red color

    ImGui::Text("Chicken Kill Count: %d", chickenKillCount);
    ImGui::PopFont();
}
