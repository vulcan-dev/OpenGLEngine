#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Utilities/Logger.h"

class CCamera {
public:
    CCamera(const float& windowWidth, const float& windowHeight, const glm::vec3& position = glm::vec3(0, 0, 5), const glm::vec3& head = glm::vec3(0, 1, 0), const glm::vec3& lookAt = glm::vec3(0, 0, 0));

    glm::mat4 GetProjection() { return this->m_Projection; }
    glm::mat4 GetView() { return this->m_View; }

    glm::vec3 GetPosition() { return this->m_PositionWorldSpace; }
    glm::vec3 GetLookAt() { return this->m_LookAt; }
    glm::vec3 GetHead() { return this->m_Head; }

    void LookAt(const glm::vec3 lookAt) {
        this->m_LookAt = lookAt;
    }

    void SetPosition(const glm::vec3& position) {
        this->m_PositionWorldSpace = position;

        this->m_View = glm::lookAt(
            this->m_PositionWorldSpace,
            this->m_LookAt,
            this->m_Head
        );

        CORE_DEBUG("m_LookAt: {}", glm::to_string(this->m_LookAt));
    }
    
    void SetLookAt(const glm::vec3& lookAt) { this->m_LookAt = lookAt; }
    void SetHead(const glm::vec3& head) { this->m_Head = head; }

    void SetFieldOfView(const float& fov) { this->m_FieldOfView = fov; }
private:
    glm::mat4 m_Projection;
    glm::mat4 m_View;

    glm::vec3 m_PositionWorldSpace;
    glm::vec3 m_LookAt;
    glm::vec3 m_Head;

    float m_FieldOfView;
};

#endif