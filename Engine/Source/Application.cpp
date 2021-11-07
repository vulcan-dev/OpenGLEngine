#include "Application.h"

CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle)
: CEngine(windowWidth, windowHeight, windowTitle) {
    this->m_Cube = new CCube();
    this->m_Cube2 = new CCube();
    this->m_Cube3 = new CCube();
    this->m_Cube4 = new CCube();
    this->m_Cube5 = new CCube();

    this->m_Cube->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    this->m_Cube2->SetPosition(glm::vec3(1.5f, -1.f, 0.f));
    this->m_Cube3->SetPosition(glm::vec3(-1.5f, 1.f, 0.f));
    this->m_Cube4->SetPosition(glm::vec3(1.5f, 1.f, 0.f));
    this->m_Cube5->SetPosition(glm::vec3(-1.5f, -1.f, 0.f));

    while (CEngine::IsRunning()) {
        this->Update();
        this->Render();
        this->m_Cube->SetRotation(40 * this->GetDeltaTime());
        this->m_Cube2->SetRotation(40 * this->GetDeltaTime());
        this->m_Cube3->SetRotation(40 * this->GetDeltaTime());
        this->m_Cube4->SetRotation(40 * this->GetDeltaTime());
        this->m_Cube5->SetRotation(40 * this->GetDeltaTime());
    }
}

void CApplication::Update() {
    CEngine::Update();
}

void CApplication::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_Cube->Render();
    this->m_Cube2->Render();
    this->m_Cube3->Render();
    this->m_Cube4->Render();
    this->m_Cube5->Render();

    glfwSwapBuffers(this->GetWindow());
    glfwPollEvents();
}

CApplication::~CApplication() {
    delete this->m_Cube;
    delete this->m_Cube2;
    delete this->m_Cube3;
    delete this->m_Cube4;
    delete this->m_Cube5;
}