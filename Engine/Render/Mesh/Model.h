#ifndef MODEL_H
#define MODEL_H

#include "../Shader.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"
#include "../../Core/OBJLoader.h"
#include <vector>

class CModel {
public:
    CModel(glm::vec3 position, CMaterial* material, CTexture* orTexDif, CTexture* orTexSpec, std::vector<Ref<CMesh>>& meshes) {
		this->m_Position = position;
		this->m_Material = material;
		this->m_OverrideTextureDiffuse = orTexDif;
		this->m_OverrideTextureSpecular = orTexSpec;

		for (auto& i : meshes) {
			this->m_Meshes.push_back(std::make_shared<CMesh>(i));
		}

		for (auto& i : this->m_Meshes) {
			i->SetPosition(this->m_Position);
			i->SetOrigin(this->m_Position);
		}
	}

	//OBJ file loaded model
	CModel(glm::vec3 position, CMaterial* material, CTexture* orTexDif, CTexture* orTexSpec, const char* objFile) {
		this->m_Position = position;
		this->m_Material = material;
		this->m_OverrideTextureDiffuse = orTexDif;
		this->m_OverrideTextureSpecular = orTexSpec;

		std::vector<Vertex> mesh = LoadOBJ(objFile);
		this->m_Meshes.push_back(std::make_shared<CMesh>(
			mesh.data(),
			GL_TRIANGLES,
			mesh.size(),
			nullptr,
			0,
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		));

		// this->m_Meshes.push_back(
		// 	std::make_shared<CMesh>(
		// 		mesh,
		// 		GL_TRIANGLES,
		// 		mesh.size(),
		// 		NULL,
		// 		0,
		// 		glm::vec3(1.f, 0.f, 0.f),
		// 		glm::vec3(0.f),
		// 		glm::vec3(0.f),
		// 		glm::vec3(1.f)
		// 	)
		// );

		for (auto& i : this->m_Meshes) {
			i->Move(this->m_Position);
			i->SetOrigin(this->m_Position);
		}
	}

	~CModel() {

	}

	void Render(CShader* shader) {
		this->UpdateUniforms();
		// this->m_Material->SendToShader(*shader);

		// // shader->Bind();

		for (auto& i : this->m_Meshes) {
			// this->m_OverrideTextureDiffuse->Bind(0);
			// this->m_OverrideTextureSpecular->Bind(1);

			i->Render(shader); //Activates shader also
		}
	}

private:
    void UpdateUniforms() {

	}

private:
    CMaterial* m_Material;
    CTexture* m_OverrideTextureDiffuse;
    CTexture* m_OverrideTextureSpecular;
    std::vector<Ref<CMesh>> m_Meshes;
    glm::vec3 m_Position;
};

#endif