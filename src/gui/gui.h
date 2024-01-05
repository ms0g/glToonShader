#pragma once

#include <SDL2/SDL.h>


class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void updateFpsCounter(float dt);

    void render();

private:
    double m_previousSeconds{};
    double m_currentSeconds{};
    int m_frameCount{};
    double m_fps{};

};
