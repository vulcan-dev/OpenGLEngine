#ifndef ENGINE_H
#define ENGINE_H

#include "LayerStack.h"

class CApplication {
public:
    CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    void Render();
    void OnAttach();
    void OnDetatch();

    void Run();

    virtual ~CApplication();

protected:
    void PushLayer(CLayer* layer);

    inline bool IsRunning() { return !glfwWindowShouldClose(this->m_Window); }

    inline GLFWwindow* GetWindow() { return this->m_Window; }
    inline const float& GetDeltaTime() const { return this->m_DeltaTime; }

    void AddShader(std::string_view name, std::string_view vertex, std::string_view fragment, std::string_view geometry) { this->m_Shaders[name.data()] = std::make_shared<CShader>(vertex.data(), fragment.data(), geometry.data()); }
    inline CShader* GetShader(std::string_view name) { return this->m_Shaders[name.data()].get(); }

    void AddTexture(std::string_view name, std::string_view filename, GLenum type) { this->m_Textures[name.data()] = std::make_shared<CTexture>(filename.data(), type); }
    inline CTexture* GetTexture(std::string_view name) { return this->m_Textures[name.data()].get(); }

    void AddMaterial(std::string_view name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTexture, GLint specularTexture) { this->m_Materials[name.data()] = std::make_shared<CMaterial>(ambient, diffuse, specular, diffuseTexture, specularTexture); }
    inline CMaterial* GetMaterial(std::string_view name) { return this->m_Materials[name.data()].get(); }

    uint32_t m_WindowWidth, m_WindowHeight;

    double m_MousePositionX, m_MousePositionY;

private:
    void CreateWindow();
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

    GLFWwindow* m_Window;

    float m_DeltaTime;
    float m_CurrentTime;
    float m_LastTime;
    uint16_t m_Framerate;

    GLint m_OpenGLMajor, m_OpenGLMinor;

private:
    std::map<std::string, Ref<CShader>> m_Shaders;
    std::map<std::string, Ref<CTexture>> m_Textures;
    std::map<std::string, Ref<CMaterial>> m_Materials;

    Ref<CInput> m_KeyboardControls;
};

#endif