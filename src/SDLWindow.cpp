#include "SDLWindow.h"
#include <iostream>
#include "glad/glad.h"

SDLWindow::SDLWindow(const char* title, bool fullscreen) : m_title(title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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

    m_sdlWindow = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            displayMode.w,
            displayMode.h,
            SDL_WINDOW_OPENGL);

    if (!m_sdlWindow) {
        std::cerr << "Error creating SDL Window";
        return;
    }

    SDL_SetWindowFullscreen(m_sdlWindow, flags);

    m_sdlGlContext = SDL_GL_CreateContext(m_sdlWindow);

}

SDLWindow::~SDLWindow() {
    SDL_GL_DeleteContext(m_sdlGlContext);
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

SDL_Window* SDLWindow::GetWindow() const {
    return m_sdlWindow;
}

void* SDLWindow::GetContext() const {
    return m_sdlGlContext;
}

void SDLWindow::UpdateFpsCounter(float dt) {
    double elapsedSeconds;

    m_currentSeconds += dt;
    elapsedSeconds = m_currentSeconds - m_previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25) {
        m_previousSeconds = m_currentSeconds;
        char tmp[128];
        double fps = (double) m_frameCount / elapsedSeconds;

        snprintf(tmp, 128, "%s @ fps: %.2f", m_title.c_str(), fps);

        SDL_SetWindowTitle(m_sdlWindow, tmp);
        m_frameCount = 0;
    }
    m_frameCount++;
}

void SDLWindow::ClearImpl(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SDLWindow::SwapBuffer() {
    SDL_GL_SwapWindow(m_sdlWindow);
}
