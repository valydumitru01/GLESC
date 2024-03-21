/**************************************************************************************************
 * @file   ConsoleInterface.cpp
 * @author Valentin Dumitru
 * @date   07/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include "engine/subsystems/hud/engine-hud/DebugConsoleHUD.h"

#include "engine/core/math/Math.h"
#include "engine/subsystems/ingame-debug/Console.h"


DebugConsoleHUD::DebugConsoleHUD() {
    this->setTitle("Console");
    this->setMaxSize({1200.0f, 300.0f});
    this->setMinSize({600.0f, 150.0f});
    this->setSizeFraction({0.5f, 0.2f});
    isVisible = true;
    this->setCenter(WindowCenter::BottomCenter);
    this->setLayoutPosition(LayoutPosition::BottomCenter);
    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
}


void DebugConsoleHUD::windowContent() {
    // Iterate through console messages and display them with appropriate color
    for (const auto& entry : GLESC::Console::GetMessages()) {
        ImVec4 color;
        std::string level;
        switch (entry.level) {
        case GLESC::LogLevel::Info:
            color = infoColor;
            level = "Info";
            break;
        case GLESC::LogLevel::Warning:
            color = warningColor;
            level = "Warning";
            break;
        case GLESC::LogLevel::Error:
            color = errorColor;
            level = "Error";
            break;
        default:
            color = infoColor;
            level = "Info";
            break;
        }


        ImGui::TextColored(color, "( %d ) %s: %s", entry.count, level.c_str(), entry.message.c_str());
    }
}
