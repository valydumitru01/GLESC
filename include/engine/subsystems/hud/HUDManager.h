/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/core/low-level-renderer/graphic-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

class HUDManager {
public:
    HUDManager(GLESC::WindowManager &window, GLESC::Renderer &renderer, GraphicInterface &graphicInterface);
    
    ~HUDManager();
    
    void render();
    
    void update();

private:
    ImGuiIO *io;
    GLESC::WindowManager &window;
    GraphicInterface &graphicInterface;
    ImFont *font;
    
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
