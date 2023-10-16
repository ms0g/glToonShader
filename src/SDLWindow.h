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

    void Clear() override;

    void SwapBuffer() override;

private:
    const std::string m_title;
    SDL_Window* window;
    SDL_GLContext context;

    double previousSeconds{};
    double currentSeconds{};
    int frameCount{};

};
