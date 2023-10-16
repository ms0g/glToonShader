#pragma once

#include "glm/glm.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

class Camera {
public:
    explicit Camera(const glm::vec3& position = glm::vec3{0.0f, 0.0f, 0.0f},
                    const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 GetViewMatrix();

    [[nodiscard]] float GetZoom() const;

    [[nodiscard]] const glm::vec3& GetPosition() const;

    [[nodiscard]] const glm::vec3& GetFront() const;

    void ProcessKeyboard(CameraMovement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset);

    void ProcessMouseScroll(float yoffset);

private:
    void UpdateCameraVectors();

    // camera Attributes
    glm::vec3 position{};
    glm::vec3 front;
    glm::vec3 up{};
    glm::vec3 right{};
    glm::vec3 worldUp{};
    // euler Angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    static constexpr float YAW{-90.0f};
    static constexpr float PITCH{0.0f};
    static constexpr float SPEED{2.5f};
    static constexpr float SENSITIVITY{0.1f};
    static constexpr float ZOOM{45.0f};


};
