#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include "core/Window.h"
#include "core/systems/render/shaders/ShaderManager.h"

class GUI
{
public:
    GUI(Window* window, ShaderManager* shaderManager);
    ~GUI();
    void render();
    void update();
private:
    ImGuiIO* io;
    Window* window;
    ShaderManager* shaderManager;
    ImFont* font;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
