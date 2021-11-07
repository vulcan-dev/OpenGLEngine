#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include "Core/Camera.h"

class CCube {
public:
    CCube(CCamera* camera, const glm::vec3& colour = glm::vec3(1.f, 1.f, 1.f));

    void SetPosition(const glm::vec3& pos);
    void SetPositionX(const float& x) { this->m_Position[0] = x; }
    void SetPositionY(const float& y) { this->m_Position[1] = y; }
    void SetPositionZ(const float& z) { this->m_Position[2] = z; }

    void SetRotation(const float& angle);
    void SetRotationX(const float& angle);
    void SetRotationY(const float& angle);
    void SetRotationZ(const float& angle);

    inline glm::vec3 GetPosition() { return this->m_Position; }

    void Render();

private:
    glm::mat4 m_ViewMatrix, m_ModelMatrix = glm::mat4(1.f);
    GLuint m_ViewMatrixID, m_ModelMatrixID = 0;

    glm::vec3 m_Position, m_Rotation, m_Scale = glm::vec3(0.f);

    GLuint m_ProgramID = 0;
    GLuint m_VAO, m_VBO = 0;

    CCamera* m_Camera;
};

#endif

extern uint8_t m_CubeCount;