#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

#include <vector>

class CCamera {
public:
    CCamera(
        const CCamera& obj,
        const float& width, const float& height, 
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), 
        const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), 
        const float& yaw = -90.f, const float& pitch = 0.f
    ) {
        this->m_Position = position;
        this->m_WorldUp = up;
        this->m_Yaw = yaw;
        this->m_Pitch = pitch;
    }

    virtual void Update(float xoffset, float yoffset, bool constrainPitch) = 0;
    virtual void UpdateUniforms(CShader* shader) = 0;

    virtual inline const glm::mat4& GetProjection() = 0;
    virtual inline glm::mat4 GetView() = 0;

    virtual inline const glm::vec3& GetPosition() = 0;
    virtual inline const glm::vec3& GetFront() = 0;
    virtual inline const glm::vec3& GetRight() = 0;
    virtual inline const glm::vec3& GetWorldUp() = 0;
    virtual inline const glm::vec3& GetUp() = 0;

    virtual void SetPosition(const glm::vec3& position) = 0;
    virtual void SetMovementSpeed(const float& speed) = 0;
    virtual void SetFieldOfView(const float& fov) = 0;
    virtual void SetMouseSensitivity(const float& sensitivity) = 0;

protected:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::mat4 m_Projection;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;

    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_FieldOfView;

protected:
    virtual void UpdateCameraVectors() = 0;
    virtual void ProcessMouseMovement(float xoffset, float yoffset, const bool& constrainPitch = true) = 0;
};

#endif