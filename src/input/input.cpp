#include "input.h"
#include <SDL2/SDL.h>
#include "../../libs/imgui/imgui_impl_sdl.h"

void Input::process(SDL_Window* window, bool& isRunning) {
    SDL_Event event;

    SDL_PollEvent(&event);

    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT)
        isRunning = false;
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(window))
        isRunning = false;

    processMouse();
}

void Input::processMouse() {
    int x, y;

    const int buttons = SDL_GetMouseState(&x, &y);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<float>(x), static_cast<float>(y));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
}
