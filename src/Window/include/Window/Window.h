#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "IWindow.hpp"


class Window : public IWindow<SDL_Window> {
public:
    explicit Window(const char* title, bool fullscreen = false);

    ~Window() override;

    void updateFpsCounter(float dt);

    [[nodiscard]] SDL_GLContext glContext() const;

    void clearImpl(float r, float g, float b, float a) override;

    void swapBuffer();

private:
    const std::string m_title;
    SDL_GLContext m_glContext;

    double m_previousSeconds{};
    double m_currentSeconds{};
    int m_frameCount{};
};
