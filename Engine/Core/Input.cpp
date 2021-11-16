#include "Input.h"
#include <algorithm>

#include "Utilities/Logger.h"

namespace VK {
    std::vector<CInput*> CInput::m_Instances;

    CInput::CInput(std::vector<int> keysToMonitor) : m_IsEnabled(true) {
        for (int key : keysToMonitor) {
            this->m_Keys[key] = false;
        }

        CInput::m_Instances.push_back(this);
        this->m_CurrentKey = 0;
    }

    CInput::~CInput() {
        m_Instances.erase(std::remove(m_Instances.begin(), m_Instances.end(), this), m_Instances.end());
    }

    bool CInput::IsKeyDown(const int& key) {
        bool result = false;
        if (this->m_IsEnabled) {
            std::map<int, bool>::iterator it = this->m_Keys.find(key);
            if (it != this->m_Keys.end()) {
                result = this->m_Keys[key];
            }
        }

        return result;
    }

    bool CInput::IsKeyUp(const int &key) {
        if (key == this->m_CurrentKey) {
            this->m_CurrentKey = 0;
            return true;
        }

        return false;
    }

    void CInput::HandleKey(const int& key, const int8_t& action) {
        if (action == GLFW_RELEASE)
            this->m_CurrentKey = key;

        std::map<int, bool>::iterator it = this->m_Keys.find(key);
        if (it != this->m_Keys.end()) {
            this->m_Keys[key] = action;
        }
    }

    void CInput::SetupKeyInputs(GLFWwindow& window) {
        glfwSetKeyCallback(&window, CInput::KeyCallback);
        glfwSetMouseButtonCallback(&window, CInput::MouseCallback);
    }

    void CInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (CInput* keyInput : m_Instances) {
            keyInput->HandleKey(key, action);
        }
    }

    void CInput::MouseCallback(GLFWwindow *window, int button, int action, int mods) {
        for (CInput* keyInput : m_Instances) {
            keyInput->HandleKey(button, action);
        }
    }
}