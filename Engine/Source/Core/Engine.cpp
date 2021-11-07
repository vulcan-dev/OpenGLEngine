#include "Engine.h"

#include "../Global.h"

void CEngine::error_callback(int error, const char* description) {
    CORE_ERROR("GLFW Error: {} - {}", error, description);
}

void CEngine::window_size_callback(GLFWwindow* window, int width, int height) {
    Globals::Projection = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
    glViewport(0, 0, width, height);
    CORE_INFO("Window Resize: New Size = {} x {}", width, height);
    CORE_INFO("Projection: {}", Globals::Projection[0][0]);
}

CEngine::CEngine(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle) :
        m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_WindowTitle(windowTitle) {
    glfwSetErrorCallback(this->error_callback);

    if (!glfwInit()) {
        CORE_CRITICAL("glfwInit failed");
        exit(1);
    }

    this->CreateWindow();

    glEnable(GL_DEPTH_TEST);

    Globals::Projection = glm::perspective(glm::radians(90.0f), (float)this->m_WindowWidth / (float)this->m_WindowHeight, 0.1f, 100.0f);
    Globals::View = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glfwSetFramebufferSizeCallback(this->m_Window, this->window_size_callback);
}

void CEngine::CreateWindow() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_Window = glfwCreateWindow(this->m_WindowWidth, this->m_WindowHeight, this->m_WindowTitle.data(), nullptr, nullptr);
    CORE_INFO("Created Window: {} x {}", this->m_WindowWidth, this->m_WindowHeight);

    glfwMakeContextCurrent(this->m_Window);
    glewInit();
}

void CEngine::Update() {
    this->UpdateTime();
    this->UpdateInput();
}

void CEngine::UpdateInput() {

}

void CEngine::UpdateTime() {
    this->m_CurrentTime = static_cast<float>(glfwGetTime());
    this->m_DeltaTime = this->m_CurrentTime - this->m_LastTime;
    this->m_LastTime = this->m_CurrentTime;
}

void CEngine::Render() {
    
}

CEngine::~CEngine() {
    glfwTerminate();
}