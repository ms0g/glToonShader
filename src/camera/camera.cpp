#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch) :
        m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_movementSpeed(SPEED),
        m_mouseSensitivity(SENSITIVITY),
        m_zoom(ZOOM) {
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
        m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_movementSpeed(SPEED),
        m_mouseSensitivity(SENSITIVITY),
        m_zoom(ZOOM) {
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
}

void Camera::update(CameraSettings& settings) {
    // update the position
    m_position.x = settings.x;
    m_position.y = settings.y;
    m_position.z = settings.z;

    m_yaw = settings.yaw;
    m_pitch = settings.pitch;

    m_zoom = settings.zoom;

    // calculate the new Front vector
    glm::vec3 _front;
    _front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    _front.y = sin(glm::radians(m_pitch));
    _front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(_front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = m_movementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD)
        m_position += m_front * velocity;
    if (direction == CameraMovement::BACKWARD)
        m_position -= m_front * velocity;
    if (direction == CameraMovement::LEFT)
        m_position -= m_right * velocity;
    if (direction == CameraMovement::RIGHT)
        m_position += m_right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;
}

void Camera::processMouseScroll(float yoffset) {
    m_zoom -= (float) yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}



