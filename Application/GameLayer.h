#pragma once

#include <any>
#include "../Engine/Layer.h"

#include "Interface.h"
#include "Events.h"
#include "../Engine/Application.h"

class CGameLayer : public VK::CLayer {
public:
    CGameLayer();

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(const float& dt) override;
    void OnRender(const float& dt) override;

    virtual ~CGameLayer() {
        glfwTerminate();
    }

private:
    void InitializeCamera();
    void InitializeKeybinds();

    void UpdateObjects(const float& dt);
    void UpdateCamera(const float& dt);
    void UpdateControls(const float& dt);

private:
    void AddShader(std::string_view name, std::string_view vertex, std::string_view fragment, std::string_view geometry = "") { this->m_Shaders[name.data()] = std::make_shared<VK::CShader>(vertex.data(), fragment.data(), geometry.data()); }
    inline VK::CShader* GetShader(std::string_view name) { return this->m_Shaders[name.data()].get(); }

    void AddTexture(std::string_view name, std::string_view filename, GLenum type) { this->m_Textures[name.data()] = std::make_shared<VK::CTexture>(filename.data(), type); }
    inline VK::CTexture* GetTexture(std::string_view name) { return this->m_Textures[name.data()].get(); }

    void AddMaterial(std::string_view name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTexture, GLint specularTexture) { this->m_Materials[name.data()] = std::make_shared<VK::CMaterial>(ambient, diffuse, specular, diffuseTexture, specularTexture); }
    inline VK::CMaterial* GetMaterial(std::string_view name) { return this->m_Materials[name.data()].get(); }

    bool AddPrimitive(std::string_view name, const glm::vec3& pos = glm::vec3(0.f));

private:
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed;

    float m_LastX, m_LastY;
    float m_FieldOfView;

private:
    std::map<std::string, Ref<VK::CShader>> m_Shaders;
    std::map<std::string, Ref<VK::CTexture>> m_Textures;
    std::map<std::string, Ref<VK::CMaterial>> m_Materials;

    std::vector<Ref<VK::CMesh>> m_Meshes;
    std::map<std::string, Ref<VK::CModel>> m_Models;

    Ref<VK::CPerspectiveCamera> m_Camera;
    Ref<VK::CSkybox> m_Skybox;

    Ref<VK::CLine> m_DebugLine;

    Ref<CInterface> m_Interface;

    std::vector<int> m_Keys;

    VK::CWindow* m_Window = nullptr;
    double m_MousePositionX, m_MousePositionY = 0;
    bool m_MouseEnabled = true;
    bool m_WasMouseEnabled = false;

    uint16_t m_PrimitiveShapeID = 0;
};