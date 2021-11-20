#pragma once

#include "Vision.h"
#include "Layer.h"
#include <cstdint>
#include "LayerStack.h"

namespace Vision {
    class Application {
    public:
        Application(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

        void Run();

        void OnAttach();
        void OnDetatch();
        void PushLayer(Layer* layer);

        virtual ~Application();

    public:
        static void Shutdown();

    private:
        static void InitializeCallbacks();
        static void InitializeOpenGL();

        static void Update();
        static void Render();

    private:
        /* Variables */
        static Application* m_Instance;
        static LayerStack m_LayerStack;
        static float m_DeltaTime;
    };
}