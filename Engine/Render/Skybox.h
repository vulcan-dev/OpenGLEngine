#ifndef SKYBOX_H
#define SKYBOX_H

#include "Camera.h"
#include "Shader.h"
#include <GL/glew.h>
#include "Mesh/Vertex.h"
#include "Mesh/Texture.h"
#include <string>

class CSkybox {
public:
    CSkybox(CCamera* camera, CTexture* a = nullptr, CTexture* b = nullptr, std::vector<std::string> faces = std::initializer_list<std::string>{});
    unsigned int LoadCubemap(std::vector<std::string> faces);
    void Render(CShader* shader, CCamera* camera);

private:
    void UpdateUniforms(CShader* shader);
    void UpdateModelMatrix();

private:
    glm::mat4 m_ViewMatrix, m_ModelMatrix = glm::mat4(1.f);
    GLuint m_ViewMatrixID, m_ModelMatrixID = 0;

	glm::vec3 m_Position;
	glm::vec3 m_Origin;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

    CCamera* m_Camera;
    GLuint m_VAO, m_VBO = 0;
    GLuint m_ProgramID = 0;

    CTexture* m_TextureDiffuse;
    CTexture* m_TextureSpecular;

    // glm::vec3 m_Position, m_Rotation, m_Scale = glm::vec3(0.f);
    unsigned int texture;
};

#endif