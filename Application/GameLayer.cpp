bool firstMouse = true;

#include "GameLayer.h"

CGameLayer::CGameLayer() : CLayer("Game") {

}

void CGameLayer::OnAttach(CWindow* window) {
    this->m_Window = window;

    APP_INFO("Game Started");

    this->AddShader("Core", "Shaders/VertexCore.vs", "Shaders/FragmentCore.fs", "");

    this->AddMaterial("Default", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1);

    this->InitializeCamera();
    this->InitializeKeybinds();

    // this->AddTexture("BOX_DIFFUSE", "Textures/Box.png", GL_TEXTURE_2D);
    // this->AddTexture("BOX_SPECULAR", "Textures/BoxSpecularMap.png", GL_TEXTURE_2D);

    this->m_Skybox = std::make_shared<CSkybox>(this->m_Window, this->m_Camera.get(), this->m_CameraPosition);
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(this->m_Window->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

    // glfwGetFramebufferSize(this->m_Window->window, &this->m_Window->width, &this->m_Window->height);
    // glViewport(0, 0, this->m_Window->width, this->m_Window->height);

    // CPrimitiveCube cube;
    // this->m_Meshes.push_back(
    //     new CMesh(
    //         &cube,
    //         glm::vec3(0.f, 0.f, 0.f),
    //         glm::vec3(0.f),
    //         glm::vec3(0.f),
    //         glm::vec3(1.f)
    //     )
    // );

    // this->m_Models.push_back(
    //     new CModel(
    //         glm::vec3(0.f),
    //         this->m_Materials["Default"].get(),
    //         this->m_Textures["BOX_DIFFUSE"].get(),
    //         this->m_Textures["BOX_SPECULAR"].get(),
    //         m_Meshes
    //     )
    // );
}

void CGameLayer::OnUpdate(const float& dt) {
    this->UpdateControls(dt);
    this->UpdateObjects(dt);
    this->UpdateCamera(dt);
}

void CGameLayer::OnRender() {
    this->m_Skybox->Render(this->m_Camera.get(), this->m_CameraPosition);
}

void CGameLayer::OnDetach() {
    APP_INFO("Exiting Application");
}

void CGameLayer::InitializeCamera() {
    this->m_LastX = this->m_Window->width / 2.0f;
    this->m_LastY = this->m_Window->height / 2.0f;

    this->m_CameraPosition = glm::vec3(0, 0, 5);

    this->m_CameraMoveSpeed = 4.5f;
    this->m_FieldOfView = 60.f;

    this->m_Camera = std::make_unique<CPerspectiveCamera>((float)this->m_Window->width, (float)this->m_Window->height);

    this->m_Camera->SetFieldOfView(this->m_FieldOfView);
    this->m_Camera->SetMovementSpeed(this->m_CameraMoveSpeed);
    this->m_Camera->SetMouseSensitivity(.1f);
}

void CGameLayer::InitializeKeybinds() {
    glfwSetInputMode(this->m_Window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->m_Keys.push_back(GLFW_KEY_W);
    this->m_Keys.push_back(GLFW_KEY_A);
    this->m_Keys.push_back(GLFW_KEY_S);
    this->m_Keys.push_back(GLFW_KEY_D);
    this->m_Keys.push_back(GLFW_KEY_ESCAPE);
    this->m_Keys.push_back(GLFW_KEY_LEFT_CONTROL);
    this->m_Keys.push_back(GLFW_KEY_LEFT_SHIFT);
    this->m_Keys.push_back(GLFW_KEY_SPACE);
    this->m_Keys.push_back(GLFW_KEY_LEFT_ALT);

    this->m_KeyboardControls = std::make_unique<CInput>(this->m_Keys);
    this->m_KeyboardControls->SetIsEnabled(true);
    this->m_KeyboardControls->SetupKeyInputs(*this->m_Window->window);
}

void CGameLayer::UpdateObjects(const float& dt) {}
void CGameLayer::UpdateCamera(const float& dt) {
     this->m_Camera->UpdateUniforms(this->GetShader("Core"));

    if (this->m_MousePositionX != this->m_LastX || this->m_MousePositionY != this->m_LastY) {
        if (firstMouse) {
            this->m_LastX = this->m_MousePositionX;
            this->m_LastY = this->m_MousePositionY;
            firstMouse = false;
        }

        double xoffset = this->m_MousePositionX - this->m_LastX;
        float yoffset = this->m_LastY - this->m_MousePositionY;

        this->m_LastX = this->m_MousePositionX;
        this->m_LastY = this->m_MousePositionY;

        this->m_Camera->Update(xoffset, yoffset, true);
    }
}

void CGameLayer::UpdateControls(const float& dt) {
    glfwGetCursorPos(this->m_Window->window, &this->m_MousePositionX, &this->m_MousePositionY);
    float velocity = this->m_CameraMoveSpeed * dt;
    
    if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_ESCAPE)) {
        // glfwSetWindowShouldClose(this->GetWindow(), true);
    }

    // x
    if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_A)) {
        this->m_CameraPosition -= this->m_Camera->GetRight() * velocity;
    } else if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_D)) {
        this->m_CameraPosition += this->m_Camera->GetRight() * velocity;
    }
    
    // y
    if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_LEFT_CONTROL)) {
        this->m_CameraPosition -= this->m_Camera->GetUp() * velocity;
    } else if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_SPACE)) {
        this->m_CameraPosition += this->m_Camera->GetUp() * velocity;
    }

    // z
    if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_W)) {
        this->m_CameraPosition += this->m_Camera->GetFront() * velocity;
    } else if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_S)) {
        this->m_CameraPosition -= this->m_Camera->GetFront() * velocity;
    }

    this->m_Camera->SetPosition(this->m_CameraPosition);

    // speed
    if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        this->m_CameraMoveSpeed = 8.f;
    } else if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_LEFT_ALT)) {
        this->m_CameraMoveSpeed = 2.f;
    } else {
        this->m_CameraMoveSpeed = 4.f;
    }
}