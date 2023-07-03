#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_opengl3.h>
#include "renderer/WindowManager.h"
#include "renderer/shaders/ShaderManager.h"
#include "renderer/Renderer.h"

class GUI
{
public:
    GUI(shared_ptr<WindowManager> &window, shared_ptr<Renderer> &renderer);
    ~GUI();
    void render();
    void update();
private:
    ImGuiIO* io;
    shared_ptr<WindowManager> window;
    shared_ptr<Renderer> renderer;
    ImFont* font;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
