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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL

    // TODO: Move to a seperate class (Camera)
    Globals::Projection = glm::perspective(glm::radians(90.0f), (float)this->m_WindowWidth / (float)this->m_WindowHeight, 0.1f, 100.0f);
    Globals::View = glm::lookAt(
        glm::vec3(0, 0, 5), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glfwSetFramebufferSizeCallback(this->m_Window, this->window_size_callback);

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

void CEngine::CreateWindow() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_Window = glfwCreateWindow(this->m_WindowWidth, this->m_WindowHeight, this->m_WindowTitle.data(), nullptr, nullptr);
    CORE_INFO("Created Window: {} x {}", this->m_WindowWidth, this->m_WindowHeight);

    glfwSetWindowSizeLimits(this->m_Window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);

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