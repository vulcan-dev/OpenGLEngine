#include "GameLayer.h"

bool firstMouse = true;

CGameLayer::CGameLayer() : CLayer("Game") {

}

void CGameLayer::AddPrimitive(std::string_view name) {
    CPrimitiveCube cube;
    CPrimitiveSphere sphere;

    this->m_PrimitiveShapeID++;

    if (name == "cube") {
        this->m_Meshes.push_back(
            std::make_shared<CMesh>(&cube, GL_TRIANGLES, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f))
        );
        
        this->m_Models[fmt::format("cube_{}", this->m_PrimitiveShapeID)] = 
            std::make_shared<CModel>(
                glm::vec3(0.f), this->m_Materials["Default"].get(), 
                this->m_Textures["BOX_DIFFUSE"].get(), 
                this->m_Textures["BOX_SPECULAR"].get(), 
                m_Meshes
        );

        APP_INFO("Added Cube, ID = {}", this->m_PrimitiveShapeID);
    } else if (name == "sphere") {
        this->m_Meshes.push_back(
            std::make_shared<CMesh>(&sphere, GL_TRIANGLE_STRIP, glm::vec3(0.f, 3.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f))
        );

        this->m_Models[fmt::format("sphere_{}", this->m_PrimitiveShapeID)] =
            std::make_shared<CModel>(
                glm::vec3(0.f), this->m_Materials["Default"].get(),
                this->m_Textures["BOX_DIFFUSE"].get(),
                this->m_Textures["BOX_SPECULAR"].get(),
                m_Meshes
        );

        APP_INFO("Added Sphere, ID = {}", this->m_PrimitiveShapeID);
    } else {
        this->m_PrimitiveShapeID--;
    }
}

void CGameLayer::OnAttach(CWindow* window) {
    this->m_Window = window;

    APP_INFO("Game Started");

    this->InitializeCamera();
    this->InitializeKeybinds();

    this->AddShader("Core", "Shaders/VertexCore.vs", "Shaders/FragmentCore.fs", "");
    this->AddShader("PBR", "Shaders/PBR.vs", "Shaders/PBR.fs");

    this->AddMaterial("Default", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1);

    this->m_Shaders["PBR"]->Bind();
    this->m_Shaders["PBR"]->Set1i(0, "irradianceMap");
    this->m_Shaders["PBR"]->Set1i(1, "prefilterMap");
    this->m_Shaders["PBR"]->Set1i(2, "brdfLUT");
    this->m_Shaders["PBR"]->SetVec3f(glm::vec3(.5f, .5f, .5f), "albedo");
    this->m_Shaders["PBR"]->Set1f(1.f, "ao");

    this->m_Shaders["PBR"]->SetMat4fv(glm::perspective(glm::radians(90.0f), (float)this->m_Window->width / (float)this->m_Window->height, 0.1f, 100.0f), "projection");

    this->AddTexture("BOX_DIFFUSE", "Textures/Box.png", GL_TEXTURE_2D);
    this->AddTexture("BOX_SPECULAR", "Textures/BoxSpecularMap.png", GL_TEXTURE_2D);

    this->m_Skybox = std::make_shared<CSkybox>(this->m_Window, this->m_Camera.get(), this->m_CameraPosition);
    this->m_Skybox->SetRotY(90);

    glfwGetFramebufferSize(this->m_Window->window, &this->m_Window->width, &this->m_Window->height);
    glViewport(0, 0, this->m_Window->width, this->m_Window->height);

    // AddPrimitive("cube");
    AddPrimitive("sphere");

    // auto filepath = fmt::format("../{}/{}", ROOT_DIR, "Models/mustang.obj");
    // this->m_Models["Obj"] = std::make_shared<CModel>(
    //     glm::vec3(0.f),
    //     this->m_Materials["Default"].get(),
    //     this->m_Textures["BOX_DIFFUSE"].get(), 
    //     this->m_Textures["BOX_SPECULAR"].get(),
    //     filepath.data()
    // );
}

void CGameLayer::OnUpdate(const float& dt) {
    this->UpdateControls(dt);
    this->UpdateObjects(dt);
    this->UpdateCamera(dt);
}

void CGameLayer::OnRender(const float& dt) {
    this->m_Shaders["PBR"]->SetMat4fv(this->m_Camera->GetView(), "view");
    this->m_Shaders["PBR"]->SetVec3f(this->m_CameraPosition, "camPos");
    this->m_Shaders["PBR"]->Bind();

    this->m_Skybox->Render(this->m_Camera.get(), this->m_CameraPosition);
    this->m_Shaders["PBR"]->Bind();
    for (const auto& model : this->m_Models) {
        model.second->Render(this->m_Shaders["PBR"].get());
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

void CGameLayer::UpdateObjects(const float& dt) {
    this->m_Skybox->SetRotY(90);
}

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