#ifndef SKYBOX_H
#define SKYBOX_H

#include "Core/Camera.h"
#include <GL/glew.h>
#include <string>

class CSkybox {
public:
    CSkybox(CCamera* camera);
    unsigned int LoadCubemap(std::vector<std::string> faces);
    void Render();

private:
    glm::mat4 m_ViewMatrix, m_ModelMatrix = glm::mat4(1.f);
    GLuint m_ViewMatrixID, m_ModelMatrixID = 0;

    CCamera* m_Camera;
    GLuint m_VAO, m_VBO = 0;
    GLuint m_ProgramID = 0;

    glm::vec3 m_Position, m_Rotation, m_Scale = glm::vec3(0.f);
    unsigned int texture;
};

#endif