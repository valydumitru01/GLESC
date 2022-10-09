#include "GUI.h"


GUI::GUI(MyWindow *window)
{
    
    /*
    this->window = window;
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    font = io.Fonts->AddFontFromFileTTF("/assets/fonts/8514OEM.FON", 30.0f);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window->getWindow(), window->getContext());
    ImGui_ImplOpenGL3_Init(STRINGIFY(GLSL_VERSION));
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    */
}
GUI::~GUI(){
    /*
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    */
}
void GUI::update(){
    /*
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window->getWindow());
    
    char* buf = "";
    ImGui::PushFont(font);
    ImGui::Begin("Window");

    ImGui::InputText("Hello", buf,0);
    // std::cout << io.Fonts->Fonts.size() << std::endl;

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();

    ImGui::PopFont();
    */
}
void GUI::render()
{
    //ImGui::ShowDemoWindow();
    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
