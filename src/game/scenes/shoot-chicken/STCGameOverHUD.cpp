/**************************************************************************************************
 * @file   STCGameOverHUD.cpp
 * @author Valentin Dumitru
 * @date   13/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "game/scenes/shoot-chicken/STCGameOverHUD.h"

#include "engine/subsystems/hud/HUDLookAndFeel.h"

STCGameOverHUD::STCGameOverHUD() {
    this->setSizeFraction({1.f, 1.f});
    this->setTitle("Game Over");
    isVisible = false;
    this->setLayoutPosition(GLESC::LayoutPos::BottomLeft);
    this->setCenter(GLESC::WindowCenter::BottomLeft);
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
    HudLookAndFeel::get().addFont(HudLookAndFeel::get().getDefaultFont(), 100);
}

void STCGameOverHUD::windowContent(float timeOfFrame) {
    // Assuming HudLookAndFeel::get().getFont(...) does not modify the font atlas
    auto& hudLookAndFeel = HudLookAndFeel::get();

    // Push the large font for "Game Over"
    ImGui::PushFont(hudLookAndFeel.getFont(hudLookAndFeel.getDefaultFont(), 100));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Red color
    ImGui::Text("Game Over");
    ImGui::PopStyleColor();
    ImGui::PopFont();

    // Push the smaller font for the instructions
    ImGui::PushFont(hudLookAndFeel.getFont(hudLookAndFeel.getDefaultFont(), 30));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  // White color
    ImGui::Text("Press 'R' to restart the game");
    ImGui::PopStyleColor();
    ImGui::PopFont();
}
