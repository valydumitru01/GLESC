/**************************************************************************************************
 * @file   DebugItemsHUD.cpp
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/hud/engine-hud/DebugItemsHUD.h"

#include "engine/subsystems/ingame-debug/HudItemsManager.h"

using namespace GLESC::HUD;

DebugItems::DebugItems(Render::Renderer& renderer, TextureFactory& textureFactory):
    renderer(renderer),
    textureFactory(textureFactory) {
    items[HudItemType::LIGHT_SPOT] = &textureFactory.loadTexture("images/sprites/engine-debug/GLESC_Light.png");
    items[HudItemType::LIGHT_SPOT]->release();
    items[HudItemType::SUN] = &textureFactory.loadTexture("images/sprites/engine-debug/GLESC_Sun.png");
    items[HudItemType::SUN]->release();

    this->setTitle("Items");
    this->setSizeFraction({1.0f, 1.0f});
    this->setMinSize({300.0f, 300.0f});
    this->isVisible = true;
    this->setCenter(WindowCenter::Center);
    this->setLayoutPosition(LayoutPos::Center);

    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoScrollbar);
    this->addFlag(ImGuiWindowFlags_NoBackground);
}

void DebugItems::windowContent() {
    for (Item& item : HudItemsManager::getItems()) {
        if (!renderer.getFrustum().contains(*item.worldPosition)) continue;
        Render::Position screenPos = Transform::Transformer::worldToViewport(*item.worldPosition,
                                                                             renderer.getView(),
                                                                             renderer.getProjection(),
                                                                             renderer.getViewportSize().width,
                                                                             renderer.getViewportSize().height);
        float imageScale = screenPos.z() * 4;
        float vpWidth = static_cast<float>(renderer.getViewportSize().height);
        float vpHeight = static_cast<float>(renderer.getViewportSize().height);

        ImVec2 size = ImVec2(imageScale * vpWidth, imageScale * vpHeight);

        ImGui::SetCursorPos(ImVec2(screenPos.x() + size.x , screenPos.y() - size.y ));

        // Get texture ID from the item's type
        auto textureId = (void*)(intptr_t)items[item.type]->getTextureID();

        // Draw the texture at the specified position
        ImGui::Image(textureId, ImVec2(size.x, size.y));

        // Optionally, you can create a tooltip on hover
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Item: %s", itemToString(item.type).c_str());
            ImGui::Text("Position: (%.2f, %.2f, %.2f)",
                        item.worldPosition->getX(), item.worldPosition->getY(), item.worldPosition->getZ());
            ImGui::EndTooltip();
        }
    }
}
