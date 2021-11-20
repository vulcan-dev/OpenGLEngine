#include "Renderer.h"

#include "../Application.h"

namespace Vision {
    Ref<Window> Renderer::m_Window;

    void Renderer::Initialize() {
        glfwSetErrorCallback(WindowCallbacks::Error);

        Renderer::CreateWindow();
        Renderer::InitializeOpenGL();

        glfwSetWindowSizeCallback(Renderer::m_Window->MainWindow, WindowCallbacks::Resize);
    }

    void Renderer::CreateWindow() {
        if (!glfwInit()) {
            CORE_CRITICAL("GLFW Init Failed! {}", glfwGetError(nullptr));
            Application::Shutdown();
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_AUTO_ICONIFY , GLFW_FALSE);

        Renderer::m_Window->MainWindow = glfwCreateWindow(Renderer::m_Window->Width, Renderer::m_Window->Height, Renderer::m_Window->Title.data(), nullptr, nullptr);
        glfwMakeContextCurrent(Renderer::m_Window->MainWindow);
        glewInit();
    }

    void Renderer::InitializeOpenGL() {

    }

    void Renderer::Shutdown() {
        if (Renderer::m_Window->MainWindow) {
            glfwDestroyWindow(Renderer::m_Window->MainWindow);
            glfwTerminate();
        }
    }
}