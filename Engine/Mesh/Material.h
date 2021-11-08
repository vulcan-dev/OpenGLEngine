#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../Shader.h"

class CMaterial {
public:
    CMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTexture, GLint specularTexture) {
        this->m_Ambient = ambient;
        this->m_Diffuse = diffuse;
        this->m_Specular = specular;
        this->m_DiffuseTexture = diffuseTexture;
        this->m_SpecularTexture = specularTexture;
    }

    void SendToShader(CShader& program) {
		program.SetVec3f(this->m_Ambient, "material.ambient");
		program.SetVec3f(this->m_Diffuse, "material.diffuse");
		program.SetVec3f(this->m_Specular, "material.specular");
		program.Set1i(this->m_DiffuseTexture, "material.diffuseTex");
		program.Set1i(this->m_SpecularTexture, "material.specularTex");
    }

    ~CMaterial() = default;

private:
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;

    GLint m_DiffuseTexture;
    GLint m_SpecularTexture;
};

#endif