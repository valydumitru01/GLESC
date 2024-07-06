#include "engine/subsystems/hud/engine-hud/DebugStatsHUD.h"

#include "engine/subsystems/hud/HUDLookAndFeel.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"

using namespace GLESC::HUD;
DebugStatsHUD::DebugStatsHUD() {
    this->setTitle("Stats");
    this->setSizeFraction({1.f, 0.5f});
    isVisible = true;
    this->setLayoutPosition(GLESC::LayoutPos::TopLeft);
    this->setCenter(GLESC::WindowCenter::TopLeft);
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

void DebugStatsHUD::windowContent(float timeOfFrame) {
    for (const auto& entry : StatsManager::getStats()) {
        std::string statName = entry.first;
        std::string statValue = entry.second;

        ImGui::PushFont(HudLookAndFeel::get().getFont(HudLookAndFeel::get().getDefaultFont(), 16));
        ImGui::TextColored(statsTextColor, "%s: %s", statName.c_str(), statValue.c_str());
        ImGui::PopFont();
    }
}