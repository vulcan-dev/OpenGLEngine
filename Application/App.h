#pragma once

#include "GameLayer.h"

static CApplication* CreateApplication();

class CApp : public CApplication {
public:
    CApp() : CApplication(1920, 1080, "OpenGL Engine", true) {
        PushLayer(new CGameLayer());
    }

    ~CApp() {}
};

CApplication* CreateApplication() {
    return new CApp();
}