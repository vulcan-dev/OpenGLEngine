#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "../Engine/Engine.h"
#include <map>

class CApplication : public CEngine {
public:
    CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    void InitializeKeybinds();
    void InitializeObjects();

    void Update() override;
    void UpdateCamera();
    void UpdateObjects();
    void UpdateControls();
    
    void Render() override;

    ~CApplication();

private:
    // std::unique_ptr<CShader> m_Shader;
    std::map<std::string, std::unique_ptr<CShader>> m_Shaders;

    std::unique_ptr<CCamera> m_Camera;
    std::unique_ptr<CInput> m_Input;

    std::unique_ptr<CMaterial> m_Material;
    std::unique_ptr<CTexture> m_Sheen;
    std::unique_ptr<CTexture> m_Specular;
    std::unique_ptr<CTexture> m_Sky;
    std::vector<CMesh*> m_Meshes;
    std::vector<CModel*> m_Models;

    std::unique_ptr<CSkybox> m_Skybox;

    glm::vec3 m_Position;
    float m_CameraMoveSpeed;

    float m_LastX, m_LastY;
    float m_FieldOfView;

    std::vector<int> m_Keys;
};

#endif