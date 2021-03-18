#include "Root.h"
#include <memory>

namespace core {


Root::Root() {
    objectsCounter = 1;

    logManager = std::make_unique<LogManager>();
    windowManager = std::make_unique<WindowManager>();
    renderManager = std::make_unique<RenderManager>();
    inputManager = std::make_unique<InputManager>();
    soundManager = std::make_unique<SoundManager>();
    networkManager = std::make_unique<NetworkManager>();

    LogManager::LogInfo("- Core initialization complete -", INTERNAL);
}
Root::~Root() {
    windowManager->DestroyAll();

    SDL_Quit();

    LogManager::LogInfo("- Core shutdown complete -", INTERNAL);
}
uint32_t Root::GetNewID() {
    objectsCounter++;

    return objectsCounter;
}

}