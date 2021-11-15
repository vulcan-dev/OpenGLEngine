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
		CModel(const std::string& displayName, glm::vec3 position, CMaterial* material, CTexture* orTexDif, CTexture* orTexSpec, Ref<CMesh>& mesh) {
			this->m_Position = position;
            this->m_Rotation = glm::vec3(0.f);
			this->m_Material = material;
			this->m_OverrideTextureDiffuse = orTexDif;
			this->m_OverrideTextureSpecular = orTexSpec;

            this->m_Mesh = std::make_shared<CMesh>(mesh);

            this->m_Mesh->SetPosition(this->m_Position);
            this->m_Mesh->SetOrigin(this->m_Position);
            this->m_DisplayName = displayName;
		}

        // Model
		CModel(const std::string& displayName, const glm::vec3& position, CMaterial* material, CTexture* orTexDif, CTexture* orTexSpec, const char* objFile) {
			this->m_Position = position;
            this->m_Rotation = glm::vec3(0.f);
			this->m_Material = material;
			this->m_OverrideTextureDiffuse = orTexDif;
			this->m_OverrideTextureSpecular = orTexSpec;
            this->m_DisplayName = displayName;

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
		}

		~CModel() = default;

		void Render(CShader* shader) {
			this->UpdateUniforms();

            if (Visible) {
                this->m_Mesh->Render(shader);
            }
		}

        inline const std::string& GetDisplayName() const { return this->m_DisplayName; }

    public:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        bool Visible = true;

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
        std::string m_DisplayName;
	};
}