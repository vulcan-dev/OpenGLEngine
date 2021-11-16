#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

namespace VK {
    class CPerspectiveCamera {
    public:
        CPerspectiveCamera(
            const float& width, const float& height, 
            const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), 
            const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), 
            const float& yaw = -90.f, const float& pitch = 0.f
        );

        void Update(float xoffset, float yoffset, bool constrainPitch);
        void UpdateUniforms(CShader* shader);

        inline const glm::mat4& GetProjection() { return this->m_Projection; }
        inline glm::mat4 GetView() { return glm::lookAt(this->m_Position, this->m_Position + this->m_Front, this->m_Up); }
        inline glm::vec4 GetEye(int mouse_x, int mouse_y, int width, int height) {
            float x = (2.0f * mouse_x) / width - 1.0f;
            float y = 1.0f - (2.0f * mouse_y) / height;
            float z = 1.0f;
            glm::vec3 ray_nds = glm::vec3(x, y, z);

            glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
            glm::vec4 ray_eye = inverse(this->GetProjection()) * ray_clip;
            ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
            return ray_eye;
        }

        inline glm::vec3 RayWorld(int mouse_x, int mouse_y, int width, int height) {
            glm::vec3 ray_word = (inverse(this->GetView()) * this->GetEye(mouse_x, mouse_y, width, height));
            return glm::normalize(ray_word);
        }

        inline const glm::vec3& GetPosition() { return this->m_Position; }
        inline const glm::vec3& GetFront() { return this->m_Front; };
        inline const glm::vec3& GetRight() { return this->m_Right; };
        inline const glm::vec3& GetWorldUp() { return this->m_WorldUp; };
        inline const glm::vec3& GetUp() { return this->m_Up; };

    public:
        void SetPosition(const glm::vec3& position) { this->m_Position = position; }
        void SetMovementSpeed(const float& speed) { this->m_MovementSpeed = speed; }
        void SetFieldOfView(const float& fov) { this->m_FieldOfView = fov; }
        void SetMouseSensitivity(const float& sensitivity) { this->m_MouseSensitivity = sensitivity; }

    private:
        void UpdateCameraVectors();
        void ProcessMouseMovement(float xoffset, float yoffset, const bool& constrainPitch = true);

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
    };
}