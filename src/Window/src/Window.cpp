#include "Window/Window.h"
#include <iostream>
#include "glad/glad.h"


Window::Window(const char* title, bool fullscreen) : m_title(title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }

    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;
    else
        flags |= SDL_WINDOW_RESIZABLE;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    m_window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            displayMode.w,
            displayMode.h,
            flags);

    if (!m_window) {
        std::cerr << "Error creating SDL Window";
        return;
    }

    SDL_SetWindowFullscreen(m_window, flags);

    m_glContext = SDL_GL_CreateContext(m_window);
}

Window::~Window() {
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::updateFpsCounter(float dt) {
    double elapsedSeconds;

    m_currentSeconds += dt;
    elapsedSeconds = m_currentSeconds - m_previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25) {
        m_previousSeconds = m_currentSeconds;
        char tmp[128];
        double fps = (double) m_frameCount / elapsedSeconds;

        snprintf(tmp, 128, "%s @ fps: %.2f", m_title.c_str(), fps);

        SDL_SetWindowTitle(m_window, tmp);
        m_frameCount = 0;
    }
    m_frameCount++;
}

void Window::clearImpl(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

SDL_GLContext Window::glContext() const {
    return m_glContext;
}

void Window::swapBuffer() {
    SDL_GL_SwapWindow(m_window);
}
