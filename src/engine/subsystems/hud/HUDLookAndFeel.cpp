/**************************************************************************************************
 * @file   HUDLookAndFeel.cpp
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/hud/HUDLookAndFeel.h"
#include "engine/core/asserts/Asserts.h"


void HudLookAndFeel::addFont(const std::string& fileName, float size) {
    D_ASSERT_TRUE(!lookAndFeelApplied, "Cannot add fonts after look and feel has been applied");
    D_ASSERT_TRUE(fonts.find(fileName) == fonts.end(), "Font already loaded");

    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(
        (ASSETS_PATH + std::string("/fonts/") + fileName + FONTS_EXTENSION).c_str(), size);
    fonts[fileName] = font;
}

ImFont* HudLookAndFeel::getFont(const std::string& fileName) {
    return fonts[fileName];
}

void HudLookAndFeel::apply() {
    ImGuiStyle& style = ImGui::GetStyle();


    // Set roundness of elements
    style.FrameRounding = 4.0f; // Roundness of buttons, sliders, etc.
    style.WindowRounding = 6.0f; // Roundness of windows
    style.ScrollbarRounding = 9.0f; // Roundness of scrollbars
    style.GrabRounding = 3.0f; // Roundness of grabbable sliders/buttons

    // Apply the color palette to ImGui elements
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = brightGreen;
    colors[ImGuiCol_WindowBg] = darkGreen;
    colors[ImGuiCol_Header] = green;
    colors[ImGuiCol_HeaderHovered] = brightGreen;
    colors[ImGuiCol_HeaderActive] = brightGreen;
    colors[ImGuiCol_Button] = green;
    colors[ImGuiCol_ButtonHovered] = brightGreen;
    colors[ImGuiCol_ButtonActive] = gray;
    colors[ImGuiCol_FrameBg] = green;
    colors[ImGuiCol_Border] = black;
    colors[ImGuiCol_SliderGrab] = brightGreen;
    colors[ImGuiCol_SliderGrabActive] = gray;
    colors[ImGuiCol_CheckMark] = brightGreen;
    colors[ImGuiCol_ResizeGrip] = green;
    colors[ImGuiCol_ResizeGripHovered] = brightGreen;
    colors[ImGuiCol_ResizeGripActive] = gray;
    colors[ImGuiCol_Tab] = green;
    colors[ImGuiCol_TabHovered] = brightGreen;
    colors[ImGuiCol_TabActive] = gray;
    colors[ImGuiCol_TabUnfocused] = green;
    colors[ImGuiCol_TabUnfocusedActive] = gray;
    colors[ImGuiCol_PlotLines] = brightGreen;
    colors[ImGuiCol_PlotLinesHovered] = gray;
    colors[ImGuiCol_PlotHistogram] = brightGreen;
    colors[ImGuiCol_PlotHistogramHovered] = gray;
    colors[ImGuiCol_TextSelectedBg] = gray;
    colors[ImGuiCol_DragDropTarget] = brightGreen;
    colors[ImGuiCol_NavHighlight] = brightGreen;
    colors[ImGuiCol_NavWindowingHighlight] = brightGreen;
    colors[ImGuiCol_NavWindowingDimBg] = black;
    colors[ImGuiCol_ModalWindowDimBg] = black;

    colors[ImGuiCol_TitleBg] = darkGreen;
    colors[ImGuiCol_TitleBgActive] = green;
    colors[ImGuiCol_TitleBgCollapsed] = darkGreen;
    colors[ImGuiCol_MenuBarBg] = darkGreen;
    colors[ImGuiCol_ScrollbarBg] = darkGreen;
    colors[ImGuiCol_ScrollbarGrab] = green;
    colors[ImGuiCol_ScrollbarGrabHovered] = brightGreen;
    colors[ImGuiCol_ScrollbarGrabActive] = brightGreen;
    colors[ImGuiCol_CheckMark] = brightGreen;
    colors[ImGuiCol_SliderGrab] = green;
    colors[ImGuiCol_SliderGrabActive] = brightGreen;
    colors[ImGuiCol_Button] = green;
    colors[ImGuiCol_ButtonHovered] = brightGreen;
    colors[ImGuiCol_ButtonActive] = gray;
    colors[ImGuiCol_Header] = green;
    colors[ImGuiCol_HeaderHovered] = brightGreen;
    colors[ImGuiCol_HeaderActive] = gray;
    colors[ImGuiCol_Separator] = black;
    colors[ImGuiCol_SeparatorHovered] = brightGreen;
    colors[ImGuiCol_SeparatorActive] = gray;
    colors[ImGuiCol_ResizeGrip] = green;
    colors[ImGuiCol_ResizeGripHovered] = brightGreen;
    colors[ImGuiCol_ResizeGripActive] = gray;
    colors[ImGuiCol_Tab] = green;
    colors[ImGuiCol_TabHovered] = brightGreen;
    colors[ImGuiCol_TabActive] = darkGreen;
    colors[ImGuiCol_TabUnfocused] = darkGreen;
    colors[ImGuiCol_TabUnfocusedActive] = green;
    colors[ImGuiCol_PlotLines] = brightGreen;
    colors[ImGuiCol_PlotLinesHovered] = gray;
    colors[ImGuiCol_PlotHistogram] = green;
    colors[ImGuiCol_PlotHistogramHovered] = brightGreen;
    colors[ImGuiCol_TextSelectedBg] = gray;
    colors[ImGuiCol_DragDropTarget] = brightGreen;
    colors[ImGuiCol_NavHighlight] = brightGreen;
    colors[ImGuiCol_NavWindowingHighlight] = brightGreen;
    colors[ImGuiCol_NavWindowingDimBg] = darkGreen;
    colors[ImGuiCol_ModalWindowDimBg] = black;

    // Adjusting padding and spacing to match the roundness and theme
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.FramePadding = ImVec2(5.0f, 3.0f);
    style.ItemSpacing = ImVec2(6.0f, 5.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.IndentSpacing = 20.0f;

    // Customizing the font size and window border size to match the overall theme feel
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    // Make sure these changes take effect
    ImGui::GetIO().Fonts->Build();

    lookAndFeelApplied = true;
}
