#include "Engine/Engine.h"


int main() {
    Engine glEngine;

    while (glEngine.IsRunning()) {
        glEngine.ProcessInput();
        glEngine.Update();
        glEngine.Render();
    }

    return 0;
}
