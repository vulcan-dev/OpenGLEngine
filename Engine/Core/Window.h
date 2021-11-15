#pragma once

#include <GLFW/glfw3.h>

namespace VK {
    struct CWindow {
        int width, height;
        std::string_view title;
        GLFWwindow* window;
    };
}