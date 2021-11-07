#include "Application.h"
#include <glm/gtx/string_cast.hpp>

CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle)
: CEngine(windowWidth, windowHeight, windowTitle) {
    this->m_Keys.push_back(GLFW_KEY_W);
    this->m_Keys.push_back(GLFW_KEY_A);
    this->m_Keys.push_back(GLFW_KEY_S);
    this->m_Keys.push_back(GLFW_KEY_D);
    this->m_Keys.push_back(GLFW_KEY_LEFT_CONTROL);
    this->m_Keys.push_back(GLFW_KEY_LEFT_SHIFT);
    this->m_Keys.push_back(GLFW_KEY_SPACE);

    this->m_Input = new CInput(this->m_Keys);
    this->m_Input->setIsEnabled(true);
    this->m_Input->setupKeyInputs(*this->GetWindow());

    this->m_CameraMoveSpeed = 5.f;
    this->m_MouseMoveSpeed = 100.f;

    APP_INFO("Application Started");
    this->m_Position = glm::vec3(0, 0, 5);
    this->m_Camera = new CCamera(this->m_WindowWidth, this->m_WindowHeight, this->m_Position, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));

    this->m_Cube = new CCube(this->m_Camera, glm::vec3(1.f, 0.f, 0.f));
    this->m_Cube2 = new CCube(this->m_Camera, glm::vec3(0.f, 1.f, 0.f));
    this->m_Cube3 = new CCube(this->m_Camera, glm::vec3(0.f, 0.f, 1.f));

    this->m_Cube->SetPosition(glm::vec3(-2.5f, 0.f, 0.f));
    this->m_Cube2->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    this->m_Cube3->SetPosition(glm::vec3(2.5f, 0.f, 0.f));

    while (CEngine::IsRunning()) {
        this->Update();
        this->Render();
    }
}

void CApplication::Update() {
    CEngine::Update();

    float px = (this->m_MousePositionX / (this->m_WindowWidth/2) - 1.f) * this->m_MouseMoveSpeed * (this->GetDeltaTime() * 2);
    float py = -1 * (this->m_MousePositionY / (this->m_WindowHeight/2) - 1.f) * this->m_MouseMoveSpeed * (this->GetDeltaTime() * 2);
    APP_DEBUG("Mouse: x = {}, y = {}", this->m_MousePositionX, this->m_MousePositionY);

    // eye = pos
    // up = head
    // lookat = center

    // auto los = glm::vec3(this->m_Position, this->m_Position + this->m_Camera->GetHead(), this->m_Camera->GetHead());
    this->m_Camera->LookAt(this->Position);

    // x
    if (this->m_Input->getIsKeyDown(GLFW_KEY_A)) {
        this->m_Position.x -= this->m_CameraMoveSpeed * this->GetDeltaTime();
    } else if (this->m_Input->getIsKeyDown(GLFW_KEY_D)) {
        this->m_Position.x += this->m_CameraMoveSpeed * this->GetDeltaTime();
    }
    
    // y
    if (this->m_Input->getIsKeyDown(GLFW_KEY_LEFT_CONTROL)) {
        this->m_Position.y -= this->m_CameraMoveSpeed * this->GetDeltaTime();
    } else if (this->m_Input->getIsKeyDown(GLFW_KEY_SPACE)) {
        this->m_Position.y += this->m_CameraMoveSpeed * this->GetDeltaTime();
    }

    // z
    if (this->m_Input->getIsKeyDown(GLFW_KEY_W)) {
        this->m_Position.z -= this->m_CameraMoveSpeed * this->GetDeltaTime();
    } else if (this->m_Input->getIsKeyDown(GLFW_KEY_S)) {
        this->m_Position.z += this->m_CameraMoveSpeed * this->GetDeltaTime();
    }

    this->m_Camera->SetPosition(this->m_Position);

    // speed
    if (this->m_Input->getIsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        this->m_CameraMoveSpeed = 15.f;
    } else {
        this->m_CameraMoveSpeed = 5.f;
    }

    this->m_Cube->SetRotation(120 * glfwGetTime());
    this->m_Cube2->SetRotation(120 * glfwGetTime());
    this->m_Cube3->SetRotation(120 * glfwGetTime());
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
    delete this->m_Input;
    delete this->m_Camera;
    delete this->m_Cube;
    delete this->m_Cube2;
    delete this->m_Cube3;

    APP_INFO("Exiting Application");
}