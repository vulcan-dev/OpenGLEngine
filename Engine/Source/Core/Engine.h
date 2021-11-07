#ifndef ENGINE_H
#define ENGINE_H

#include <string_view>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Utilities/Logger.h"
#include "../Global.h"

class CEngine {
public:
    CEngine(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual ~CEngine();

protected:
    inline bool IsRunning() { return !glfwWindowShouldClose(this->m_Window); }
    inline GLFWwindow* GetWindow() { return this->m_Window; }
    inline const float& GetDeltaTime() const { return this->m_DeltaTime; }

private:
    void CreateWindow();
    void UpdateTime();
    void UpdateInput();

private:
    uint32_t m_WindowWidth, m_WindowHeight;
    std::string_view m_WindowTitle;

    GLFWwindow* m_Window;

    float m_DeltaTime;
    float m_CurrentTime;
    float m_LastTime;
};

#endif