#ifndef ENGINE_H
#define ENGINE_H

#include "Include.h"

class CEngine {
public:
    CEngine(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual ~CEngine();

private:
    static void error_callback(int error, const char* description);
    static void window_size_callback(GLFWwindow* window, int width, int height);

protected:
    inline bool IsRunning() { return !glfwWindowShouldClose(this->m_Window); }
    inline GLFWwindow* GetWindow() { return this->m_Window; }
    inline const float& GetDeltaTime() const { return this->m_DeltaTime; }
    uint32_t m_WindowWidth, m_WindowHeight;

    double m_MousePositionX, m_MousePositionY;

private:
    void CreateWindow();
    void UpdateTime();
    void UpdateInput();

private:
    std::string_view m_WindowTitle;

    GLFWwindow* m_Window;

    float m_DeltaTime;
    float m_CurrentTime;
    float m_LastTime;
    uint16_t m_Framerate;

    GLint m_OpenGLMajor, m_OpenGLMinor;
};

#endif