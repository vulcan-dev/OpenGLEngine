#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Vision {
    struct Window {
        uint16_t Width;
        uint16_t Height;
        std::string_view Title;
        GLFWwindow* MainWindow;
    };

    namespace WindowCallbacks {
        static void Error(int error, const char* description) {
            CORE_ERROR("GLFW Error: {} - {}", error, description);
        }

        static void Resize(GLFWwindow* window, int width, int height) {
            CORE_INFO("Window Resized: {}x{}", width, height);
        }
    }
}