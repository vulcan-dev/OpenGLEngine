#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class CCube {
public:
    CCube();

    void SetPosition(const glm::vec3& pos);
    void SetRotation(const float& angle);
    void SetRotationX(const float& angle);
    void SetRotationY(const float& angle);
    void SetRotationZ(const float& angle);

    void Render();

private:
    glm::mat4 mvp, ModelMatrix;
    GLuint MatrixID, ModelMatrixID;
    GLuint programID;
    GLuint VAID, vertexbuffer, colorbuffer;
};

#endif