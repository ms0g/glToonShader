#include "gui.h"
#include <string>
#include "glad/glad.h"
#include "../camera/cameraSettings.hpp"
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_sdl.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"
#include "../../libs/imgui/imgui_internal.h"

float Gui::posX = 0;
float Gui::posY = 0;
float Gui::posZ = 5.0;
float Gui::yaw = -90.0;
float Gui::pitch = 0.0;
float Gui::zoom = 45.0;

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

void Gui::update(CameraSettings& cameraSettings, float deltaTime) {
    updateFpsCounter(deltaTime);
    cameraSettings.x = posX;
    cameraSettings.y = posY;
    cameraSettings.z = posZ;
    cameraSettings.yaw = yaw;
    cameraSettings.pitch = pitch;
    cameraSettings.zoom = zoom;
}

void Gui::render() const {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

//    bool show_demo_window = true;
//    ImGui::ShowDemoWindow(&show_demo_window);

    renderUI();

    //Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::updateFpsCounter(float deltaTime) {
    double elapsedSeconds;

    m_currentSeconds += deltaTime;
    elapsedSeconds = m_currentSeconds - m_previousSeconds;
    // limit text updates to 4 per second
    if (elapsedSeconds > 0.25) {
        m_previousSeconds = m_currentSeconds;
        m_fps = (double) m_frameCount / elapsedSeconds;
        m_frameCount = 0;
    }
    m_frameCount++;
}

void Gui::renderUI() const {
    if (ImGui::Begin("Settings")) {
        if (ImGui::CollapsingHeader("Graphics", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("%s FPS", std::to_string(m_fps).c_str());
            ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION));
            ImGui::Text("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
            ImGui::Text("OpenGL Driver Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("OpenGL Renderer: %s", glGetString(GL_RENDERER));
        }
        ImGui::Separator();
        if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::SliderFloat("x", &posX, -5.0, 5.0);
            ImGui::SliderFloat("y", &posY, -3.0, 3.0);
            ImGui::SliderFloat("z", &posZ, 1.0, 9.0);
            ImGui::SliderFloat("yaw", &yaw, -180.0, 90.0);
            ImGui::SliderFloat("pitch", &pitch, -90.0, 90.0);
            ImGui::SliderFloat("zoom", &zoom, 1.0, 90.0);
        }
    }
    ImGui::End();
}