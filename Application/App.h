#pragma once

#include "GameLayer.h"

static CApplication* CreateApplication();

class CApp : public CApplication {
public:
    CApp() : CApplication(1280, 960, "Title") {
        PushLayer(new CGameLayer());
    }

    ~CApp() {}
};

CApplication* CreateApplication() {
    return new CApp();
}