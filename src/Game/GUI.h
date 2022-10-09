#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include "MyWindow.h"
#include "ShaderManager.h"
class GUI
{
public:
    GUI(MyWindow* window, ShaderManager* shaderManager);
    ~GUI();
    void render();
    void update();
private:
    ImGuiIO* io;
    MyWindow* window;
    ShaderManager* shaderManager;
    ImFont* font;

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
