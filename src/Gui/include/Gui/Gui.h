#pragma once

#include <SDL2/SDL.h>


class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void render();
};
