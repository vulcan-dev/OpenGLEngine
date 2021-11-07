#include "Cube.h"

#include "Core/Utilities/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Core/Vertex.h"

unsigned long indicieCount;

uint8_t cubeCount;

CCube::CCube(CCamera* camera, const glm::vec3& colour) {
    Vertex vertices[] = {
        // side 1
        glm::vec3(-1.0f,-1.0f,-1.0f), colour,
        glm::vec3(-1.0f,-1.0f, 1.0f), colour,
        glm::vec3(-1.0f, 1.0f, 1.0f), colour,

        glm::vec3(1.0f, 1.0f,-1.0f), colour,
        glm::vec3(-1.0f,-1.0f,-1.0f), colour,
        glm::vec3(-1.0f, 1.0f,-1.0f), colour,

        // side 2
        glm::vec3(1.0f,-1.0f, 1.0f), colour,
        glm::vec3(-1.0f,-1.0f,-1.0f), colour,
        glm::vec3(1.0f,-1.0f,-1.0f), colour,

        glm::vec3(1.0f, 1.0f,-1.0f), colour,
        glm::vec3(1.0f,-1.0f,-1.0f), colour,
        glm::vec3(-1.0f,-1.0f,-1.0f), colour,

        // side 3
        glm::vec3(-1.0f,-1.0f,-1.0f), colour,
        glm::vec3(-1.0f, 1.0f, 1.0f), colour,
        glm::vec3(-1.0f, 1.0f,-1.0f), colour,

        glm::vec3(1.0f,-1.0f, 1.0f), colour,
        glm::vec3(-1.0f,-1.0f, 1.0f), colour,
        glm::vec3(-1.0f,-1.0f,-1.0f), colour,

        // side 4
        glm::vec3(-1.0f, 1.0f, 1.0f), colour,
        glm::vec3(-1.0f,-1.0f, 1.0f), colour,
        glm::vec3(1.0f,-1.0f, 1.0f), colour,

        glm::vec3(1.0f, 1.0f, 1.0f), colour,
        glm::vec3(1.0f,-1.0f,-1.0f), colour,
        glm::vec3(1.0f, 1.0f,-1.0f), colour,

        // side 5
        glm::vec3(1.0f,-1.0f,-1.0f), colour,
        glm::vec3(1.0f, 1.0f, 1.0f), colour,
        glm::vec3(1.0f,-1.0f, 1.0f), colour,

        glm::vec3(1.0f, 1.0f, 1.0f), colour,
        glm::vec3(1.0f, 1.0f,-1.0f), colour,
        glm::vec3(-1.0f, 1.0f,-1.0f), colour,

        // side 6
        glm::vec3(1.0f, 1.0f, 1.0f), colour,
        glm::vec3(-1.0f, 1.0f,-1.0f), colour,
        glm::vec3(-1.0f, 1.0f, 1.0f), colour,

        glm::vec3(1.0f, 1.0f, 1.0f), colour,
        glm::vec3(-1.0f, 1.0f, 1.0f), colour,
        glm::vec3(1.0f,-1.0f, 1.0f), colour,
    };
    GLuint indices[] = {
        // 1
        0, 1, 2,
        3, 4, 5,

        // 2
        6, 7, 8,
        9, 10, 11,
        
        // 3
        12, 13, 14,
        15, 16, 17,

        // 4
        18, 19, 20,
        21, 22, 23,

        // 5
        24, 25, 26,
        27, 28, 29,

        // 6
        30, 31, 32,
        33, 34, 35
    };

#ifdef DEBUG_MODE
    cubeCount++;
#endif

    this->m_Camera = camera;

    // auto vertexCount = sizeof(vertices) / sizeof(Vertex);
    indicieCount = sizeof(indices) / sizeof(GLuint);

    glCreateVertexArrays(1, &this->m_VAO);
    glBindVertexArray(this->m_VAO);

    glGenBuffers(1, &this->m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);   

    this->m_ProgramID = Shader::LoadFromFile("Shaders/SimpleVertexShader.vs", "Shaders/SimpleFragmentShader.fs");
    this->m_ViewMatrixID = glGetUniformLocation(this->m_ProgramID, "VP");

    this->m_Rotation = glm::vec3(0.f);
    this->m_Position = glm::vec3(0.f);
    this->m_Scale = glm::vec3(1.f);

    this->m_ViewMatrix = glm::mat4(1.f);
    this->m_ViewMatrix = camera->GetProjection() * camera->GetView() * glm::mat4(1.f);

    this->m_ModelMatrix = glm::mat4(1.f);
    this->m_ModelMatrix *= glm::translate(glm::mat4(1.f), this->m_Position);
    this->m_ModelMatrix *= glm::rotate(glm::mat4(1.f), glm::radians(this->m_Rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->m_ModelMatrix *= glm::rotate(glm::mat4(1.f), glm::radians(this->m_Rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->m_ModelMatrix *= glm::rotate(glm::mat4(1.f), glm::radians(this->m_Rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->m_ModelMatrix *= glm::scale(glm::mat4(1.f), this->m_Scale);

    this->m_ModelMatrixID = glGetUniformLocation(this->m_ProgramID, "ModelMatrix");

    glUseProgram(this->m_ProgramID);
    glUniformMatrix4fv(this->m_ViewMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_ViewMatrix));
    glUniformMatrix4fv(this->m_ModelMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_ModelMatrix));
    glUseProgram(0);
}

void CCube::Render() {    
    this->m_ViewMatrix = glm::mat4(1.f);
    this->m_ViewMatrix = this->m_Camera->GetProjection() * this->m_Camera->GetView() * glm::mat4(1.f);

    this->m_ModelMatrix = glm::mat4(1.f);
    this->m_ModelMatrix *= glm::translate(glm::mat4(1.f), this->m_Position);
    this->m_ModelMatrix *= glm::rotate(glm::mat4(1.f), glm::radians(this->m_Rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->m_ModelMatrix *= glm::rotate(glm::mat4(1.f), glm::radians(this->m_Rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->m_ModelMatrix *= glm::rotate(glm::mat4(1.f), glm::radians(this->m_Rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->m_ModelMatrix *= glm::scale(glm::mat4(1.f), this->m_Scale);

    glUseProgram(m_ProgramID);
    glUniformMatrix4fv(this->m_ViewMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_ViewMatrix));
    glUniformMatrix4fv(m_ModelMatrixID, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, indicieCount, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glUseProgram(0);
}

void CCube::SetRotation(const float& angle) {
    this->m_Rotation.x = angle;
    this->m_Rotation.y = angle;
    this->m_Rotation.z = angle;
}

void CCube::SetPosition(const glm::vec3& pos) {
    this->m_Position = pos;
}

void CCube::SetRotationX(const float& angle) {
    this->m_Rotation.x = angle;
}

void CCube::SetRotationY(const float& angle) {
    this->m_Rotation.y = angle;
}

void CCube::SetRotationZ(const float& angle) {
    this->m_Rotation.z = angle;
}