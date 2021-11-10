// #ifndef CAPPLICATION_H
// #define CAPPLICATION_H

// #include "../Engine/Engine.h"
// #include <map>

// class CApplication : public CEngine {
// public:
//     CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

//     void InitializeKeybinds();
//     void InitializeObjects();

//     void Update() override;

//     void UpdateCamera();
//     void UpdateObjects();
//     void UpdateControls();
    
//     void Render() override;

//     ~CApplication();

// private:
//     std::map<std::string, std::unique_ptr<CTexture>> m_Textures;
//     std::unique_ptr<CPerspectiveCamera> m_Camera;

//     glm::vec3 m_Position;

//     float m_CameraMoveSpeed;
//     float m_LastX, m_LastY;
//     float m_FieldOfView;

//     std::vector<int> m_Keys;
// };

// #endif

#pragma once

#include "../Engine/Layer.h"

class CGameLayer : public CLayer {
public:
    CGameLayer();

    void OnAttach(CWindow* window) override;
    void OnDetach() override;

    void OnUpdate(const float& dt) override;
    void OnRender() override;

    virtual ~CGameLayer() = default;

private:
    void InitializeCamera();
    void InitializeKeybinds();

    void UpdateObjects(const float& dt);
    void UpdateCamera(const float& dt);
    void UpdateControls(const float& dt);

private:
    void AddShader(std::string_view name, std::string_view vertex, std::string_view fragment, std::string_view geometry) { this->m_Shaders[name.data()] = std::make_shared<CShader>(vertex.data(), fragment.data(), geometry.data()); }
    inline CShader* GetShader(std::string_view name) { return this->m_Shaders[name.data()].get(); }

    void AddTexture(std::string_view name, std::string_view filename, GLenum type) { this->m_Textures[name.data()] = std::make_shared<CTexture>(filename.data(), type); }
    inline CTexture* GetTexture(std::string_view name) { return this->m_Textures[name.data()].get(); }

    void AddMaterial(std::string_view name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTexture, GLint specularTexture) { this->m_Materials[name.data()] = std::make_shared<CMaterial>(ambient, diffuse, specular, diffuseTexture, specularTexture); }
    inline CMaterial* GetMaterial(std::string_view name) { return this->m_Materials[name.data()].get(); }

private:
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed;

    float m_LastX, m_LastY;
    float m_FieldOfView;

private:
    std::map<std::string, Ref<CShader>> m_Shaders;
    std::map<std::string, Ref<CTexture>> m_Textures;
    std::map<std::string, Ref<CMaterial>> m_Materials;

    std::vector<CMesh*> m_Meshes;
    std::vector<CModel*> m_Models;

    Ref<CPerspectiveCamera> m_Camera;
    Ref<CInput> m_KeyboardControls;

    std::vector<int> m_Keys;

    CWindow* m_Window;
    double m_MousePositionX, m_MousePositionY;
};