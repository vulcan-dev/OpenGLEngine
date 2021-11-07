#include "Application.h"
#include "Core/Utilities/Logger.h"
#include "RootDir.h.in"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    Logger::Initialize();
    CApplication Application(800, 600, "Title");

    return 0;
}