#include "Application.h"
#include "../Application/App.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
#ifdef DEBUG_MODE
    spdlog::set_level(spdlog::level::debug);
#endif
    Logger::Initialize();

    auto app = CreateApplication();

    app->Run();

    delete app;

    return 0;
}