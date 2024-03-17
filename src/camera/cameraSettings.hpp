#pragma once

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

struct CameraSettings {
    float x;
    float y;
    float z;
    float zoom;
    float yaw;
    float pitch;
};
