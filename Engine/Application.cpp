#include <string_view>
#include "Application.h"

#include "Base.h"

#include "Renderer/Renderer.h"

namespace Vision {
    /* Variables */
    Application* Application::m_Instance = nullptr;
    LayerStack Application::m_LayerStack;
    float Application::m_DeltaTime;

    /* Functions */
    Application::Application(const uint32_t &windowWidth, const uint32_t &windowHeight,
                                     std::string_view windowTitle) {

        Application::m_Instance = this;

        Renderer::m_Window = CreateRef<Window>(windowWidth, windowHeight, windowTitle);

        Renderer::Initialize();
//        InputManager::Initialize(Renderer::Window);
    }

    void Application::InitializeCallbacks() {

    }

    void Application::InitializeOpenGL() {

    }

    void Application::Update() {
        glfwPollEvents();

        for (Layer* Layer : m_LayerStack) {
            Layer->OnUpdate(Application::m_Instance->m_DeltaTime);
        }
    }

    void Application::Render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Layer* Layer : Application::m_Instance->m_LayerStack) {
            Layer->OnRender(Application::m_Instance->m_DeltaTime);
        }

        glfwSwapBuffers(Renderer::m_Window->MainWindow);
    }

/*
 * Game Update Loop
 */
    void Application::Run() {
        while (!glfwWindowShouldClose(Renderer::m_Window->MainWindow)) {
            Application::Update();
            Application::Render();
        }
    }

    /*
     * Gets called when game has started running
     */
    void Application::OnAttach() {

    }

    /*
     * Gets called when game is no longer running
     */
    void Application::OnDetatch() {

    }

    void Application::PushLayer(Layer* layer) {
        Application::m_Instance->m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    /*
     * Shutdown the Game
     */
    void Application::Shutdown() {
        for (Layer* Layer : m_LayerStack) {
            Layer->OnDetach();
        }

        Renderer::Shutdown();
    }

    Application::~Application() {

    }
}