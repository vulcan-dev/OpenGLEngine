#pragma once

#include "GameLayer.h"

static CApplication* CreateApplication();

class CApp : public CApplication {
public:
    CApp() : CApplication(1280, 960, "OpenGL Engine") {
        PushLayer(new CGameLayer());
    }

    ~CApp() {}
};

CApplication* CreateApplication() {
    return new CApp();
}