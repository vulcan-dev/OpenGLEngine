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

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(const float& dt) override;
    void OnRender() override;

    virtual ~CGameLayer() = default;
};