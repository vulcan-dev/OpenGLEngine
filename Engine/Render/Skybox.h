#pragma once

#include "Shader.h"
#include "Mesh/Texture.h"
#include "PerspectiveCamera.h"
#include "../Core/Window.h"

#include <map>

class CSkybox {
public:
    CSkybox(CWindow* window, CPerspectiveCamera* camera, glm::vec3 cameraPos);

    void Render(CPerspectiveCamera* camera, glm::vec3 cameraPos);

    ~CSkybox();

private:
    void InitializeShaders();
    void InitializeHDR();
    void InitializeCubemap(CPerspectiveCamera* camera, glm::vec3 cameraPos);

    void UpdateUniforms(CPerspectiveCamera* camera, glm::vec3 cameraPos);
	void UpdateViewMatrix(CPerspectiveCamera* camera);

private:
    void AddShader(std::string_view name, std::string_view vertex, std::string_view fragment, std::string_view geometry = "") { this->m_Shaders[name.data()] = std::make_shared<CShader>(vertex.data(), fragment.data()); }
    inline CShader* GetShader(std::string_view name) { return this->m_Shaders[name.data()].get(); }

private:
    std::map<std::string, Ref<CShader>> m_Shaders;
    unsigned int m_Texture;

    unsigned int m_Cubemap, m_Irradiance;
    CWindow* m_Window;
};