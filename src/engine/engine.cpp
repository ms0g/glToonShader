#include "engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "image/stb_image.h"
#include "filesystem/filesystem.h"
#include "glad/glad.h"
#include "../camera/camera.h"
#include "../window//window.h"
#include "../shader/shader.h"
#include "../model/model.h"
#include "../input/input.h"
#include "../gui/gui.h"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::init(const char* modelName) {
    m_window = std::make_unique<Window>();
    m_window->init("Toon Shader");

    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 5.0f));

    m_input = std::make_unique<Input>();

    m_gui = std::make_unique<Gui>(m_window->nativeHandle(),
                                  m_window->glContext());

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

    m_shader = std::make_unique<Shader>(
            Filesystem::path(SHADER_DIR + "toon.vert.glsl"),
            Filesystem::path(SHADER_DIR + "toon.frag.glsl"));

    m_model = std::make_unique<Model>(Filesystem::path(ASSET_DIR + modelName));

    m_isRunning = true;
}

void Engine::processInput() {
    m_input->process(m_window->nativeHandle(), m_isRunning);
}

void Engine::update() {
    m_deltaTime = (SDL_GetTicks() - m_millisecsPreviousFrame) / 1000.0f;
    m_millisecsPreviousFrame = SDL_GetTicks();

    m_gui->update(cameraSettings, m_deltaTime);

    m_camera->update(cameraSettings);

    // Activate shader
    m_shader->activate();
    // View/projection transformations
    glm::mat4 viewMat = m_camera->getViewMatrix();
    glm::vec3 viewPos = m_camera->getPosition();
    glm::mat4 projectionMat = glm::perspective(glm::radians(m_camera->getZoom()),
                                               ASPECT, ZNEAR, ZFAR);
    m_shader->setMat4("projection", projectionMat);
    m_shader->setMat4("view", viewMat);
    m_shader->setVec3("viewPos", viewPos);
    // Render the loaded model
    glm::mat4 modelMat = glm::mat4(1.0f);
    // translate it down so it's at the center of the scene
    modelMat = glm::translate(modelMat,
                              glm::vec3(0.0f, 0.0f, 0.0f));
    // it's a bit too big for our scene, so scale it down
    modelMat = glm::scale(modelMat,
                          glm::vec3(1.0f, 1.0f, 1.0f));

    modelMat = glm::rotate(modelMat, (float) SDL_GetTicks() * ROTATION_SPEED, glm::vec3(0.0f, 1.0f, 0.0f));

    m_shader->setMat4("model", modelMat);
}

void Engine::render() {
    m_window->clear(0.2f, 0.3f, 0.3f, 1.0f);

    m_model->draw(*m_shader);

    m_gui->render();

    // SDL swap buffers
    m_window->swapBuffer();
}
