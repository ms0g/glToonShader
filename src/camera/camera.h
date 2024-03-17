#pragma once

#include "glm/glm.hpp"
#include "cameraSettings.hpp"
#include "../configs/configs.hpp"

class Camera {
public:
    explicit Camera(const glm::vec3& position = glm::vec3{0.0f, 0.0f, 0.0f},
                    const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void update(CameraSettings& settings);

    glm::mat4 getViewMatrix();

    [[nodiscard]]
    inline float getZoom() const { return m_zoom; }

    [[nodiscard]]
    inline const glm::vec3& getPosition() const { return m_position; }

    [[nodiscard]]
    inline const glm::vec3& getFront() const { return m_front; }

    void processKeyboard(CameraMovement direction, float deltaTime);

    void processMouseMovement(float xoffset, float yoffset);

    void processMouseScroll(float yoffset);

private:
    // camera Attributes
    glm::vec3 m_position{};
    glm::vec3 m_front;
    glm::vec3 m_up{};
    glm::vec3 m_right{};
    glm::vec3 m_worldUp{};
    // euler Angles
    float m_yaw;
    float m_pitch;
    // camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;


};
