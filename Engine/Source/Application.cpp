#include "Application.h"

CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle)
: CEngine(windowWidth, windowHeight, windowTitle) {
    APP_INFO("Application Started");
    this->m_Cube = new CCube(glm::vec3(1.f, 0.f, 0.f));
    this->m_Cube2 = new CCube(glm::vec3(0.f, 1.f, 0.f));
    this->m_Cube3 = new CCube(glm::vec3(0.f, 0.f, 1.f));

    this->m_Cube->SetPosition(glm::vec3(-2.5f, 0.f, 0.f));
    this->m_Cube2->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    this->m_Cube3->SetPosition(glm::vec3(2.5f, 0.f, 0.f));
    // this->m_Cube2->SetPosition(glm::vec3(0.f, 3.f, -1.f));

    while (CEngine::IsRunning()) {
        this->Update();
        this->Render();
    }
}

void CApplication::Update() {
    CEngine::Update();

    this->m_Cube->SetRotation(120 * glfwGetTime());
    this->m_Cube2->SetRotation(120 * glfwGetTime());
    this->m_Cube3->SetRotation(120 * glfwGetTime());

    APP_DEBUG("glfwGetTime = {}", 120 * glfwGetTime());
}

void CApplication::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_Cube->Render();
    this->m_Cube2->Render();
    this->m_Cube3->Render();

    glfwSwapBuffers(this->GetWindow());
    glfwPollEvents();
}

CApplication::~CApplication() {
    delete this->m_Cube;
    delete this->m_Cube2;
    delete this->m_Cube3;

    APP_INFO("Exiting Application");
}