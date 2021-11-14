#include "Input.h"
#include <algorithm>

#include "Utilities/Logger.h"

std::vector<CInput*> CInput::m_Instances;

CInput::CInput(std::vector<int> keysToMonitor) : m_IsEnabled(true) {
    for (int key : keysToMonitor) {
        this->m_Keys[key] = false;
    }

    CInput::m_Instances.push_back(this);
}

CInput::~CInput() {
    m_Instances.erase(std::remove(m_Instances.begin(), m_Instances.end(), this), m_Instances.end());
}

bool CInput::IsKeyDown(const int& key) {
    bool result = false;
    if (this->m_IsEnabled) {
        std::map<int,bool>::iterator it = this->m_Keys.find(key);
        if (it != this->m_Keys.end()) {
            result = this->m_Keys[key];
        }
    }

    return result;
}

void CInput::SetIsKeyDown(const int& key, const bool& value) {
    std::map<int,bool>::iterator it = this->m_Keys.find(key);
    if (it != this->m_Keys.end()) {
        this->m_Keys[key] = value;
    }
}

void CInput::SetupKeyInputs(GLFWwindow& window) {
    glfwSetKeyCallback(&window, CInput::Callback);
}

void CInput::Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (CInput* keyInput : m_Instances) {
        keyInput->SetIsKeyDown(key, action != GLFW_RELEASE);
    }
}