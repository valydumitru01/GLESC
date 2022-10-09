//#include <imgui/imgui.h>
//#include <imgui/imgui_impl_sdl.h>
//#include <imgui/imgui_impl_opengl3.h>
#include "MyWindow.h"
#include "PreprocessorUtil.h"
class GUI
{
public:
    GUI(MyWindow* window);
    ~GUI();
    void render();
    void update();
private:
    //ImGuiIO io;
    MyWindow* window;
    //ImFont* font;
};
