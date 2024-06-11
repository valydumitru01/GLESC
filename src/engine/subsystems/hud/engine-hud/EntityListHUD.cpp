/**************************************************************************************************
 * @file   EntityListHUD.cpp
 * @author Valentin Dumitru
 * @date   27/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/hud/engine-hud/EntityListHUD.h"

#include <map>

#include "engine/core/asserts/Asserts.h"
#include "engine/subsystems/ingame-debug/EntityListManager.h"

GLESC::HUD::EntityListHUD::EntityListHUD() {
    this->setTitle("Entity List");
    this->setSizeFraction({0.2f, 0.7f});
    this->setMinSize({300.0f, 0.0f});
    isVisible = true;
    this->setLayoutPosition(LayoutPos::BottomLeft);
    this->setCenter(WindowCenter::BottomLeft);

    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
    this->addFlag(ImGuiWindowFlags_AlwaysAutoResize);
}

void entityButton(int index, const std::string& name) {
    ImGui::Columns(2, nullptr, false);
    // Set column widths
    ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.1f);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() * 0.9f);

    ImGui::Text("%d", index);
    ImGui::NextColumn();


    if (ImGui::Button(name.c_str(), ImVec2(-1, 0.0f))) {
        EntityListManager::setSelectedEntity(name);
    }

    ImGui::NextColumn();
}

void GLESC::HUD::EntityListHUD::windowContent(float timeOfFrame) {
    std::map<std::string, std::vector<const std::string*>> entityMap;

    // Group entities and instances
    for (const auto& entityListItem : EntityListManager::getEntities()) {
        D_ASSERT_NOT_NULLPTR(entityListItem.name, "Entity is null");
        const std::string* entityName = entityListItem.name;

        if (entityListItem.type == EntityType::Instance) {
            std::string strippedName = GLESC::Stringer::strip(*entityName, "1234567890");
            entityMap[strippedName].push_back(entityName);
        } else {
            entityMap[*entityName]; // Ensure the entity is in the map
        }
    }

    // Display entities and instances
    int entityIndex = 0;
    for (const auto& entityPair : entityMap) {
        const std::string& entityName = entityPair.first;
        const std::vector<const std::string*>& instances = entityPair.second;

        // Create two columns for all entries
        ImGui::Columns(2, nullptr, false);

        if(instances.empty())
            // Display the main entity
            entityButton(entityIndex + 1, entityName);

        ImGui::Columns(1,nullptr, false);
        // Display instances if any using CollapsingHeader for consistency
        if (!instances.empty()) {
            std::string headerLabel = entityName;
            ImGui::PushID(entityIndex); // Ensure unique IDs for ImGui components
            if (ImGui::CollapsingHeader(headerLabel.c_str())) {
                for (const auto& instanceName : instances) {
                    ImGui::Indent();
                    entityButton(++entityIndex, *instanceName);
                    ImGui::Unindent();
                }
            }
            ImGui::PopID();
        }

        ImGui::Columns(1); // Reset columns for the next entry
        ++entityIndex; // Increment the entity index
    }
}
