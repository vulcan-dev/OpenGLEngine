#include "GameLayer.h"

bool firstMouse = true;

CGameLayer::CGameLayer() : CLayer("Game") {}

/*
 * TODO: Fix plane issue
 * TODO: Shader outline
 * TODO: PBR realtime-reflection (works with skybox currently, nothing else)
 * TODO: Lights
 * TODO: Arrows in "editor" to drag object
 * TODO: Textures
 * TODO: Model Loading
 * TODO: Model Resize
 * TODO: Rays & Intersections
 */

bool CGameLayer::AddPrimitive(std::string_view name, const glm::vec3& pos) {
    this->m_PrimitiveShapeID++;

    std::string meshName;

    if (name == "cube") {
        VK::CPrimitiveCube cube;

        Ref<VK::CMesh> meshCube = std::make_shared<VK::CMesh>(&cube, GL_TRIANGLES, glm::vec3(0.f, 3.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

        meshName = fmt::format("cube_{}", this->m_PrimitiveShapeID);
        this->m_Models[meshName] = std::make_shared<VK::CModel>("Cube",
                pos,
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
                pos, this->m_Materials["Default"].get(),
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
                pos, this->m_Materials["Default"].get(),
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

    this->AddMaterial("Default", glm::vec3(0.1f), glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f), 0, 1);

    this->m_Shaders["PBR"]->Bind();
    this->m_Shaders["PBR"]->Set1i(0, "irradianceMap");
    this->m_Shaders["PBR"]->Set1i(1, "prefilterMap");
    this->m_Shaders["PBR"]->Set1i(2, "brdfLUT");
    this->m_Shaders["PBR"]->Set1f(5, "metallic");
    this->m_Shaders["PBR"]->Set1f(0, "roughness");
    this->m_Shaders["PBR"]->SetVec3f(glm::vec3(.5f, .5f, .5f), "albedo");
    this->m_Shaders["PBR"]->Set1f(1.f, "ao");

//    this->m_Shaders["PBR"]->SetMat4fv(glm::perspective(glm::radians(90.0f), (float)this->m_Window->width / (float)this->m_Window->height, 0.1f, 100.0f), "projection");

    this->AddTexture("BOX_DIFFUSE", "Textures/Box.png", GL_TEXTURE_2D);
    this->AddTexture("BOX_SPECULAR", "Textures/BoxSpecularMap.png", GL_TEXTURE_2D);

    this->m_Skybox = std::make_shared<VK::CSkybox>(this->m_Window, "Skyboxes/studio_small_09_4k.hdr", this->m_Camera.get(), this->m_CameraPosition);
    this->m_Skybox->SetRotY(90);

    this->m_DebugLine = std::make_shared<VK::CLine>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 2.f));

    glfwGetFramebufferSize(this->m_Window->window, &this->m_Window->width, &this->m_Window->height);
    glViewport(0, 0, this->m_Window->width, this->m_Window->height);

    AddPrimitive("cube");
    AddPrimitive("sphere", glm::vec3(3.f, 4.f, 0.f));
}

void CGameLayer::OnUpdate(const float& dt) {
    this->m_Interface->FPS = static_cast<int16_t>(1.f/dt);

    if (this->m_KeyboardControls->IsKeyDown(GLFW_MOUSE_BUTTON_RIGHT)) {
        glfwSetInputMode(this->m_Window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (!this->m_WasMouseEnabled) {
            glfwSetCursorPos(this->m_Window->window, this->m_LastX, this->m_LastY);
            this->m_WasMouseEnabled = true;
        }
        this->m_MouseEnabled = false;
        this->m_Camera->SetPosition(this->m_CameraPosition);
        this->UpdateCamera(dt);
    } else if (this->m_KeyboardControls->IsKeyUp(GLFW_MOUSE_BUTTON_RIGHT)) {
        glfwSetInputMode(this->m_Window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        this->m_MouseEnabled = true;
        this->m_WasMouseEnabled = false;
        this->m_LastX = this->m_Window->width / 2.0f;
        this->m_LastY = this->m_Window->height / 2.0f;
    }

    this->UpdateObjects(dt);
    this->UpdateControls(dt);
}

void CGameLayer::OnRender(const float& dt) {
    // Core
//    this->m_Shaders["Core"]->Bind();
//    this->m_Shaders["Core"]->SetMat4fv(this->m_Camera->GetView(), "view");
//    this->m_Shaders["Core"]->SetVec3f(this->m_CameraPosition, "camPos");
//    this->m_Shaders["Core"]->SetMat4fv(this->m_Camera->GetProjection(), "projection");
//    this->m_DebugLine->SetPosition(glm::vec3(this->m_CameraPosition.x, this->m_CameraPosition.y, this->m_CameraPosition.z));

//    this->m_DebugLine->Render(this->m_Shaders["Core"].get());
//    this->m_Shaders["Core"]->Unbind();

    // PBR
    this->m_Skybox->Render(this->m_Camera.get(), this->m_CameraPosition);

    this->m_Shaders["PBR"]->Bind();
    for (const auto& model : this->m_Models) {
        model.second->Render(this->m_Shaders["PBR"].get());
    }
    this->m_Shaders["PBR"]->Unbind();

    this->m_Interface->Render(dt);
}

void CGameLayer::UpdateObjects(const float& dt) {
    for (const auto& o : this->m_Models) {
        glm::vec3 ray = this->m_Camera->RayWorld(this->m_MousePositionX, this->m_MousePositionY, this->m_Window->width, this->m_Window->height);
        if (o.second->Intersects(ray, this->m_Camera->GetProjection(), this->m_Camera->GetView())) {
            this->m_Interface->Debug = fmt::format("Intersecting {}", o.second->GetDisplayName());
        }
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

    this->m_Camera = std::make_unique<VK::CPerspectiveCamera>((float)this->m_Window->width, (float)this->m_Window->height);

    this->m_Camera->SetFieldOfView(this->m_FieldOfView);
    this->m_Camera->SetMovementSpeed(this->m_CameraMoveSpeed);
    this->m_Camera->SetMouseSensitivity(.1f);
}

void CGameLayer::initializeKeybinds() {
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
    this->m_Keys.push_back(GLFW_MOUSE_BUTTON_RIGHT);
    this->m_Keys.push_back(GLFW_MOUSE_BUTTON_LEFT);

    this->m_KeyboardControls = std::make_unique<VK::CInput>(this->m_Keys);
    this->m_KeyboardControls->SetIsEnabled(true);
    this->m_KeyboardControls->SetupKeyInputs(*this->m_Window->window);
}

void CGameLayer::UpdateCamera(const float& dt) {
     this->m_Camera->UpdateUniforms(this->GetShader("PBR"));

    if (this->m_MousePositionX != this->m_LastX || this->m_MousePositionY != this->m_LastY) {
        if (firstMouse) {
            this->m_LastX = this->m_MousePositionX;
            this->m_LastY = this->m_MousePositionY;
            firstMouse = false;
        }

        double xoffset = this->m_MousePositionX - this->m_LastX;
        double yoffset = this->m_LastY - this->m_MousePositionY;

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

    if (!this->m_MouseEnabled) {
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

        // speed
        if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
            this->m_CameraMoveSpeed = 8.f;
        } else if (this->m_KeyboardControls->IsKeyDown(GLFW_KEY_LEFT_ALT)) {
            this->m_CameraMoveSpeed = 2.f;
        } else {
            this->m_CameraMoveSpeed = 4.f;
        }
    }
}