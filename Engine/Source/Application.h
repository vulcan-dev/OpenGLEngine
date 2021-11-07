#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "Core/Engine.h"
#include "Cube.h"

class CApplication : public CEngine {
public:
    CApplication(const uint32_t& windowWidth, const uint32_t& windowHeight, std::string_view windowTitle);

    void Update();
    void Render();

    ~CApplication();

private:
    CCube* m_Cube;
};

#endif