/**************************************************************************************************
 * @file   DebugItemsHUD.cpp
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#ifndef NDEBUG_GLESC
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
    items[HudItemType::FOG] = &textureFactory.loadTexture("images/sprites/engine-debug/GLESC_Fog.png");
    items[HudItemType::FOG]->release();

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

void DebugItems::windowContent(float timeOfFrame) {
    float width = static_cast<float>(renderer.getViewportSize().width);
    float height = static_cast<float>(renderer.getViewportSize().height);
    const auto& viewProj = renderer.getViewProjection();
    float vpWidth = static_cast<float>(renderer.getViewportSize().height);
    float vpHeight = static_cast<float>(renderer.getViewportSize().height);
    for (Item& item : HudItemsManager::getItems()) {
        if (!renderer.getFrustum().contains(*item.worldPosition)) continue;
        // TODO: Possible memory leak here if the item is not removed from the interpolators map
        interpolators[item.worldPosition].pushTransform(Transform::Transform(*
                                                                             item.worldPosition, {}, {1, 1, 1}));

        Render::Position screenPos =
            Transform::Transformer::worldToViewport(
                interpolators[item.worldPosition].interpolate(timeOfFrame).getPosition(),
                viewProj, width, height);
        float imageScale = screenPos.z() * 20;

        ImVec2 size = ImVec2(imageScale * vpWidth, imageScale * vpHeight);

        ImGui::SetCursorPos(ImVec2(screenPos.x() - size.x / 2, screenPos.y() - size.y / 2));

        // Get texture ID from the item's type
        auto textureId = (void*)(intptr_t)items[item.type]->getTextureID();

        // Draw the texture at the specified position
        ImGui::Image(textureId, ImVec2(size.x, size.y));

        // Optionally, you can create a tooltip on hover
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Text("Item: %s", itemToString(item.type).c_str());
            ImGui::Text("Screen Position: (%.2f, %.2f)", screenPos.x(), screenPos.y());
            ImGui::EndTooltip();
        }
    }
}
#endif