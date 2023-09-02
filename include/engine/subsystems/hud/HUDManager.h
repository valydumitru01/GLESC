/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/Renderer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "engine/subsystems/hud/HUDManager.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLAPI.h"

template <typename GAPI>
class HUDManager {
public:
    HUDManager(GLESC::WindowManager<GAPI> &window, IGraphicInterface &graphicInterface) :
            window(window), graphicInterface(graphicInterface) {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
        font = io->Fonts->AddFontFromFileTTF("assets\\fonts\\PixelIntv.ttf", 30.0f);
        io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        
        std::string glslCoreStr = graphicInterface.getIsGlslCore() ? "core" : "";
        std::string glslVersionStr = "#version " + std::to_string(graphicInterface.getGlslMajorVersion()) + "" +
                                     std::to_string(graphicInterface.getGlslMinorVersion()) + glslCoreStr + "\n";
        #ifdef GLESC_RENDER_OPENGL
        const auto &openGLGDI = dynamic_cast<OpenGLAPI &>(graphicInterface);
        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(&window.getWindow(), openGLGDI.getContext());
        ImGui_ImplOpenGL3_Init(glslVersionStr.c_str());
        #endif
        // Setup Dear ImGui style
        ImGui::StyleColorsLight();
    }
    
    void update() {
        #ifdef GLESC_RENDER_OPENGL
        ImGui_ImplOpenGL3_NewFrame();
        #endif
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        // 1. Show the big demo windowManager (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its
        // code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        // 2. Show a simple windowManager that we create ourselves. We use a Begin/End pair to create a named windowManager.
        {
            static float f = 0.0f;
            static int counter = 0;
            
            ImGui::Begin("Hello, world!"); // Create a windowManager called "Hello, world!" and append into it.
            
            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our windowManager open/close state
            ImGui::Checkbox("Another Window", &show_another_window);
            
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color
            
            if (ImGui::Button(
                    "Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        // 3. Show another simple windowManager.
        if (show_another_window) {
            ImGui::Begin("Another Window",
                         &show_another_window); // Pass a pointer to our bool variable (the windowManager
            // will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another windowManager!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }
    
    void render() const{
        // ImGui::ShowDemoWindow();
        ImGui::Render();
        #ifdef GLESC_RENDER_OPENGL
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        #endif
    }
    
    ~HUDManager() {
        #ifdef GLESC_RENDER_OPENGL
        ImGui_ImplOpenGL3_Shutdown();
        #endif
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

private:
    ImGuiIO *io;
    GLESC::WindowManager<GAPI> &window;
    IGraphicInterface &graphicInterface;
    ImFont *font;
    
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
