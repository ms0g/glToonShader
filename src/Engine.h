#pragma once

#include <memory>
#include "Camera/Camera.h"
#include "Window/IWindow.hpp"
#include "Shader.h"
#include "Model.h"
#include "Input.h"
#include "Gui.h"


class Engine {
public:
    Engine();

    [[nodiscard]] bool IsRunning() const;

    void ProcessInput();

    void Update();

    void Render();

private:
    bool isRunning;
    std::unique_ptr<IWindow<SDL_Window>> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Model> m_model;


    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};