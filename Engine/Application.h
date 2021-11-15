#pragma once

#include "LayerStack.h"
#include "Core/Window.h"

namespace VK {
    class CApplication {
    public:
        CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle, bool borderless = false);

        void Render();
        void OnAttach(CWindow* window);
        void OnDetatch();

        void Run();

        virtual ~CApplication();

    protected:
        void PushLayer(CLayer* layer);

        inline bool IsRunning() { return !glfwWindowShouldClose(this->m_Window->window); }

        inline GLFWwindow* GetWindow() { return this->m_Window->window; }
        inline const float& GetDeltaTime() const { return this->m_DeltaTime; }

        uint32_t m_WindowWidth, m_WindowHeight;

        double m_MousePositionX, m_MousePositionY;

    private:
        void CreateWindow(bool borderless);
        void InitializeOpenGL();
        void UpdateTime();
        void UpdateInput();

    private:
        static void error_callback(int error, const char* description);
        static void window_size_callback(GLFWwindow* window, int width, int height);

    private:
        std::string_view m_WindowTitle;
        CLayerStack m_LayerStack;
        static CApplication* m_Instance;

        float m_DeltaTime;
        float m_CurrentTime;
        float m_LastTime;
        uint16_t m_Framerate;

        GLint m_OpenGLMajor, m_OpenGLMinor;
        CWindow* m_Window;
    };
}