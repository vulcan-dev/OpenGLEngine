#include "Application.h"
#include "Core/Utilities/Logger.h"
#include "RootDir.h.in"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    Logger::Initialize();
    CApplication Application(1280, 960, "First OpenGL Engine");

    return 0;
}