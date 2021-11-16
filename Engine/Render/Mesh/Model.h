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
            this->m_Material->SendToShader(*shader);

            if (Visible) {
                this->m_Mesh->Render(shader);
            }
		}

        inline bool Intersects(const glm::vec3 ray, const glm::mat4& projection, const glm::mat4 view) {
            // https://stackoverflow.com/questions/40276068/opengl-raycasting-with-any-object
            const glm::mat4 model = this->m_Mesh->m_ModelMatrix;
            GLint viewi[4];
            glGetIntegerv(GL_VIEWPORT, reinterpret_cast<GLint *>(&viewi));
            glm::vec3 v1 = glm::unProject(glm::vec3(ray.x, ray.y, 0), model, projection, glm::vec4(viewi[0], viewi[1], 1.f, 0.f));
            glm::vec3 v2 = glm::unProject(glm::vec3(ray.x, ray.y, 1), model, projection, glm::vec4(viewi[0], viewi[1], 1.f, 0.f));

            float t = (0 - v1.z) / (v1.z - v1.z);

            float x = (1 - t) * v1.x + t * v2.x;
            float y = (1 - t) * v1.y + t * v2.y;

            glm::vec3 intersection(x, y, 0);

            return true;
        }

        inline const std::string& GetDisplayName() const { return this->m_DisplayName; }
        inline const glm::mat4& GetModel() const { return this->m_Mesh->m_ModelMatrix; }

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