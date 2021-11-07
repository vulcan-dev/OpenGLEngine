#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "../Core/Engine.h"
#include "../Core/Input.h"
#include "../Cube.h"

class CApplication : public CEngine {
public:
    CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    void Update();
    void UpdateCamera();
    void UpdateObjects();
    void UpdateControls();
    void Render();

    ~CApplication();

private:
    CCube* m_Cube;
    CCube* m_Cube2;
    CCube* m_Cube3;

    CCamera* m_Camera;
    CInput* m_Input;

    glm::vec3 m_Position;
    float m_CameraMoveSpeed;
    float m_MouseMoveSpeed;

    float m_LastX, m_LastY;

    std::vector<int> m_Keys;
};

#endif