/******************************************************************************
 * @file   HUDManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/hud/HUDManager.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include "engine/Config.h"
#ifdef GLESC_OPENGL
#include <imgui/imgui_impl_opengl3.h>
#endif
#include "engine/subsystems/hud/HudLookAndFeel.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

using namespace GLESC::HUD;
HUDManager::HUDManager(SDL_Window &window) :
    window(window) {
    initImGUI();
}

HUDManager::~HUDManager() {
#ifdef GLESC_OPENGL
    ImGui_ImplOpenGL3_Shutdown();
#endif
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void HUDManager::processInput(SDL_Event &event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void HUDManager::addWindow(GLESC::InGameWindow &window, const std::string &name) {
    windows.push_back(&window);
    windowNames.push_back(Hasher::hash(name));
}
void HUDManager::removeWindow(const std::string &name) {
    auto hash = Hasher::hash(name);
    for (int i = 0; i < windowNames.size(); i++) {
        if (windowNames[i] == hash) {
            windows.erase(windows.begin() + i);
            windowNames.erase(windowNames.begin() + i);
            break;
        }
    }
}

void HUDManager::update() {
    for (auto &window : windows) {
            window->update();
    }
}

void HUDManager::render(double timeOfFrame) {
    newFrame();
    for (auto &window : windows) {
        window->render(static_cast<float>(timeOfFrame));
    }
    endFrame();

    // ImGui::ShowDemoWindow();
    ImGui::Render();
#ifdef GLESC_OPENGL
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void HUDManager::newFrame() {
#ifdef GLESC_OPENGL
    ImGui_ImplOpenGL3_NewFrame();
#endif
    ImGui_ImplSDL2_NewFrame(&window);
    ImGui::NewFrame();
}

void HUDManager::endFrame() {
    ImGui::EndFrame();
}

void HUDManager::initImGUI() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    std::string glslCoreStr = GLESC_GLSL_CORE_PROFILE ? "core" : "";
    std::string glslVersionStr = "#version " + std::to_string(GLESC_GL_MAJOR_VERSION) + "" +
                                 std::to_string(GLESC_GL_MINOR_VERSION) + "0 " + glslCoreStr + "\n";
#ifdef GLESC_OPENGL
    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(&window, getGAPI().getContext());
    ImGui_ImplOpenGL3_Init(glslVersionStr.c_str());
#endif
    HudLookAndFeel::get().setDefaultFont("PixelIntv");
    HudLookAndFeel::get().setDefaultFontSize(20);
    // This must be called after all the inits
    for (int i = 1; i < 40; i++) {
        HudLookAndFeel::get().addFont(HudLookAndFeel::get().getDefaultFont(), i);
    }
    HudLookAndFeel::get().apply();
}
