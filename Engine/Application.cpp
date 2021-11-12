#include "Application.h"

#include <glm/gtx/string_cast.hpp>
#include <string>
#include <vector>

CApplication* CApplication::m_Instance = nullptr;

void CApplication::error_callback(int error, const char* description) {
    CORE_ERROR("GLFW Error: {} - {}", error, description);
}

void CApplication::window_size_callback(GLFWwindow* window, int width, int height) {
    // Globals::Projection = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
    // TODO: Set ^ for game camera
    glViewport(0, 0, width, height);
    CORE_INFO("Window Resize: New Size = {} x {}", width, height);
}

CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle) {
    this->m_Window = new CWindow(windowWidth, windowHeight, windowTitle);

    glfwSetErrorCallback(this->error_callback);

    if (!glfwInit()) {
        CORE_CRITICAL("glfwInit failed");
        exit(1);
    }

    this->CreateWindow();
    this->InitializeOpenGL();

    CApplication::m_Instance = this;
    for (CLayer* Layer : m_LayerStack) {
        Layer->OnAttach(this->m_Window);
    }

    // while (this->IsRunning()) {
        // this->Update();
        // this->Render();
    // }
}

void CApplication::PushLayer(CLayer* layer) {
    this->m_LayerStack.PushLayer(layer);
    layer->OnAttach(this->m_Window);
}

void CApplication::InitializeOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB); 
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);

    glfwSetFramebufferSizeCallback(this->m_Window->window, this->window_size_callback);

    glGetIntegerv(GL_MAJOR_VERSION, &this->m_OpenGLMajor);
    glGetIntegerv(GL_MINOR_VERSION, &this->m_OpenGLMinor);
    CORE_INFO("OpenGL Version: {}.{}", this->m_OpenGLMajor, this->m_OpenGLMinor);
    CORE_INFO("Version: {}", glGetString(GL_VERSION));
    CORE_INFO("Graphics Card: {}", glGetString(GL_RENDERER));
    CORE_INFO("Shader Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    GLint extensionCount = 0; 
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensionCount); 

    CORE_INFO("{} Extensions Supported", extensionCount);
}

void CApplication::CreateWindow() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_Window->window = glfwCreateWindow(this->m_Window->width, this->m_Window->height, this->m_Window->title.data(), nullptr, nullptr);
    CORE_INFO("Created Window: {} x {}", this->m_Window->width, this->m_Window->height);

    glfwSetWindowSizeLimits(this->m_Window->window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(this->m_Window->window);
    glewInit();
}

void CApplication::Run() {
    while (this->IsRunning()) {
        this->UpdateTime();
        this->UpdateInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (CLayer* Layer : m_LayerStack) {
            Layer->OnRender();
            Layer->OnUpdate(this->m_DeltaTime);
        }

        glfwSwapBuffers(this->m_Window->window);
        glfwPollEvents();
    }
}

void CApplication::UpdateInput() {
    glfwGetCursorPos(this->m_Window->window, &this->m_MousePositionX, &this->m_MousePositionY);
}

void CApplication::UpdateTime() {
    this->m_CurrentTime = static_cast<float>(glfwGetTime());
    this->m_DeltaTime = this->m_CurrentTime - this->m_LastTime;
    this->m_LastTime = this->m_CurrentTime;

    this->m_Framerate = static_cast<int16_t>(1.f/this->m_DeltaTime);
}

void CApplication::Render() {
    for (CLayer* Layer : m_LayerStack) {
        Layer->OnRender();
    }
}

CApplication::~CApplication() {
    glfwTerminate();
    delete this->m_Window;
}