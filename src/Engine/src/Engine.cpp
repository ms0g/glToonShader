#include "Engine/Engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "image/stb_image.h"
#include "filesystem/filesystem.h"
#include "glad/glad.h"
#include "Window/Window.h"
#include "Configs/Configs.hpp"


Engine::Engine() :
        m_window(std::make_unique<Window>("Toon Shader")),
        m_camera(std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f))),
        m_input(std::make_unique<Input>()) {

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    m_shader = std::make_unique<Shader>(Filesystem::path(SHADER_DIR + "toon.vert.glsl"),
                                        Filesystem::path(SHADER_DIR + "toon.frag.glsl"));

    auto window = dynamic_cast<Window*>(m_window.get());
    m_gui = std::make_unique<Gui>(m_window->NativeHandle(),
                                  window->GLContext());

    m_model = std::make_unique<Model>(Filesystem::path(ASSET_DIR + "suzanne.glb"));

    isRunning = true;

#ifdef DEBUG
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
    std::cout << "OpenGL Driver Vendor: " << glGetString(GL_VENDOR) << '\n';
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << '\n';
#endif
}

bool Engine::IsRunning() const {
    return isRunning;
}

void Engine::ProcessInput() {
    m_input->Process(*m_camera, m_window->NativeHandle(), m_deltaTime, isRunning);
}

void Engine::Update() {
    m_deltaTime = (SDL_GetTicks() - m_millisecsPreviousFrame) / 1000.0f;
    m_millisecsPreviousFrame = SDL_GetTicks();

    auto window = dynamic_cast<Window*>(m_window.get());
    window->UpdateFpsCounter(m_deltaTime);

    // Activate shader
    m_shader->Activate();
    // View/projection transformations
    glm::mat4 viewMat = m_camera->GetViewMatrix();
    glm::vec3 viewPos = m_camera->GetPosition();
    glm::mat4 projectionMat = glm::perspective(glm::radians(m_camera->GetZoom()),
                                            (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
    m_shader->SetMat4("projection", projectionMat);
    m_shader->SetMat4("view", viewMat);
    m_shader->SetVec3("viewPos", viewPos);
    // Render the loaded model
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    modelMat = glm::scale(modelMat, glm::vec3(1.0f, 1.0f, 1.0f));    // it's a bit too big for our scene, so scale it down
    m_shader->SetMat4("model", modelMat);
}

void Engine::Render() {
    m_window->Clear(0.2f, 0.3f, 0.3f, 1.0f);

    m_model->Draw(*m_shader);

    m_gui->Render();

    // SDL swap buffers
    auto window = dynamic_cast<Window*>(m_window.get());
    window->SwapBuffer();
}
