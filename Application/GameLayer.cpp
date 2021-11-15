#include "GameLayer.h"

bool firstMouse = true;

CGameLayer::CGameLayer() : CLayer("Game") {

}

bool CGameLayer::AddPrimitive(std::string_view name) {
    this->m_PrimitiveShapeID++;

    std::string meshName;

    if (name == "cube") {
        VK::CPrimitiveCube cube;

        Ref<VK::CMesh> meshCube = std::make_shared<VK::CMesh>(&cube, GL_TRIANGLES, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

        meshName = fmt::format("cube_{}", this->m_PrimitiveShapeID);
        this->m_Models[meshName] = std::make_shared<VK::CModel>("Cube",
                glm::vec3(0.f),
                this->m_Materials["Default"].get(),
                this->m_Textures["BOX_DIFFUSE"].get(),
                this->m_Textures["BOX_SPECULAR"].get(),
                meshCube
                );

        APP_INFO("Added Cube, ID = {}", this->m_PrimitiveShapeID);
    } else if (name == "sphere") {
        VK::CPrimitiveSphere sphere;
        Ref<VK::CMesh> sphereMesh = std::make_shared<VK::CMesh>(&sphere, GL_TRIANGLE_STRIP, glm::vec3(0.f, 3.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

        meshName = fmt::format("sphere_{}", this->m_PrimitiveShapeID);
        this->m_Models[meshName] =
            std::make_shared<VK::CModel>("Sphere",
                glm::vec3(0.f), this->m_Materials["Default"].get(),
                this->m_Textures["BOX_DIFFUSE"].get(),
                this->m_Textures["BOX_SPECULAR"].get(),
                sphereMesh
        );

        APP_INFO("Added Sphere, ID = {}, Name = {}", this->m_PrimitiveShapeID, fmt::format("sphere_{}", this->m_PrimitiveShapeID));
    } else if (name == "plane") {
        VK::CPrimitivePlane plane;
        Ref<VK::CMesh> planeMesh = std::make_shared<VK::CMesh>(&plane, GL_TRIANGLES, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

        meshName = fmt::format("plane_{}", this->m_PrimitiveShapeID);
        this->m_Models[meshName] =
            std::make_shared<VK::CModel>("Plane",
                glm::vec3(0.f), this->m_Materials["Default"].get(),
                this->m_Textures["BOX_DIFFUSE"].get(),
                this->m_Textures["BOX_SPECULAR"].get(),
                planeMesh
        );
    } else {
        this->m_PrimitiveShapeID--;
        return 1;
    }

    APP_DEBUG("Mesh Name: {}", meshName);

    this->m_Interface->AddModel(this->m_Models);
    return 0;
}

void CGameLayer::OnAttach(VK::CWindow* window) {
    this->m_Window = window;

    this->m_Interface = std::make_shared<CInterface>(this->m_Window->window);
    this->m_Interface->SetWindowSize(this->m_Window->width, this->m_Window->height);

    APP_INFO("Game Started");

    this->InitializeCamera();
    this->initializeKeybinds();

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

    this->m_Skybox = std::make_shared<VK::CSkybox>(this->m_Window, "Skyboxes/adams_place_bridge_4k.hdr", this->m_Camera.get(), this->m_CameraPosition);
    this->m_Skybox->SetRotY(90);

    glfwGetFramebufferSize(this->m_Window->window, &this->m_Window->width, &this->m_Window->height);
    glViewport(0, 0, this->m_Window->width, this->m_Window->height);

//    AddPrimitive("plane");
    AddPrimitive("sphere");
    AddPrimitive("sphere");
    AddPrimitive("sphere");
    AddPrimitive("sphere");
    AddPrimitive("sphere");
    AddPrimitive("sphere");
    AddPrimitive("cube");
    AddPrimitive("cube");
    AddPrimitive("cube");
    AddPrimitive("cube");
    AddPrimitive("cube");
    AddPrimitive("plane");
    AddPrimitive("plane");
    AddPrimitive("plane");
    AddPrimitive("plane");
    AddPrimitive("plane");
    AddPrimitive("plane");

    /*
     * TODO: Fix rotation
     * TODO: Fix plane issue
     * TODO: Re-enable face culling
     * TODO: Go for a piss
     * TODO: Make menu not look like crap
     * TODO: Shader outline
     * TODO: PBR realtime-reflection (works with skybox currently, nothing else)
     * TODO: Lights
     * TODO: Really go for a piss
     * TODO: Arrows in "editor" to drag object
     * TODO: Textures
     * TODO: Model Loading
     */

    // auto filepath = fmt::format("../{}/{}", ROOT_DIR, "Models/Handgun_obj.obj");
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

//    EventModify<bool> wireframe(&this->m_Interface->Wireframe, [this]() {
//        int mode = GL_FILL;
//        this->m_Interface->Wireframe ? GL_LINE : GL_FILL;
//        glPolygonMode(GL_FRONT_AND_BACK, mode);
//        APP_DEBUG("Changed");
//    });

    if (!this->m_MouseEnabled)
        this->UpdateCamera(dt);
    /*
     * RunOnModify(variable, lambda);
     */
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

    this->m_Interface->Render(dt);
}

void CGameLayer::UpdateObjects(const float& dt) {

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

    this->m_Camera = std::make_unique<VK::CPerspectiveCamera>((float)this->m_Window->width, (float)this->m_Window->height);

    this->m_Camera->SetFieldOfView(this->m_FieldOfView);
    this->m_Camera->SetMovementSpeed(this->m_CameraMoveSpeed);
    this->m_Camera->SetMouseSensitivity(.1f);
}

void CGameLayer::initializeKeybinds() {
    glfwSetInputMode(this->m_Window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->m_Keys.push_back(GLFW_KEY_W);
    this->m_Keys.push_back(GLFW_KEY_A);
    this->m_Keys.push_back(GLFW_KEY_S);
    this->m_Keys.push_back(GLFW_KEY_D);
    this->m_Keys.push_back(GLFW_KEY_ESCAPE);
    this->m_Keys.push_back(GLFW_KEY_F1);
    this->m_Keys.push_back(GLFW_KEY_LEFT_CONTROL);
    this->m_Keys.push_back(GLFW_KEY_LEFT_SHIFT);
    this->m_Keys.push_back(GLFW_KEY_SPACE);
    this->m_Keys.push_back(GLFW_KEY_LEFT_ALT);

    this->m_KeyboardControls = std::make_unique<VK::CInput>(this->m_Keys);
    this->m_KeyboardControls->SetIsEnabled(true);
    this->m_KeyboardControls->SetupKeyInputs(*this->m_Window->window);
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

    if (this->m_KeyboardControls->IsKeyUp(GLFW_KEY_ESCAPE)) {
        glfwTerminate();
    }

    if (this->m_KeyboardControls->IsKeyUp(GLFW_KEY_F1)) {
        this->m_MouseEnabled = !this->m_MouseEnabled;

        glfwSetInputMode(this->m_Window->window, GLFW_CURSOR, this->m_MouseEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
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