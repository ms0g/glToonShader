#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "IWindow.hpp"

class Window : public IWindow<SDL_Window> {
public:
    explicit Window(const char* title, bool fullscreen = false);

    ~Window() override;

    [[nodiscard]] void* GetContext() const;

    void UpdateFpsCounter(float dt);

    void ClearImpl(float r, float g, float b, float a) override;

    void SwapBuffer() override;

private:
    const std::string m_title;
    SDL_GLContext m_sdlGlContext;

    double m_previousSeconds{};
    double m_currentSeconds{};
    int m_frameCount{};
};
