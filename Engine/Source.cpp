#include "Application.h"
#include "Utilities/Logger.h"
#include "../Application/App.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    Vision::Logger::Initialize();

    Vision::Application* Application = CreateApplication();
    Application->Run();

    delete Application;

    return 0;
}