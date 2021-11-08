#include "Skybox.h"

#include "Core/Utilities/Shader.h"

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "Core/stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

unsigned long ic;

CSkybox::CSkybox(CCamera* camera) {
    float vertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,

        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,

        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,

        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    std::vector<std::string> faces = {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg"
    };

    auto vertexCount = sizeof(vertices) / sizeof(float);

    this->texture = LoadCubemap(faces);
    this->m_Camera = camera;

    glGenVertexArrays(1, &this->m_VAO);
    glBindVertexArray(this->m_VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenBuffers(1, &this->m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);;
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);   

    this->m_ProgramID = Shader::LoadFromFile("Shaders/Skybox.vs", "Shaders/Skybox.fs");
    this->m_ViewMatrixID = glGetUniformLocation(this->m_ProgramID, "VP");

    this->m_ViewMatrix = glm::mat4(1.f);
    this->m_ViewMatrix = camera->GetView() * glm::mat4(1.f);

    this->m_ModelMatrixID = glGetUniformLocation(this->m_ProgramID, "ModelMatrix");

    glUseProgram(this->m_ProgramID);
    glUniformMatrix4fv(this->m_ViewMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_ViewMatrix));
    glUniformMatrix4fv(this->m_ViewMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_Camera->GetProjection()));
    glUseProgram(0);

    CORE_DEBUG("{}", glm::to_string(this->m_Camera->GetView()));
}

void CSkybox::Render() {
    glDepthFunc(GL_LEQUAL);
    glUseProgram(m_ProgramID);
    this->m_ViewMatrix = glm::mat4(1.f);
    this->m_ViewMatrix = glm::mat4(glm::mat3(this->m_Camera->GetView()));

    glUniformMatrix4fv(this->m_ModelMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_ViewMatrix));
    glUniformMatrix4fv(this->m_ViewMatrixID, 1, GL_FALSE, glm::value_ptr(this->m_Camera->GetProjection()));

    glDepthMask(GL_FALSE);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    glBindVertexArray(this->m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);

    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    glActiveTexture(0);
    glUseProgram(0);
}

unsigned int CSkybox::LoadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(fmt::format("../{}/{}", ROOT_DIR, faces[i].c_str()).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        } else {
            CORE_ERROR("Failed loading cubemap: {}", faces[i]);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}