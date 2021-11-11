bool firstMouse = true;

#include "GameLayer.h"

void CGameLayer::TestCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

CGameLayer::CGameLayer() : CLayer("Game") {

}

void CGameLayer::OnAttach(CWindow* window) {
    this->m_Window = window;

    APP_INFO("Game Started");

    this->AddShader("Core", "Shaders/VertexCore.vs", "Shaders/FragmentCore.fs", "");

    this->AddMaterial("Default", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1);

    this->InitializeCamera();
    this->InitializeKeybinds();

    this->AddTexture("BOX_DIFFUSE", "Textures/Box.png", GL_TEXTURE_2D);
    this->AddTexture("BOX_SPECULAR", "Textures/BoxSpecularMap.png", GL_TEXTURE_2D);

    this->m_Skybox = std::make_shared<CSkybox>(this->m_Window, this->m_Camera.get(), this->m_CameraPosition);

    glfwGetFramebufferSize(this->m_Window->window, &this->m_Window->width, &this->m_Window->height);
    glViewport(0, 0, this->m_Window->width, this->m_Window->height);

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

    this->m_Models.push_back(
        new CModel(
            glm::vec3(0.f),
            this->m_Materials["Default"].get(),
            this->m_Textures["BOX_DIFFUSE"].get(),
            this->m_Textures["BOX_SPECULAR"].get(),
            m_Meshes
        )
    );

    this->m_Meshes.push_back(
        new CMesh(
            &cube,
            glm::vec3(1.f, 0.f, 1.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        )
    );

    this->m_Models.push_back(
        new CModel(
            glm::vec3(0.f),
            this->m_Materials["Default"].get(),
            this->m_Textures["BOX_DIFFUSE"].get(),
            this->m_Textures["BOX_SPECULAR"].get(),
            m_Meshes
        )
    );
}

void CGameLayer::OnUpdate(const float& dt) {
    this->UpdateControls(dt);
    this->UpdateObjects(dt);
    this->UpdateCamera(dt);
}

void CGameLayer::OnRender() {
    // TestCube();
    this->m_Skybox->Render(this->m_Camera.get(), this->m_CameraPosition);
    for (const auto& model : this->m_Models) {
        model->Render(this->m_Shaders["Core"].get());
    }
}

void CGameLayer::OnDetach() {
    APP_INFO("Exiting Application");
}

void CGameLayer::InitializeCamera() {
    this->m_LastX = this->m_Window->width / 2.0f;
    this->m_LastY = this->m_Window->height / 2.0f;

    this->m_CameraPosition = glm::vec3(0, 0, 5);

    this->m_CameraMoveSpeed = 4.5f;
    this->m_FieldOfView = 90.f;

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