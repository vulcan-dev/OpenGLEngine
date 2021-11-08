#include "Skybox.h"

#include "Shader.h"

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "Core/stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

unsigned long ic;

CSkybox::CSkybox(CCamera* camera, std::vector<std::string> faces) {
    if (faces.empty()) {
        faces = {
            "Skybox/Default/right.jpg",
            "Skybox/Default/left.jpg",
            "Skybox/Default/top.jpg",
            "Skybox/Default/bottom.jpg",
            "Skybox/Default/front.jpg",
            "Skybox/Default/back.jpg"
        };
    }

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
}

void CSkybox::UpdateUniforms(CShader* shader) {
    shader->SetMat4fv(this->m_ModelMatrix, "ModelMatrix");
}

void CSkybox::UpdateModelMatrix() {
    this->m_ModelMatrix = glm::mat4(1.f);
    this->m_ModelMatrix = glm::translate(this->m_ModelMatrix, this->m_Origin);
    this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->m_ModelMatrix = glm::translate(this->m_ModelMatrix, this->m_Position - this->m_Origin);
    this->m_ModelMatrix = glm::scale(this->m_ModelMatrix, this->m_Scale);
}

void CSkybox::Render(CShader* shader, CCamera* camera) {
    this->UpdateModelMatrix();
    this->UpdateUniforms(shader);

    this->m_ViewMatrix = glm::mat4(glm::mat3(camera->GetView()));

    shader->SetMat4fv(this->m_ViewMatrix, "ModelMatrix");
    shader->SetMat4fv(camera->GetProjection(), "VP");

    shader->Bind();
    glDepthFunc(GL_LEQUAL);

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
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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