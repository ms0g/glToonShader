#pragma once

class SDL_Window;
class Input {
public:
    Input() = default;

    void process(SDL_Window* window, bool& isRunning);

private:
    void processMouse();

};
