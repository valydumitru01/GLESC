/**************************************************************************************************
 * @file   HudLookAndFeel.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Class that encapsulates the look and feel of the HUD.
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <imgui/imgui.h>
/**
 * @brief Class that encapsulates the look and feel of the HUD.
 * @details Allows setting the look and feel of the HUD, such as the font, font size, and colors.
 */
class HudLookAndFeel {
public:
    using FontSize = int;

    ~HudLookAndFeel() = default;
    /**
     * @brief Returns the singleton instance of the class.
     * @return The singleton instance of the class.
     */
    static HudLookAndFeel &get() {
        static HudLookAndFeel instance;
        return instance;
    }

    /**
     * @brief Adds a font from a file with a size.
     * @details The font is added to the list of fonts that can be used in the HUD.
     * Fonts need to be loaded before use, and this class handles the loading and caching of fonts.
     * @param fileName The name of the font file.
     * @param size The font size.
     */
    void addFont(const std::string &fileName, FontSize size);
    ImFont *getFont(const std::string &fileName, FontSize size);



    /**
     * @brief Sets the default font
     * @param fileName The name of the font file.
     */
    void setDefaultFont(const std::string &fileName);
    /**
     * @brief Sets the default font size.
     * @param size The font size.
     */
    void setDefaultFontSize(int size);

    /**
     * @brief Returns the default font and font size.
     * @return The default font and font size.
     */
    std::string getDefaultFont() const;
    /**
     * @brief Returns the default font size.
     * @return The default font size.
     */
    FontSize getDefaultFontSize() const;

    /**
     * @brief Applies the look and feel to ImGui.
     */
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
    std::string defaultFont;
    int defaultFontSize = 0;

    bool lookAndFeelApplied = false;
}; // class HudLookAndFeel
