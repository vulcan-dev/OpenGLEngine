#pragma once

#include "Shader.h"
#include "Mesh/Texture.h"
#include "PerspectiveCamera.h"
#include "../Core/Window.h"

#include <map>

namespace VK {
    class CSkybox {
    public:
        CSkybox(CWindow* window, std::string_view hdrpath, CPerspectiveCamera* camera, glm::vec3 cameraPos);

        void Render(CPerspectiveCamera* camera, glm::vec3 cameraPos);
        unsigned int GetIMap() { return m_IrradianceMap; }
        unsigned int GetPFMap() { return m_PrefilterMap; }
        unsigned int GetBRDFLUTT() { return m_brdfLUTTexture; }

        void SetRotY(float rot) { this->m_rot = rot; };

        ~CSkybox() = default;

    private:
        void InitializeShaders();
        void InitializeHDR();
        void InitializeCubemap(CPerspectiveCamera* camera, glm::vec3 cameraPos);
        void RenderSkyboxCube();


        void UpdateUniforms(CPerspectiveCamera* camera, glm::vec3 cameraPos);
        void UpdateViewMatrix(CPerspectiveCamera* camera);

    private:
        void AddShader(std::string_view name, std::string_view vertex, std::string_view fragment, std::string_view geometry = "") { this->m_Shaders[name.data()] = std::make_shared<CShader>(vertex.data(), fragment.data()); }
        inline CShader* GetShader(std::string_view name) { return this->m_Shaders[name.data()].get(); }

        void AddTexture(std::string_view name, std::string_view filename, GLenum type) { this->m_Textures[name.data()] = std::make_shared<CTexture>(filename.data(), type); }
        inline CTexture* GetTexture(std::string_view name) { return this->m_Textures[name.data()].get(); }

    private:
        std::map<std::string, Ref<CShader>> m_Shaders;
        std::map<std::string, Ref<CTexture>> m_Textures;
        unsigned int m_Texture;
        unsigned int m_IrradianceMap, m_PrefilterMap, m_brdfLUTTexture;
        glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
        float m_rot = 0;

        unsigned int m_Cubemap;
        CWindow* m_Window;

        std::string m_HDRPath;
    };
}