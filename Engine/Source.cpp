#include "Application.h"
#include "../Application/App.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    VK::Logger::Initialize();
#ifdef DEBUG_MODE
    spdlog::set_level(spdlog::level::debug);
#endif

    auto app = CreateApplication();

    app->Run();

    delete app;

    return 0;
}