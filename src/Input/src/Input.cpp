#include "Input/Input.h"
#include <SDL2/SDL.h>
#include "Camera/Camera.h"
#include "../../../libs/imgui/imgui_impl_sdl.h"


void Input::process(Camera& camera, SDL_Window* window, float dt, bool& isRunning) {
    SDL_Event event;
    SDL_PollEvent(&event);

    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT)
        isRunning = false;
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(window))
        isRunning = false;

    ImGuiIO& io = ImGui::GetIO();

    int mouseX, mouseY;
    const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
    io.MousePos = ImVec2(mouseX, mouseY);
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

    processKeyboard(camera, dt, isRunning);
    processMouse(camera, mouseX, mouseY);
}


void Input::processKeyboard(Camera& camera, float dt, bool& isRunning) {
    auto* keystate = SDL_GetKeyboardState(nullptr);

    if (keystate[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    } else if (keystate[SDL_SCANCODE_W]) {
        camera.processKeyboard(FORWARD, dt);
    } else if (keystate[SDL_SCANCODE_S]) {
        camera.processKeyboard(BACKWARD, dt);
    } else if (keystate[SDL_SCANCODE_A]) {
        camera.processKeyboard(LEFT, dt);
    } else if (keystate[SDL_SCANCODE_D]) {
        camera.processKeyboard(RIGHT, dt);
    }
}

void Input::processMouse(Camera& camera, int x, int y) {
    auto xpos = static_cast<float>(x);
    auto ypos = static_cast<float>(y);

    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top

    m_lastX = xpos;
    m_lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}
