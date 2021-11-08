#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "../Core/Engine.h"
#include "../Core/Input.h"
#include "../Skybox.h"
#include "../Cube.h"

class CApplication : public CEngine {
public:
    CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    void InitializeKeybinds();
    void InitializeObjects();

    void Update();
    void UpdateCamera();
    void UpdateObjects();
    void UpdateControls();
    void Render();

    ~CApplication();

private:
    std::vector<std::shared_ptr<CCube>> m_Cubes;

    std::unique_ptr<CCamera> m_Camera;
    std::unique_ptr<CInput> m_Input;

    std::unique_ptr<CSkybox> m_Skybox;

    glm::vec3 m_Position;
    float m_CameraMoveSpeed;

    float m_LastX, m_LastY;
    float m_FieldOfView;

    std::vector<int> m_Keys;
};

#endif