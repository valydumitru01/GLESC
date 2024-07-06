#include "engine/subsystems/hud/engine-hud/CrosshairHUD.h"


using namespace GLESC::HUD;
CrosshairHUD::CrosshairHUD() {
    this->setSizeFraction({0.3f, 0.3f});
    isVisible = true;
    this->setLayoutPosition(GLESC::LayoutPos::Center);
    this->setCenter(GLESC::WindowCenter::Center);
    this->addFlag(ImGuiWindowFlags_NoBackground);
    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
}

void CrosshairHUD::windowContent(float timeOfFrame) {
    // Get the center of your window or viewport
    ImVec2 windowCenter = ImVec2(
        ImGui::GetWindowPos().x + ImGui::GetWindowSize().x * 0.5f,
        ImGui::GetWindowPos().y + ImGui::GetWindowSize().y * 0.5f
    );
    ImU32 crosshairColor = IM_COL32(
        static_cast<int>(linesColor.getR()),
        static_cast<int>(linesColor.getG()),
        static_cast<int>(linesColor.getB()),
        static_cast<int>(linesColor.getA())
    );
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Draw vertical line
    drawList->AddLine(
        ImVec2(windowCenter.x, windowCenter.y - linesLength),
        ImVec2(windowCenter.x, windowCenter.y + linesLength),
        crosshairColor
    );

    // Draw horizontal line
    drawList->AddLine(
        ImVec2(windowCenter.x - linesLength, windowCenter.y),
        ImVec2(windowCenter.x + linesLength, windowCenter.y),
        crosshairColor
    );
}
