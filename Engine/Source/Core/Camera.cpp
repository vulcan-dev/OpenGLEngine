#include "Camera.h"

#include "Utilities/Logger.h"

CCamera::CCamera(const float& width, const float& height, const glm::vec3& position, const glm::vec3& up, const float& yaw, const float& pitch) {
    this->m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->m_MovementSpeed = 2.5f;
    this->m_MouseSensitivity = .1f;
    this->m_FieldOfView = 60;

    this->m_Projection = glm::perspective(glm::radians(this->m_FieldOfView), width / height, 0.1f, 100.0f);
    this->m_Position = position;
    this->m_WorldUp = up;
    this->m_Yaw = yaw;
    this->m_Pitch = pitch;
    this->UpdateCameraVectors();
}

void CCamera::Update(float xoffset, float yoffset, bool constrainPitch) {
    this->ProcessMouseMovement(xoffset, yoffset, constrainPitch);
    this->UpdateCameraVectors();
}

void CCamera::ProcessMouseMovement(float xoffset, float yoffset, const bool& constrainPitch) {
    xoffset *= this->m_MouseSensitivity;
    yoffset *= this->m_MouseSensitivity;

    this->m_Yaw += xoffset;
    this->m_Pitch += yoffset;

    if (constrainPitch) {
        if (this->m_Pitch > 89.0f) this->m_Pitch = 89.0f;
        if (this->m_Pitch < -89.0f) this->m_Pitch = -89.0f;
    }
}

void CCamera::UpdateCameraVectors() {
    glm::vec3 front;

    front.x = cos(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
    front.y = sin(glm::radians(this->m_Pitch));
    front.z = sin(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));

    this->m_Front = glm::normalize(front);
    this->m_Right = glm::normalize(glm::cross(this->m_Front, this->m_WorldUp));
    this->m_Up = glm::normalize(glm::cross(this->m_Right, this->m_Front));
}