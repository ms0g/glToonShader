#pragma once

#include <SDL2/SDL.h>

class CameraSettings;
class Gui {
public:
    Gui(SDL_Window* window, SDL_GLContext gl_context);

    ~Gui();

    void update(CameraSettings& cameraSettings, float deltaTime);

    void render() const;

private:
    void updateFpsCounter(float deltaTime);

    void renderUI() const;

    static float posX, posY, posZ, yaw, pitch, zoom;
    double m_previousSeconds{0.0};
    double m_currentSeconds{0.0};
    int m_frameCount{0};
    double m_fps{0.0};

};
