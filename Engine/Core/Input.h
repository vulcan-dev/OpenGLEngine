#pragma once

#include <GLFW/glfw3.h>
#include <map>
#include <vector>

namespace VK {
    class CInput {
    public:
        CInput();

        static bool IsKeyDown(const int& key);
        static bool IsKeyUp(const int& key);

//        static inline const bool& GetIsEnabled();

        static void SetIsEnabled(const bool& value);
        static void HandleKey(const int& key, const int8_t& action);

        ~CInput();

    public:
        static void SetupKeyInputs(GLFWwindow& window, std::vector<int> keysToMonitor);
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, int button, int action, int mods);

    private:
        static CInput* m_Instance;
        std::map<int, bool> m_Keys;
        bool m_IsEnabled;

        int m_CurrentKey;
    };
}