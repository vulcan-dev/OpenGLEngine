#include "Skybox.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb_image.h"

glm::mat4 captureViews[] = {
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
};

unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;

unsigned int captureFBO, captureRBO;

// int nrRows = 7;
// int nrColumns = 7;
// float spacing = 2.5;

// glm::vec3 lightPositions[] = {
//     glm::vec3(-10.0f,  10.0f, 10.0f),
//     glm::vec3( 10.0f,  10.0f, 10.0f),
//     glm::vec3(-10.0f, -10.0f, 10.0f),
//     glm::vec3( 10.0f, -10.0f, 10.0f),
// };

// glm::vec3 lightColors[] = {
//     glm::vec3(300.0f, 300.0f, 300.0f),
//     glm::vec3(300.0f, 300.0f, 300.0f),
//     glm::vec3(300.0f, 300.0f, 300.0f),
//     glm::vec3(300.0f, 300.0f, 300.0f)
// };

// unsigned int m_IrradianceMap;

// unsigned int sphereVAO = 0;
// unsigned int indexCount;
// void renderSphere()
// {
//     if (sphereVAO == 0)
//     {
//         glGenVertexArrays(1, &sphereVAO);

//         unsigned int vbo, ebo;
//         glGenBuffers(1, &vbo);
//         glGenBuffers(1, &ebo);

//         std::vector<glm::vec3> positions;
//         std::vector<glm::vec2> uv;
//         std::vector<glm::vec3> normals;
//         std::vector<unsigned int> indices;

//         const unsigned int X_SEGMENTS = 64;
//         const unsigned int Y_SEGMENTS = 64;
//         const float PI = 3.14159265359;
//         for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//         {
//             for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
//             {
//                 float xSegment = (float)x / (float)X_SEGMENTS;
//                 float ySegment = (float)y / (float)Y_SEGMENTS;
//                 float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//                 float yPos = std::cos(ySegment * PI);
//                 float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

//                 positions.push_back(glm::vec3(xPos, yPos, zPos));
//                 uv.push_back(glm::vec2(xSegment, ySegment));
//                 normals.push_back(glm::vec3(xPos, yPos, zPos));
//             }
//         }

//         bool oddRow = false;
//         for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
//         {
//             if (!oddRow) // even rows: y == 0, y == 2; and so on
//             {
//                 for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//                 {
//                     indices.push_back(y * (X_SEGMENTS + 1) + x);
//                     indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//                 }
//             }
//             else
//             {
//                 for (int x = X_SEGMENTS; x >= 0; --x)
//                 {
//                     indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//                     indices.push_back(y * (X_SEGMENTS + 1) + x);
//                 }
//             }
//             oddRow = !oddRow;
//         }
//         indexCount = indices.size();

//         std::vector<float> data;
//         for (unsigned int i = 0; i < positions.size(); ++i)
//         {
//             data.push_back(positions[i].x);
//             data.push_back(positions[i].y);
//             data.push_back(positions[i].z);
//             if (normals.size() > 0)
//             {
//                 data.push_back(normals[i].x);
//                 data.push_back(normals[i].y);
//                 data.push_back(normals[i].z);
//             }
//             if (uv.size() > 0)
//             {
//                 data.push_back(uv[i].x);
//                 data.push_back(uv[i].y);
//             }
//         }
//         glBindVertexArray(sphereVAO);
//         glBindBuffer(GL_ARRAY_BUFFER, vbo);
//         glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//         unsigned int stride = (3 + 2 + 3) * sizeof(float);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
//         glEnableVertexAttribArray(1);
//         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
//         glEnableVertexAttribArray(2);
//         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
//     }

//     glBindVertexArray(sphereVAO);
//     glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
// }


void CSkybox::RenderSkyboxCube() {
    if (cubeVAO == 0) {
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

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

CSkybox::CSkybox(CWindow* window, CPerspectiveCamera* camera, glm::vec3 cameraPos) {
    this->InitializeShaders();
    this->InitializeHDR();
    this->InitializeCubemap(camera, cameraPos);

    this->m_Window = window;
}

void CSkybox::InitializeShaders() {
    // this->AddShader("PBR", "Shaders/PBR.vs", "Shaders/PBR.fs");
    this->AddShader("ETCShader", "Shaders/Cubemap.vs", "Shaders/ETC.fs");
    this->AddShader("IShader", "Shaders/Cubemap.vs", "Shaders/Irradiance.fs");
    this->AddShader("BGShader", "Shaders/Background.vs", "Shaders/Background.fs");

    // TODO: Finish https://learnopengl.com/PBR/IBL/Specular-IBL
    this->AddShader("PFShader", "Shaders/Cubemap.vs", "Shaders/Prefilter.fs");
    this->AddShader("BRDFShader", "Shaders/BRDF.vs", "Shaders/BRDF.fs");

    // this->m_Shaders["PBR"]->Bind();
    // this->m_Shaders["PBR"]->Set1i(0, "m_IrradianceMap");
    // this->m_Shaders["PBR"]->SetVec3f(glm::vec3(.5f, .0f, .0f), "albedo");
    // this->m_Shaders["PBR"]->Set1f(1.f, "ao");

    this->m_Shaders["BGShader"]->Bind();
    this->m_Shaders["BGShader"]->Set1i(0, "environmentMap");

    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
}

void CSkybox::InitializeHDR() {
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf(fmt::format("..{}/{}", ROOT_DIR, "Skyboxes/adams_place_bridge_4k.hdr").c_str(), &width, &height, &nrComponents, 0);

    if (data) {
        glGenTextures(1, &this->m_Texture);
        glBindTexture(GL_TEXTURE_2D, this->m_Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        CORE_ERROR("cannot load");
    }
}

void CSkybox::InitializeCubemap(CPerspectiveCamera* camera, glm::vec3 cameraPos) {
    glGenTextures(1, &this->m_Cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_Cubemap);

    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    this->m_Shaders["ETCShader"]->Bind();
    this->m_Shaders["ETCShader"]->Set1i(0, "equirectangularMap");
    this->m_Shaders["ETCShader"]->SetMat4fv(camera->GetProjection(), "projection");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_Texture);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i) {
        this->m_Shaders["ETCShader"]->SetMat4fv(captureViews[i], "view");
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->m_Cubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->RenderSkyboxCube();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    glGenTextures(1, &m_IrradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_IrradianceMap);
    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    /* Solve Diffuse Cubemap */
    this->m_Shaders["IShader"]->Bind();
    this->m_Shaders["IShader"]->Set1i(0, "environmentMap");
    this->m_Shaders["IShader"]->SetMat4fv(camera->GetProjection(), "projection");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_Cubemap);

    glViewport(0, 0, 32, 32);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i) {
        this->m_Shaders["IShader"]->SetMat4fv(captureViews[i], "view");
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_IrradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->RenderSkyboxCube();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* Initialize Uniforms */
    // this->m_Shaders["PBR"]->Bind();
    // this->m_Shaders["PBR"]->SetMat4fv(camera->GetProjection(), "projection");
    this->m_Shaders["BGShader"]->Bind();
    this->m_Shaders["BGShader"]->SetMat4fv(camera->GetProjection(), "projection");

    // int scrWidth, scrHeight;
    // glfwGetFramebufferSize(this->m_Window->window, &scrWidth, &scrHeight);
    // glViewport(0, 0, scrWidth, scrHeight);
}

void CSkybox::UpdateUniforms(CPerspectiveCamera* camera, glm::vec3 cameraPos) {
    
}

void CSkybox::Render(CPerspectiveCamera* camera, glm::vec3 cameraPos) {
    // this->UpdateUniforms(camera, cameraPos);

    // Bind All Shaders

    this->m_Shaders["BGShader"]->Bind();
    this->m_Shaders["BGShader"]->SetMat4fv(camera->GetView(), "view");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_Cubemap);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, m_IrradianceMap);
    glDisable(GL_CULL_FACE);
    this->RenderSkyboxCube();
    glEnable(GL_CULL_FACE);
}

CSkybox::~CSkybox() {
    // glDeleteVertexArrays(1, &this->m_VAO);
    // glDeleteBuffers(1, &this->m_VBO);

    // if (this->m_TotalIndices > 0) {
    //     glDeleteBuffers(1, &this->m_EBO);
    // }

    // delete[] this->m_VertexArray;
    // delete[] this->m_IndexArray;
}