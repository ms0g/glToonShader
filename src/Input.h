#pragma once

#include "Configs.hpp"

class Camera;
class SDL_Window;
class Input {
public:
    Input() = default;

    void Process(Camera& camera, SDL_Window* window, float dt, bool& isRunning);

private:
    void ProcessKeyboard(Camera& camera, float dt, bool& isRunning);

    void ProcessMouse(Camera& camera, int x, int y);

    int mouseX{}, mouseY{};
    float lastX{SCR_WIDTH / 2.0f};
    float lastY{SCR_HEIGHT / 2.0f};
    bool firstMouse{true};

};
