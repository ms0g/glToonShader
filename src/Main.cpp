#include "Engine/Engine.h"


int main() {
    Engine glEngine;

    while (glEngine.isRunning()) {
        glEngine.processInput();
        glEngine.update();
        glEngine.render();
    }

    return 0;
}
