#pragma once

#include "../Engine/Application.h"
#include "Game.h"

static Vision::Application* CreateApplication();

class App : public Vision::Application {
public:
    App() : Vision::Application(1280, 960, "Vision Application") {
        PushLayer(new Game());
    }

    ~App() {}
};

Vision::Application* CreateApplication() {
    return new App();
}