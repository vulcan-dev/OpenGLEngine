#pragma once

#include "../Shader.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"
#include "../../Core/OBJLoader.h"
#include <vector>

namespace VK {
	class CModel {
	public:
		CModel(glm::vec3 position, CMaterial* material, CTexture* orTexDif, CTexture* orTexSpec, Ref<CMesh>& mesh) {
			this->m_Position = position;
			this->m_Material = material;
			this->m_OverrideTextureDiffuse = orTexDif;
			this->m_OverrideTextureSpecular = orTexSpec;

            this->m_Mesh = std::make_shared<CMesh>(mesh);

            this->m_Mesh->SetPosition(this->m_Position);
            this->m_Mesh->SetOrigin(this->m_Position);
		}

		//OBJ file loaded model
		CModel(glm::vec3 position, CMaterial* material, CTexture* orTexDif, CTexture* orTexSpec, const char* objFile) {
			this->m_Position = position;
			this->m_Material = material;
			this->m_OverrideTextureDiffuse = orTexDif;
			this->m_OverrideTextureSpecular = orTexSpec;

			std::vector<Vertex> mesh = LoadOBJ(objFile);
			this->m_Mesh = std::make_shared<CMesh>(
				mesh.data(),
				GL_TRIANGLES,
				mesh.size(),
				nullptr,
				0,
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f),
				glm::vec3(0.f),
				glm::vec3(1.f)
			);

			// this->m_Meshes.push_back(
//			 	std::make_shared<CMesh>(
//			 		mesh,
//			 		GL_TRIANGLES,
//			 		mesh.size(),
//			 		NULL,
//			 		0,
//			 		glm::vec3(1.f, 0.f, 0.f),
//			 		glm::vec3(0.f),
//			 		glm::vec3(0.f),
//			 		glm::vec3(1.f)
//			 	)
//			 );

            this->m_Mesh->SetPosition(this->m_Position);
            this->m_Mesh->SetOrigin(this->m_Position);

//			for (auto& i : this->m_Meshes) {
//				i.second->Move(this->m_Position);
//				i.second->SetOrigin(this->m_Position);
//			}
		}

		~CModel() {

		}

		void Render(CShader* shader) {
			this->UpdateUniforms();
//			 this->m_Material->SendToShader(*shader);

			// // shader->Bind();

            this->m_Mesh->Render(shader);

//			for (auto& i : this->m_Meshes) {
//				// this->m_OverrideTextureDiffuse->Bind(0);
//				// this->m_OverrideTextureSpecular->Bind(1);
//
//				i.second->Render(shader); //Activates shader also
//			}
		}

    public:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;

	private:
		void UpdateUniforms() {
            this->m_Mesh->SetPosition(this->m_Position);
            this->m_Mesh->SetRotation(this->m_Rotation);
		}

	private:
		CMaterial* m_Material;
		CTexture* m_OverrideTextureDiffuse;
		CTexture* m_OverrideTextureSpecular;
		Ref<CMesh> m_Mesh;
	};
}