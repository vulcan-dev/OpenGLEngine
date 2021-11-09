#include "Application.h"
#include <glm/gtx/string_cast.hpp>

bool firstMouse = true;

CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle)
: CEngine(windowWidth, windowHeight, windowTitle) {
    APP_INFO("Application Started");

    this->m_LastX = this->m_WindowWidth / 2.0f;
    this->m_LastY = this->m_WindowHeight / 2.0f;

    this->m_Position = glm::vec3(0, 0, 5);

    this->m_CameraMoveSpeed = 4.5f;
    this->m_FieldOfView = 60.f;

    this->m_Textures["BOX_DIFFUSE"] = std::make_unique<CTexture>("Textures/Box.png", GL_TEXTURE_2D);
    this->m_Textures["BOX_SPECULAR"] = std::make_unique<CTexture>("Textures/BoxSpecularMap.png", GL_TEXTURE_2D);

    this->m_Material = std::make_unique<CMaterial>(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1);

    this->m_Shaders["Core"] = std::make_unique<CShader>("Shaders/VertexCore.vs", "Shaders/FragmentCore.fs", "");

    this->m_Camera = std::make_unique<CCamera>((float)this->m_WindowWidth, (float)this->m_WindowHeight, glm::vec3(0.f, 0.f, 5.f));
    this->m_Camera->SetFieldOfView(this->m_FieldOfView);
    this->m_Camera->SetMovementSpeed(this->m_CameraMoveSpeed);
    this->m_Camera->SetMouseSensitivity(.1f);

    this->InitializeKeybinds();
    this->InitializeObjects();

    while (CEngine::IsRunning()) {
        this->Update();
        this->Render();
    }
}

void CApplication::InitializeKeybinds() {
    glfwSetInputMode(this->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->m_Keys.push_back(GLFW_KEY_W);
    this->m_Keys.push_back(GLFW_KEY_A);
    this->m_Keys.push_back(GLFW_KEY_S);
    this->m_Keys.push_back(GLFW_KEY_D);
    this->m_Keys.push_back(GLFW_KEY_ESCAPE);
    this->m_Keys.push_back(GLFW_KEY_LEFT_CONTROL);
    this->m_Keys.push_back(GLFW_KEY_LEFT_SHIFT);
    this->m_Keys.push_back(GLFW_KEY_SPACE);
    this->m_Keys.push_back(GLFW_KEY_LEFT_ALT);

    this->m_Input = std::make_unique<CInput>(this->m_Keys);
    this->m_Input->SetIsEnabled(true);
    this->m_Input->SetupKeyInputs(*this->GetWindow());
}

void CApplication::InitializeObjects() {
    CPrimitiveCube cube;

    this->m_Meshes.push_back(
        new CMesh(
            &cube,
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        )
    );

    // this->m_Models.push_back(
    //     new CModel(
    //         glm::vec3(0.f),
    //         this->m_Material.get(),
    //         this->m_Textures["BOX_DIFFUSE"].get(),
    //         this->m_Textures["BOX_SPECULAR"].get(),
    //         m_Meshes
    //     )
    // );

    this->m_Meshes.push_back(
        new CMesh(
            &cube,
            glm::vec3(2.f, 2.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        )
    );

    this->m_Models.push_back(
        new CModel(
            glm::vec3(0.f),
            this->m_Material.get(),
            this->m_Textures["BOX_DIFFUSE"].get(),
            this->m_Textures["BOX_SPECULAR"].get(),
            m_Meshes
        )
    );
}

void CApplication::Update() {
    CEngine::Update();
    this->UpdateControls();
    this->UpdateCamera();
    this->UpdateObjects();
}

void CApplication::UpdateCamera() {
    for (const auto& shader : this->m_Shaders) {
        this->m_Camera->UpdateUniforms(shader.second.get());
    }

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

void CApplication::UpdateObjects() {

}

void CApplication::UpdateControls() {
    float velocity = this->m_CameraMoveSpeed * this->GetDeltaTime();
    
    if (this->m_Input->IsKeyDown(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(this->GetWindow(), true);
    }

    // x
    if (this->m_Input->IsKeyDown(GLFW_KEY_A)) {
        this->m_Position -= this->m_Camera->GetRight() * velocity;
    } else if (this->m_Input->IsKeyDown(GLFW_KEY_D)) {
        this->m_Position += this->m_Camera->GetRight() * velocity;
    }
    
    // y
    if (this->m_Input->IsKeyDown(GLFW_KEY_LEFT_CONTROL)) {
        this->m_Position -= this->m_Camera->GetUp() * velocity;
    } else if (this->m_Input->IsKeyDown(GLFW_KEY_SPACE)) {
        this->m_Position += this->m_Camera->GetUp() * velocity;
    }

    // z
    if (this->m_Input->IsKeyDown(GLFW_KEY_W)) {
        this->m_Position += this->m_Camera->GetFront() * velocity;
    } else if (this->m_Input->IsKeyDown(GLFW_KEY_S)) {
        this->m_Position -= this->m_Camera->GetFront() * velocity;
    }

    this->m_Camera->SetPosition(this->m_Position);

    // speed
    if (this->m_Input->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        this->m_CameraMoveSpeed = 8.f;
    } else if (this->m_Input->IsKeyDown(GLFW_KEY_LEFT_ALT)) {
        this->m_CameraMoveSpeed = 2.f;
    } else {
        this->m_CameraMoveSpeed = 4.f;
    }
}

void CApplication::Render() {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    for (const auto& obj : this->m_Models) {
        obj->Render(this->m_Shaders["Core"].get());
    }

    glfwSwapBuffers(this->GetWindow());
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
    glfwPollEvents();
}

CApplication::~CApplication() {
    APP_INFO("Exiting Application");
}