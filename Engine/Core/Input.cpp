#include "Input.h"
#include <algorithm>

#include "Utilities/Logger.h"

namespace VK {
    CInput* CInput::m_Instance = nullptr;

    CInput::CInput() {
        CInput::m_Instance = this;
    }

    CInput::~CInput() {
        delete CInput::m_Instance;
    }

    void CInput::SetIsEnabled(const bool &value) {
        CInput::m_Instance->m_IsEnabled = value;
    }

    bool CInput::IsKeyDown(const int& key) {
        bool result = false;
        if (CInput::m_Instance->m_IsEnabled) {
            std::map<int, bool>::iterator it = CInput::m_Instance->m_Keys.find(key);
            if (it != CInput::m_Instance->m_Keys.end()) {
                result = CInput::m_Instance->m_Keys[key];
            }
        }

        return result;
    }

    bool CInput::IsKeyUp(const int &key) {
        if (key == CInput::m_Instance->m_CurrentKey) {
            CInput::m_Instance->m_CurrentKey = 0;
            return true;
        }

        return false;
    }

    void CInput::HandleKey(const int& key, const int8_t& action) {
        if (action == GLFW_RELEASE)
            CInput::m_Instance->m_CurrentKey = key;

        std::map<int, bool>::iterator it = CInput::m_Instance->m_Keys.find(key);
        if (it != CInput::m_Instance->m_Keys.end()) {
            CInput::m_Instance->m_Keys[key] = action;
        }
    }

    void CInput::SetupKeyInputs(GLFWwindow& window, std::vector<int> keysToMonitor) {
        for (int key : keysToMonitor) {
            CInput::m_Instance->m_Keys[key] = false;
        }

        CInput::m_Instance->m_CurrentKey = 0;

        glfwSetKeyCallback(&window, CInput::KeyCallback);
        glfwSetMouseButtonCallback(&window, CInput::MouseCallback);
    }

    void CInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        CInput::m_Instance->HandleKey(key, action);
    }

    void CInput::MouseCallback(GLFWwindow *window, int button, int action, int mods) {
        CInput::m_Instance->HandleKey(button, action);
    }
}