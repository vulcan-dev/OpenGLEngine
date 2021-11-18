#include "Application.h"

#include <glm/gtx/string_cast.hpp>
#include <string>
#include <vector>

/*
 * Variables
 */
namespace VK {
    CApplication *CApplication::m_Instance = nullptr;
    std::string_view CApplication::m_WindowTitle = "";
    CLayerStack CApplication::m_LayerStack;

    float CApplication::m_DeltaTime = 0.f;
    float CApplication::m_CurrentTime = 0.f;
    float CApplication::m_LastTime = 0.f;
    uint16_t CApplication::m_Framerate = 0;

    GLint CApplication::m_OpenGLMajor, CApplication::m_OpenGLMinor = 0;
    CWindow *CApplication::m_Window = nullptr;
    CInput CApplication::m_Input;

    uint32_t CApplication::m_WindowWidth, CApplication::m_WindowHeight;

    double CApplication::m_MousePositionX, CApplication::m_MousePositionY;
}

namespace VK {
    /*
     * GLFW Callbacks
     */
    void CApplication::error_callback(int error, const char* description) {
        CORE_ERROR("GLFW Error: {} - {}", error, description);
    }

    void CApplication::window_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        CORE_INFO("Window Resize: New Size = {} x {}", width, height);
    }

    CApplication::CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle, bool borderless) {
        CApplication::m_Instance = this;
        CApplication::m_Instance->m_Window = new CWindow{static_cast<int>(windowWidth), static_cast<int>(windowHeight), windowTitle};

        glfwSetErrorCallback(CApplication::m_Instance->error_callback);

        if (!glfwInit()) {
            CORE_CRITICAL("glfwInit failed");
            exit(1);
        }

        CApplication::m_Instance->CreateWindow(borderless);
        CApplication::m_Instance->InitializeOpenGL();

        for (CLayer* Layer : m_LayerStack) {
            Layer->OnAttach();
        }
    }

    void CApplication::PushLayer(CLayer* layer) {
        CApplication::m_Instance->m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void CApplication::InitializeOpenGL() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glDepthFunc(GL_LEQUAL);
        glFrontFace(GL_CCW);

        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        glfwSetFramebufferSizeCallback(CApplication::m_Instance->m_Window->window, CApplication::m_Instance->window_size_callback);

        glGetIntegerv(GL_MAJOR_VERSION, &CApplication::m_Instance->m_OpenGLMajor);
        glGetIntegerv(GL_MINOR_VERSION, &CApplication::m_Instance->m_OpenGLMinor);
        CORE_INFO("OpenGL Version: {}.{}", CApplication::m_Instance->m_OpenGLMajor, CApplication::m_Instance->m_OpenGLMinor);
        CORE_INFO("Version: {}", glGetString(GL_VERSION));
        CORE_INFO("Graphics Card: {}", glGetString(GL_RENDERER));
        CORE_INFO("Shader Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
        
        GLint extensionCount = 0; 
        glGetIntegerv(GL_NUM_EXTENSIONS, &extensionCount); 

        CORE_INFO("{} Extensions Supported", extensionCount);

        glfwGetFramebufferSize(CApplication::m_Instance->m_Window->window, &CApplication::m_Instance->m_Window->width, &CApplication::m_Instance->m_Window->height);
        glViewport(0, 0, CApplication::m_Instance->m_Window->width, CApplication::m_Instance->m_Window->height);
    }

    void CApplication::CreateWindow(bool borderless) {
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_AUTO_ICONIFY , GLFW_FALSE);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        
        if (borderless) {
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
            CApplication::m_Instance->m_Window->window = glfwCreateWindow(mode->width, mode->height, CApplication::m_Instance->m_Window->title.data(), glfwGetPrimaryMonitor(), nullptr);
        } else {
            CApplication::m_Instance->m_Window->window = glfwCreateWindow(CApplication::m_Instance->m_Window->width, CApplication::m_Instance->m_Window->height, CApplication::m_Instance->m_Window->title.data(), nullptr, nullptr);
            glfwSetWindowSizeLimits(CApplication::m_Instance->m_Window->window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
        }

        CORE_INFO("Created Window: {} x {}", CApplication::m_Instance->m_Window->width, CApplication::m_Instance->m_Window->height);

        glfwMakeContextCurrent(CApplication::m_Instance->m_Window->window);
        glewInit();
    }

    void CApplication::Run() {
        while (CApplication::m_Instance->IsRunning()) {
            CApplication::m_Instance->Update();

            CApplication::m_Instance->UpdateTime();
            CApplication::m_Instance->UpdateInput();

            CApplication::m_Instance->Render();
        }
    }

    void CApplication::Shutdown() {
        for (CLayer* Layer : m_LayerStack) {
            Layer->OnDetach();
        }

        glfwSetWindowShouldClose(CApplication::m_Instance->m_Window->window, true);
        delete CApplication::m_Instance;
    }

    void CApplication::UpdateInput() {
        glfwGetCursorPos(CApplication::m_Instance->m_Window->window, &CApplication::m_Instance->m_MousePositionX, &CApplication::m_Instance->m_MousePositionY);
    }

    void CApplication::UpdateTime() {
        CApplication::m_Instance->m_CurrentTime = static_cast<float>(glfwGetTime());
        CApplication::m_Instance->m_DeltaTime = CApplication::m_Instance->m_CurrentTime - CApplication::m_Instance->m_LastTime;
        CApplication::m_Instance->m_LastTime = CApplication::m_Instance->m_CurrentTime;

        CApplication::m_Instance->m_Framerate = static_cast<int16_t>(1.f/CApplication::m_Instance->m_DeltaTime);
    }

    void CApplication::Update() {
        glfwPollEvents();

        for (CLayer* Layer : m_LayerStack) {
            Layer->OnUpdate(CApplication::m_Instance->m_DeltaTime);
        }
    }

    void CApplication::Render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (CLayer* Layer : CApplication::m_Instance->m_LayerStack) {
            Layer->OnRender(CApplication::m_Instance->m_DeltaTime);
        }

        glfwSwapBuffers(CApplication::m_Instance->m_Window->window);
    }

    CApplication::~CApplication() {

    }

    bool CApplication::IsRunning() {
        return !glfwWindowShouldClose(CApplication::m_Instance->m_Window->window);
    }

    /*
     * Window Specific Functions
     */
    GLFWwindow *CApplication::GetWindow() {
        return CApplication::m_Instance->m_Window->window;
    }

    uint32_t CApplication::GetWindowWidth() {
        return CApplication::m_Instance->m_Window->width;
    }

    uint32_t CApplication::GetWindowHeight() {
        return CApplication::m_Instance->m_Window->height;
    }

    glm::vec2 CApplication::GetWindowSize() {
        return glm::vec2(CApplication::m_Instance->m_Window->width, CApplication::m_Instance->m_Window->height);
    }

    /*
     * Other Functions
     */
    float CApplication::GetDeltaTime() {
        return CApplication::m_Instance->m_DeltaTime;
    }

    glm::vec2 CApplication::GetMousePosition() {
        return glm::vec2(CApplication::m_Instance->m_MousePositionX, CApplication::m_Instance->m_MousePositionY);
    }
}