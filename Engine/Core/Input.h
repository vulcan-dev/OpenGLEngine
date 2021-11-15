#pragma once

#include <GLFW/glfw3.h>
#include <map>
#include <vector>

namespace VK {
    class CInput {
    public:
        CInput(std::vector<int> keysToMonitor);

        bool IsKeyDown(const int& key);
        bool IsKeyUp(const int& key);

        inline const bool& GetIsEnabled() const { return this->m_IsEnabled; }

        void SetIsEnabled(const bool& value) { this->m_IsEnabled = value; }
        void HandleKey(const int& key, const int8_t& action);

        ~CInput();

    public:
        static void SetupKeyInputs(GLFWwindow& window);
        static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
        static std::vector<CInput*> m_Instances;
        std::map<int, bool> m_Keys;
        bool m_IsEnabled;

        int m_CurrentKey;
    };
}