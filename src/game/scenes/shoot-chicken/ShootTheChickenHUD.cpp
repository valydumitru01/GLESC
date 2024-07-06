
#include "game/scenes/shoot-chicken/ShootTheChickenHUD.h"

#include "engine/subsystems/hud/HUDLookAndFeel.h"


ShootTheChickenHUD::ShootTheChickenHUD() {
    this->setSizeFraction({0.3f, 0.1f});
    this->setTitle("Chicken Kill Count");
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

void ShootTheChickenHUD::windowContent(float timeOfFrame) {
    ImGui::PushFont(HudLookAndFeel::get().getFont(HudLookAndFeel::get().getDefaultFont(), 30));
    // Push text color
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Red color

    ImGui::Text("Chicken Kill Count: %d", chickenKillCount);
    ImGui::Text("Ammunition: %d", ammunition);
    ImGui::PopStyleColor();
    ImGui::PopFont();
}
