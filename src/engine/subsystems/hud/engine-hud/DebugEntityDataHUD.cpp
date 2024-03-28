/**************************************************************************************************
 * @file   DebugEntityDataHUD.cpp
 * @author Valentin Dumitru
 * @date   09/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/hud/engine-hud/DebugEntityDataHUD.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

DebugEntityDataHUD::DebugEntityDataHUD() {
    this->setTitle("Entity Data");
    this->setSizeFraction({0.2f, 1.0f});
    isVisible = true;
    this->setLayoutPosition(GLESC::LayoutPos::CenterRight);
    this->setCenter(GLESC::WindowCenter::CenterRight);
    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoScrollbar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
}


void DebugEntityDataHUD::windowContent() {
    EntityData data = EntityStatsManager::getEntityData();

    // Set a window title with the entity's name
    ImGui::Text("Entity: %s", data.name.c_str());
    ImGui::Separator();

    for (auto& stat : data.components) {
        // Use a frame to individualize each component
        ImGui::BeginChild(stat.name.c_str(), ImVec2(0, 0), true);

        // Set a title for the component inside its frame
        ImGui::Text("%s", stat.name.c_str());
        ImGui::Separator();

        // Display each attribute of the component
        for (auto& nameValuePair : stat.nameValuePairs) {
            ImGui::Text("%s: %s", nameValuePair.first.c_str(), nameValuePair.second.c_str());
        }

        ImGui::EndChild(); // End of component frame
        ImGui::Spacing(); // Add some space between components for better readability
    }
}
