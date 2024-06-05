/**************************************************************************************************
 * @file   DebugEntityDataHUD.cpp
 * @author Valentin Dumitru
 * @date   09/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/hud/engine-hud/DebugEntityDataHUD.h"

#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/subsystems/hud/HUDLookAndFeel.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

using namespace GLESC::HUD;

DebugEntityData::DebugEntityData() {
    this->setTitle("Entity Data");
    this->setSizeFraction({0.2f, 1.0f});
    this->setMinSize({300.0f, 0.0f});
    isVisible = true;
    this->setLayoutPosition(LayoutPos::CenterRight);
    this->setCenter(WindowCenter::CenterRight);
    this->addFlag(ImGuiWindowFlags_NoResize);
    this->addFlag(ImGuiWindowFlags_NoMove);
    this->addFlag(ImGuiWindowFlags_NoCollapse);
    this->addFlag(ImGuiWindowFlags_NoTitleBar);
    this->addFlag(ImGuiWindowFlags_NoSavedSettings);
    this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
    this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
    this->addFlag(ImGuiWindowFlags_AlwaysAutoResize);
}

template <typename InputType>
void text(const std::string& name, InputType* data) {
    if constexpr (std::is_same_v<InputType, float>) {
        ImGui::Text(name.c_str(), *data);
    }
    else if constexpr (std::is_same_v<InputType, int>) {
        ImGui::Text(name.c_str(), *data);
    }
    else if constexpr (std::is_same_v<InputType, bool>) {
        ImGui::Text(name.c_str(), *data ? "true" : "false");
    }
    else if constexpr (std::is_same_v<InputType, std::string>) {
        ImGui::Text(name.c_str(), data->data());
    }
    else if constexpr (std::is_same_v<InputType, Vec2F>) {
        ImGui::Text(name.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec3F>) {
        ImGui::Text(name.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec4F>) {
        ImGui::Text(name.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec2I>) {
        ImGui::Text(name.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec3I>) {
        ImGui::Text(name.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec4I>) {
        ImGui::Text(name.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec2B>) {
        ImGui::Text("%s: x: %s, y: %s", name.c_str(), data->x() ? "true" : "false", data->y() ? "true" : "false");
    }
    else if constexpr (std::is_same_v<InputType, Vec3B>) {
        ImGui::Text("%s: x: %s, y: %s, z: %s", name.c_str(), data->x() ? "true" : "false", data->y() ? "true" : "false",
                    data->z() ? "true" : "false");
    }
    else if constexpr (std::is_same_v<InputType, Vec4B>) {
        ImGui::Text("%s: x: %s, y: %s, z: %s, w: %s",
                    name.c_str(), data->x() ? "true" : "false", data->y() ? "true" : "false",
                    data->z() ? "true" : "false", data->w() ? "true" : "false");
    }
    else if constexpr (std::is_same_v<InputType, Mat2F> || std::is_same_v<InputType, Mat3F> ||
        std::is_same_v<InputType, Mat4F>) {
        ImGui::Text("%s: \n", name.c_str());
        ImGui::Text(data->toString().c_str());
    }
}

template <typename InputType>
void slider(const std::string& name, InputType* data, const float& minParam, const float& maxParam) {
    std::string inputName = "##" + name + " -- Slider";
    if constexpr (std::is_same_v<InputType, float>) {
        ImGui::SliderFloat(inputName.c_str(), data, minParam, maxParam);
    }
    else if constexpr (std::is_same_v<InputType, int>) {
        ImGui::SliderInt(inputName.c_str(), data, minParam, static_cast<int>(maxParam));
    }
    else if constexpr (std::is_same_v<InputType, Vec2F>) {
        ImGui::SliderFloat2(inputName.c_str(), data->data.data(), minParam, maxParam);
    }
    else if constexpr (std::is_same_v<InputType, Vec3F>) {
        ImGui::SliderFloat3(inputName.c_str(), data->data.data(), minParam, maxParam);
    }
    else if constexpr (std::is_same_v<InputType, Vec4F>) {
        ImGui::SliderFloat4(inputName.c_str(), data->data.data(), minParam, maxParam);
    }
    else if constexpr (std::is_same_v<InputType, Vec2I>) {
        ImGui::SliderInt2(inputName.c_str(), data->data.data(), minParam, static_cast<int>(maxParam));
    }
    else if constexpr (std::is_same_v<InputType, Vec3I>) {
        ImGui::SliderInt3(inputName.c_str(), data->data.data(), minParam, static_cast<int>(maxParam));
    }
}

template <typename InputType>
void input(const std::string& name, InputType* data) {
    std::string inputName = "##" + name + " -- Input";
    if constexpr (std::is_same_v<InputType, float>) {
        ImGui::InputFloat(inputName.c_str(), data);
    }
    else if constexpr (std::is_same_v<InputType, int>) {
        ImGui::InputInt(inputName.c_str(), data);
    }
    else if constexpr (std::is_same_v<InputType, bool>) {
        ImGui::Checkbox(inputName.c_str(), data);
    }
    else if constexpr (std::is_same_v<InputType, std::string>) {
        ImGui::InputText(inputName.c_str(), data->data(), data->size());
    }
    else if constexpr (std::is_same_v<InputType, Vec2F>) {
        ImGui::InputFloat2(inputName.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec3F>) {
        ImGui::InputFloat3(inputName.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec4F>) {
        ImGui::InputFloat4(inputName.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec2I>) {
        ImGui::InputInt2(inputName.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec3I>) {
        ImGui::InputInt3(inputName.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec4I>) {
        ImGui::InputInt4(inputName.c_str(), data->data.data());
    }
    else if constexpr (std::is_same_v<InputType, Vec2B>) {
        ImGui::Checkbox(std::string(" - x ").c_str(), &data->x());
        ImGui::SameLine();
        ImGui::Checkbox(std::string(" - y ").c_str(), &data->y());
    }
    else if constexpr (std::is_same_v<InputType, Vec3B>) {
        ImGui::Checkbox(std::string(" - x ").c_str(), &data->x());
        ImGui::SameLine();
        ImGui::Checkbox(std::string(" - y ").c_str(), &data->y());
        ImGui::SameLine();
        ImGui::Checkbox(std::string(" - z ").c_str(), &data->z());
    }
    else if constexpr (std::is_same_v<InputType, Vec4B>) {
        ImGui::Checkbox(std::string(" - x ").c_str(), &data->x());
        ImGui::SameLine();
        ImGui::Checkbox(std::string(" - y ").c_str(), &data->y());
        ImGui::SameLine();
        ImGui::Checkbox(std::string(" - z ").c_str(), &data->z());
        ImGui::SameLine();
        ImGui::Checkbox(std::string(" - w ").c_str(), &data->w());
    }
}


template
<typename InputType>
void input(EntityStatsManager::Value& value) {
    auto inputValue = reinterpret_cast<InputType*>(value.data);
    ImGui::PushItemWidth(-FLT_MIN); // Set the width of the input field to the maximum width of the window
    text(value.name, inputValue);

    if (!value.isModifiable) return;
    if (value.usesSlider) {
        slider(value.name, inputValue, value.min, value.max);
    }
    input(value.name, inputValue);
    ImGui::PopItemWidth();
}

void putInputForType(EntityStatsManager::ValueType type, EntityStatsManager::Value& value) {
    switch (type) {
    case EntityStatsManager::ValueType::FLOAT:
        input<float>(value);
        break;

    case EntityStatsManager::ValueType::INT:
        input<int>(value);
        break;

    case EntityStatsManager::ValueType::BOOL:
        input<bool>(value);
        break;

    case EntityStatsManager::ValueType::VEC2B:
        input<Vec2B>(value);
        break;
    case EntityStatsManager::ValueType::VEC3B:
        input<Vec3B>(value);
        break;

    case EntityStatsManager::ValueType::VEC4B:
        input<Vec4B>(value);
        break;

    case EntityStatsManager::ValueType::STRING:
        input<std::string>(value);
        break;

    case EntityStatsManager::ValueType::VEC2F:
        input<Vec2F>(value);
        break;

    case EntityStatsManager::ValueType::VEC3F:
        input<Vec3F>(value);
        break;

    case EntityStatsManager::ValueType::VEC4F:
        input<Vec4F>(value);
        break;

    case EntityStatsManager::ValueType::VEC2I:
        input<Vec2I>(value);
        break;

    case EntityStatsManager::ValueType::VEC3I:
        input<Vec3I>(value);
        break;

    case EntityStatsManager::ValueType::VEC4I:
        input<Vec4I>(value);
        break;

    case EntityStatsManager::ValueType::MAT2F:
        input<Mat2F>(value);
        break;

    case EntityStatsManager::ValueType::MAT3F:
        input<Mat3F>(value);
        break;

    case EntityStatsManager::ValueType::MAT4F:
        input<Mat4F>(value);
        break;
    default: {
        D_ASSERT_TRUE(false, "Unknown value type");
    }
    }
}


void DebugEntityData::windowContent() {
    EntityStatsManager::EntityData& data = EntityStatsManager::getEntityData();


    // Set a window title with the entity's name
    ImGui::Text("Entity: %s", data.name.c_str());
    ImGui::Separator();
    ImGui::PushFont(HudLookAndFeel::get().getFont(HudLookAndFeel::get().getDefaultFont(), 14.0f));
    for (const EntityStatsManager::ComponentData& stat : data.components) {
        // Dynamically calculate the needed height for each child window based on the number of items
        float childHeight = 15 * ImGui::GetTextLineHeightWithSpacing();

        // Begin a child window with a specific height to enforce stacking
        ImGui::BeginChild(stat.name.c_str(), ImVec2(-1, childHeight), true);

        // Set a title for the component inside its frame
        ImGui::Text("%s", stat.name.c_str());
        ImGui::Separator();

        // Display each attribute of the component
        for (EntityStatsManager::Value& value : *stat.values) {
            if (value.isString) {
                ImGui::Text(value.name.c_str());
                ImGui::Text(value.stringData.c_str());
                break;
            }
            // While visible the panel of the data, the value is dirty as we want to update it
            if (value.valueDirty != nullptr)
                *value.valueDirty = true;
            putInputForType(value.type, value);
        }
        for (EntityStatsManager::Value value : stat.updatedValues) {
            putInputForType(value.type, value);
        }
        ImGui::EndChild(); // End of component frame
        ImGui::Spacing(); // Add some space between components for better readability
    }
    ImGui::PopFont();
}
