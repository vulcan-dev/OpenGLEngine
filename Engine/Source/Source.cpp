#include "Application.h"
#include "Core/Utilities/Logger.h"
#include "RootDir.h.in"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
#ifdef DEBUG_MODE
    spdlog::set_level(spdlog::level::debug);
#endif

    Logger::Initialize();
    CApplication Application(1280, 960, "First OpenGL Engine");

    return 0;
}