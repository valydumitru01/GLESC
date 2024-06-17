/**************************************************************************************************
 * @file   HUDLookAndFeel.cpp
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/hud/HUDLookAndFeel.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/core/file-system/BinPath.h"
#include "engine/core/logger/Logger.h"


#define FONTS_PATH_FROM_ASSETS "/fonts/"
#define FONTS_EXTENSION ".ttf"


void HudLookAndFeel::addFont(const std::string& fileName, FontSize size) {
    validateFontName(fileName);
    validateFontSize(size);
    std::string fullFontPath = BinPath::getExecutableDirectory() + ASSETS_PATH + FONTS_PATH_FROM_ASSETS + fileName +
        FONTS_EXTENSION;
    //fullFontPath= GLESC::Stringer::replace(fullFontPath, "/", "\\");
    Logger::get().info("Loading font: " + fullFontPath);
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(fullFontPath.c_str(), static_cast<float>(size));
    D_ASSERT_NOT_NULLPTR(font, "Failed to load font: " + fullFontPath);
    fonts[fileName + std::to_string(size)] = font;
}

void HudLookAndFeel::validateFontName(const std::string& fileName) {
    D_ASSERT_TRUE(!fileName.empty(), "Font file name cannot be empty");
    D_ASSERT_TRUE(!GLESC::Stringer::contains(fileName, FONTS_EXTENSION),
                  "Font file should not contain the extension");
    D_ASSERT_TRUE(!GLESC::Stringer::contains(fileName, FONTS_PATH_FROM_ASSETS),
                  "Font file should not contain the path");
}

void HudLookAndFeel::validateFontSize(FontSize size) {
    D_ASSERT_TRUE(size > 0, "Font size should be greater than 0");
}

void HudLookAndFeel::setDefaultFont(const std::string& fileName) {
    validateFontName(fileName);
    defaultFont = fileName;
}

void HudLookAndFeel::setDefaultFontSize(FontSize size) {
    validateFontSize(size);
    defaultFontSize = size;
}

std::string HudLookAndFeel::getDefaultFont() const {
    D_ASSERT_TRUE(!defaultFont.empty(), "Default font not set");
    return defaultFont;
}

HudLookAndFeel::FontSize HudLookAndFeel::getDefaultFontSize() const {
    D_ASSERT_TRUE(defaultFontSize > 0, "Default font size not set");
    return defaultFontSize;
}

ImFont* HudLookAndFeel::getFont(const std::string& fileName, FontSize size) {
    validateFontName(fileName);
    validateFontSize(size);
    if (fonts.find(fileName + std::to_string(size)) == fonts.end()) {
        addFont(fileName, size);
    }
    return fonts[fileName + std::to_string(size)];
}

void HudLookAndFeel::apply() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.29f, 1.00f, 0.28f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.48f, 0.61f, 0.48f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.15f, 0.70f, 0.22f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.69f, 0.47f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.41f, 0.64f, 0.41f, 0.69f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.54f, 0.27f, 0.83f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.63f, 0.32f, 0.87f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.80f, 0.41f, 0.20f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.55f, 0.40f, 0.80f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.30f, 0.20f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.80f, 0.40f, 0.30f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.80f, 0.40f, 0.40f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.39f, 0.80f, 0.39f, 0.60f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
    colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.80f, 0.39f, 0.60f);
    colors[ImGuiCol_Button] = ImVec4(0.35f, 0.61f, 0.36f, 0.62f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.71f, 0.41f, 0.79f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.80f, 0.47f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.40f, 0.90f, 0.40f, 0.45f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.90f, 0.45f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.87f, 0.54f, 0.80f);
    colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.39f, 0.21f, 0.60f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.70f, 0.60f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.90f, 0.70f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 1.00f, 0.79f, 0.60f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 1.00f, 0.78f, 0.90f);
    colors[ImGuiCol_Tab] = ImVec4(0.34f, 0.68f, 0.34f, 0.79f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.90f, 0.46f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.40f, 0.73f, 0.41f, 0.84f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.28f, 0.57f, 0.29f, 0.82f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.65f, 0.35f, 0.84f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.38f, 0.27f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.45f, 0.31f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 0.01f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.45f, 0.90f, 0.45f, 0.80f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);


    // Make sure these changes take effect
    ImGui::GetIO().FontDefault = getFont(defaultFont, defaultFontSize);
    ImGui::GetIO().Fonts->Build();
    lookAndFeelApplied = true;
}
