bool firstMouse = true;

#include "GameLayer.h"

unsigned int sphereVAO = 0;
unsigned int indexCount;
int nrRows = 7;
int nrColumns = 7;
float spacing = 2.5;
void renderSphere()
{
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        unsigned int stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

glm::vec3 lightPositions[] = {
    glm::vec3(-10.0f,  10.0f, 10.0f),
    glm::vec3( 10.0f,  10.0f, 10.0f),
    glm::vec3(-10.0f, -10.0f, 10.0f),
    glm::vec3( 10.0f, -10.0f, 10.0f),
};

glm::vec3 lightColors[] = {
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f)
};

CGameLayer::CGameLayer() : CLayer("Game") {

}

void CGameLayer::OnAttach(CWindow* window) {
    this->m_Window = window;

    APP_INFO("Game Started");

    this->AddShader("Core", "Shaders/VertexCore.vs", "Shaders/FragmentCore.fs", "");
    this->AddShader("PBR", "Shaders/PBR.vs", "Shaders/PBR.fs");

    this->AddMaterial("Default", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1);

    this->InitializeCamera();
    this->InitializeKeybinds();

    this->m_Shaders["PBR"]->Bind();
    this->m_Shaders["PBR"]->Set1i(0, "irradianceMap");
    this->m_Shaders["PBR"]->SetVec3f(glm::vec3(.5f, .0f, .0f), "albedo");
    this->m_Shaders["PBR"]->Set1f(1.f, "ao");

    this->m_Shaders["PBR"]->SetMat4fv(this->m_Camera->GetProjection(), "projection");

    // this->m_Shaders["PBR"]->Unbind();

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
}

void CGameLayer::OnUpdate(const float& dt) {
    this->UpdateControls(dt);
    this->UpdateObjects(dt);
    this->UpdateCamera(dt);
}

void CGameLayer::OnRender() {
    this->m_Shaders["PBR"]->Bind();
    this->m_Shaders["PBR"]->SetMat4fv(this->m_Camera->GetView(), "view");
    this->m_Shaders["PBR"]->SetVec3f(this->m_CameraPosition, "camPos");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_Skybox->GetIMap());

    // glm::mat4 model = glm::mat4(1.0f);
    // for (int row = 0; row < nrRows; ++row) {
    //     this->m_Shaders["PBR"]->Set1f((float)row / (float)nrRows, "metallic");
    //     for (int col = 0; col < nrColumns; ++col) {
    //         this->m_Shaders["PBR"]->Set1f(glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f), "roughness");

    //         model = glm::mat4(1.0f);
    //         model = glm::translate(model, glm::vec3(
    //             (float)(col - (nrColumns / 2)) * spacing,
    //             (float)(row - (nrRows / 2)) * spacing,
    //             -2.0f
    //         ));
    //         this->m_Shaders["PBR"]->SetMat4fv(model, "model"); // check 4fv and normal
    //         renderSphere();
    //     }
    // }

    // for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
    //     glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
    //     newPos = lightPositions[i];
    //     this->m_Shaders["PBR"]->SetVec3f(newPos, "lightPositions[" + std::to_string(i) + "]");
    //     this->m_Shaders["PBR"]->SetVec3f(lightColors[i], "lightColors[" + std::to_string(i) + "]");

    //     model = glm::mat4(1.0f);
    //     model = glm::translate(model, newPos);
    //     model = glm::scale(model, glm::vec3(0.5f));
    //     this->m_Shaders["PBR"]->SetMat4fv(model, "model");
    //     renderSphere();
    // }

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