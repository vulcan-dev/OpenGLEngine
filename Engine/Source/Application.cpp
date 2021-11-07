#include "Application.h"

CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle)
: CEngine(windowWidth, windowHeight, windowTitle) {
    this->m_Cube = new CCube();

    while (CEngine::IsRunning()) {
        this->Update();
        this->Render();
        this->m_Cube->SetRotation(40 * this->GetDeltaTime());
    }
}

void CApplication::Update() {
    CEngine::Update();
}

void CApplication::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_Cube->Render();

    glfwSwapBuffers(this->GetWindow());
    glfwPollEvents();
}

CApplication::~CApplication() {
    delete this->m_Cube;
}