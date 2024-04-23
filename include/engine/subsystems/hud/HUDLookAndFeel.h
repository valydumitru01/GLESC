/**************************************************************************************************
 * @file   HudLookAndFeel.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <imgui/imgui.h>

#include "engine/core/asserts/Asserts.h"

class HudLookAndFeel {
public:
    using FontSize = int;

    ~HudLookAndFeel() = default;
    static HudLookAndFeel &get() {
        static HudLookAndFeel instance;
        return instance;
    }

    void addFont(const std::string &fileName, FontSize size);
    ImFont *getFont(const std::string &fileName, FontSize size);


    void setDefaultFont(const std::string &fileName);
    void setDefaultFontSize(int size);

    std::string getDefaultFont() const;
    FontSize getDefaultFontSize() const;


    void apply();


private:
    HudLookAndFeel() = default;
    static void validateFontName(const std::string &fileName);
    static void validateFontSize(FontSize size);

    // Define the color palette
    ImVec4 veryDarkGreen = ImVec4(0.00f, 0.10f, 0.07f, 1.00f);
    ImVec4 darkGreen = ImVec4(0.00f, 0.20f, 0.13f, 1.00f);
    ImVec4 green = ImVec4(0.00f, 0.50f, 0.33f, 1.00f);
    ImVec4 brightGreen = ImVec4(0.20f, 0.75f, 0.40f, 1.00f);
    ImVec4 black = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    ImVec4 white = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    ImVec4 gray = ImVec4(0.20f, 0.25f, 0.20f, 1.00f);
    std::unordered_map<std::string, ImFont *> fonts;
    std::string defaultFont = "";
    int defaultFontSize = 0;

    bool lookAndFeelApplied = false;
}; // class HudLookAndFeel
