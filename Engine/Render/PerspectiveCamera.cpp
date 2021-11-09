#include "PerspectiveCamera.h"

#include "../Core/Utilities/Logger.h"

CPerspectiveCamera::CPerspectiveCamera(const float& width, const float& height, const glm::vec3& position, const glm::vec3& up, const float& yaw, const float& pitch) {
    this->m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->m_MovementSpeed = 2.5f;
    this->m_MouseSensitivity = .1f;
    this->m_FieldOfView = 60;

    this->m_Projection = glm::perspective(glm::radians(this->m_FieldOfView), width / height, 0.1f, 1000.0f);
    this->m_Position = position;
    this->m_WorldUp = up;
    this->m_Yaw = yaw;
    this->m_Pitch = pitch;

    this->UpdateCameraVectors();
}

void CPerspectiveCamera::UpdateUniforms(CShader* shader) {
    auto vm = this->GetProjection() * this->GetView() * glm::mat4(1.f);

    shader->SetMat4fv(vm, "VP");
    shader->SetVec3f(this->m_Position, "cameraPos");
}

void CPerspectiveCamera::Update(float xoffset, float yoffset, bool constrainPitch) {
    this->ProcessMouseMovement(xoffset, yoffset, constrainPitch);
    this->UpdateCameraVectors();
}

void CPerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, const bool& constrainPitch) {
    xoffset *= this->m_MouseSensitivity;
    yoffset *= this->m_MouseSensitivity;

    this->m_Yaw += xoffset;
    this->m_Pitch += yoffset;

    if (constrainPitch) {
        if (this->m_Pitch > 89.0f) this->m_Pitch = 89.0f;
        if (this->m_Pitch < -89.0f) this->m_Pitch = -89.0f;
    }
}

void CPerspectiveCamera::UpdateCameraVectors() {
    this->m_Front.x = cos(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
    this->m_Front.y = sin(glm::radians(this->m_Pitch));
    this->m_Front.z = sin(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));

    this->m_Front = glm::normalize(this->m_Front);
    this->m_Right = glm::normalize(glm::cross(this->m_Front, this->m_WorldUp));
    this->m_Up = glm::normalize(glm::cross(this->m_Right, this->m_Front));
}