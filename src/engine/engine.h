#pragma once

#include <memory>
#include "../camera/camera.h"
#include "../window//IWindow.hpp"
#include "../shader/shader.h"
#include "../model/model.h"
#include "../input/input.h"
#include "../gui/gui.h"


class Engine {
public:
    Engine();

    [[nodiscard]] bool isRunning() const;

    void processInput();

    void update();

    void render();

private:
    bool m_isRunning;
    std::unique_ptr<IWindow<SDL_Window>> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Model> m_model;


    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};