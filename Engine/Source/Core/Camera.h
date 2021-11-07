#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class CCamera {
public:
    CCamera(const float& width, const float& height, const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), const float& yaw = -90.f, const float& pitch = 0.f);

    void Update(float xoffset, float yoffset, bool constrainPitch);

    inline const glm::mat4& GetProjection() const { return this->m_Projection; }
    inline glm::mat4 GetView() { return glm::lookAt(this->m_Position, this->m_Position + this->m_Front, this->m_Up); }

    inline const glm::vec3& GetFront() const { return this->m_Front; };
    inline const glm::vec3& GetRight() const { return this->m_Right; };
    inline const glm::vec3& GetWorldUp() const { return this->m_WorldUp; };
    inline const glm::vec3& GetUp() const { return this->m_Up; };

    void SetPosition(glm::vec3 pos) { this->m_Position = pos; }
private:
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

private:
    void UpdateCameraVectors();
    void ProcessMouseMovement(float xoffset, float yoffset, const bool& constrainPitch = true);
};

#endif