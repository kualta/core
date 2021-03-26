#include "Root.h"
#include <memory>

namespace core {


Root::Root() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        LogManager::LogInfo("SDL initialized successfully", INTERNAL);
    } else {
        LogManager::LogError("SDL initialization failed!", INTERNAL);
    }

    logManager = std::make_unique<LogManager>();
    windowManager = std::make_unique<WindowManager>();
    renderManager = std::make_unique<RenderManager>();
    soundManager = std::make_unique<SoundManager>();
    networkManager = std::make_unique<NetworkManager>();

    LogManager::LogInfo("- Core initialization complete -", INTERNAL);
}
Root::~Root() {
    windowManager->DestroyAll();

    SDL_Quit();

    LogManager::LogInfo("- Core shutdown complete -", INTERNAL);
}
const std::unique_ptr<LogManager> &Root::GetLogManager() const {
    return logManager;
}
const std::unique_ptr<WindowManager> &Root::GetWindowManager() const {
    return windowManager;
}
const std::unique_ptr<RenderManager> &Root::GetRenderManager() const {
    return renderManager;
}
const std::unique_ptr<SoundManager> &Root::GetSoundManager() const {
    return soundManager;
}
const std::unique_ptr<NetworkManager> &Root::GetNetworkManager() const {
    return networkManager;
}

}