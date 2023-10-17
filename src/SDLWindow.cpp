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

    window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            displayMode.w,
            displayMode.h,
            SDL_WINDOW_OPENGL);

    if (!window) {
        std::cerr << "Error creating SDL Window";
        return;
    }

    SDL_SetWindowFullscreen(window, flags);

    context = SDL_GL_CreateContext(window);

}

SDLWindow::~SDLWindow() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* SDLWindow::GetWindow() const {
    return window;
}

void* SDLWindow::GetContext() const {
    return context;
}

void SDLWindow::UpdateFpsCounter(float dt) {
    double elapsedSeconds;

    currentSeconds += dt;
    elapsedSeconds = currentSeconds - previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        char tmp[128];
        double fps = (double) frameCount / elapsedSeconds;

        snprintf(tmp, 128, "%s @ fps: %.2f", m_title.c_str(), fps);

        SDL_SetWindowTitle(window, tmp);
        frameCount = 0;
    }
    frameCount++;
}

void SDLWindow::ClearImpl(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SDLWindow::SwapBuffer() {
    SDL_GL_SwapWindow(window);
}
