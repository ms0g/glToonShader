#pragma once

#include <memory>
#include "../camera/cameraSettings.hpp"

class Camera;
class Window;
class Gui;
class Input;
class Shader;
class Model;
class Engine {
public:
    Engine();

    ~Engine();

    [[nodiscard]] inline bool isRunning() const { return m_isRunning; }

    void init(const char* modelName);

    void processInput();

    void update();

    void render();

private:
    CameraSettings cameraSettings{};
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Gui> m_gui;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Model> m_model;

    bool m_isRunning{false};
    float m_deltaTime{};
    uint32_t m_millisecsPreviousFrame{0};

};