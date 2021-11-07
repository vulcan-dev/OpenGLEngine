#include "Camera.h"

#include "Utilities/Logger.h"

CCamera::CCamera(const float& windowWidth, const float& windowHeight, const glm::vec3& position, const glm::vec3& head, const glm::vec3& lookAt) {
    this->m_Projection = glm::perspective(glm::radians(90.0f), windowWidth / windowHeight, 0.1f, 100.0f);
    this->m_PositionWorldSpace = position;;
    this->m_LookAt = lookAt;
    this->m_Head = head;

    this->m_View = glm::lookAt(
        position,
        lookAt,
        head
    );
}