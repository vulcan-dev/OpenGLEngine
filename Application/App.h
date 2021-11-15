#pragma once

#include "GameLayer.h"

static VK::CApplication* CreateApplication();

class CApp : public VK::CApplication {
public:
    CApp() : VK::CApplication(1920, 1080, "OpenGL Engine", true) {
        PushLayer(new CGameLayer());
    }

    ~CApp() {}
};

VK::CApplication* CreateApplication() {
    return new CApp();
}