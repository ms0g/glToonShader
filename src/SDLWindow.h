#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Window.hpp"

class SDLWindow : public IWindow {
public:
    explicit SDLWindow(const char* title, bool fullscreen = false);

    ~SDLWindow() override;

    [[nodiscard]] SDL_Window* GetWindow() const;

    [[nodiscard]] void* GetContext() const;

    void UpdateFpsCounter(float dt) override;

    void ClearImpl(float r, float g, float b, float a) override;

    void SwapBuffer() override;

private:
    const std::string m_title;
    SDL_Window* m_sdlWindow;
    SDL_GLContext m_sdlGlContext;

    double m_previousSeconds{};
    double m_currentSeconds{};
    int m_frameCount{};

};
