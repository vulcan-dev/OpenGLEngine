#pragma once

#include "LayerStack.h"
#include "Core/Window.h"

namespace VK {
    class CApplication {
    public:
        CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle, bool borderless = false);

        void OnAttach();
        void OnDetatch();

        void Run();

        virtual ~CApplication();

    public:
        /*
         * GLFW Specific Abstractions
         */
        static void SetCursorPosition();
        static void SetInputMode();

        /*
         * Window Specific Functions
         */
        static GLFWwindow* GetWindow();
        static uint32_t GetWindowWidth();
        static uint32_t GetWindowHeight();
        static glm::vec2 GetWindowSize();

        /*
         * Other Functions
         */
        static float GetDeltaTime();
        static glm::vec2 GetMousePosition();
        static void Shutdown();

    protected:
        static void PushLayer(CLayer* layer);

    private:
        static void CreateWindow(bool borderless);
        static void InitializeOpenGL();
        static void UpdateTime();
        static void UpdateInput();
        static void Update();
        static void Render();

        static bool IsRunning();

    private:
        static void error_callback(int error, const char* description);
        static void window_size_callback(GLFWwindow* window, int width, int height);

    private:
        static std::string_view m_WindowTitle;
        static CLayerStack m_LayerStack;
        static CApplication* m_Instance;

        static float m_DeltaTime;
        static float m_CurrentTime;
        static float m_LastTime;
        static uint16_t m_Framerate;

        static GLint m_OpenGLMajor, m_OpenGLMinor;
        static CInput m_Input;
        static CWindow* m_Window;

        static uint32_t m_WindowWidth, m_WindowHeight;
        static double m_MousePositionX, m_MousePositionY;
    };
}