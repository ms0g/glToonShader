#include "gui.h"
#include <string>
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_sdl.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"
#include "../../libs/imgui/imgui_internal.h"


Gui::Gui(SDL_Window* window, SDL_GLContext gl_context) {
    // Initialize the ImGui context
    const char* glsl_version = "#version 410";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Gui::~Gui() {
    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::updateFpsCounter(float dt) {
    double elapsedSeconds;

    m_currentSeconds += dt;
    elapsedSeconds = m_currentSeconds - m_previousSeconds;
    // limit text updates to 4 per second
    if (elapsedSeconds > 0.25) {
        m_previousSeconds = m_currentSeconds;
        m_fps = (double) m_frameCount / elapsedSeconds;
        m_frameCount = 0;
    }
    m_frameCount++;
}

void Gui::render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

//    bool show_demo_window = true;
//    ImGui::ShowDemoWindow(&show_demo_window);


    if (ImGui::Begin("Statistics")) {
        ImGui::Text("Graphics:  %s FPS", std::to_string(m_fps).c_str());
    }
    ImGui::End();
    //Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
