#pragma once

#include "../Base.h"

#include "Window.h"

namespace Vision {
    class Renderer {
    public:
        static void Initialize();
        static void Shutdown();

    public:
        static Ref<Window> m_Window;

    private:
        static void CreateWindow();
        static void InitializeOpenGL();
    };
}