#pragma once

#include "GameLayer.h"

static VK::CApplication* CreateApplication();

class CApp : public VK::CApplication {
public:
    CApp() : VK::CApplication(1280, 960, "OpenGL Engine") {
        PushLayer(new CGameLayer());
    }

    ~CApp() {}
};

VK::CApplication* CreateApplication() {
    return new CApp();
}