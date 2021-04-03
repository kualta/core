#include <core/Root.h>
#include <core/WindowPool.h>

#include <memory>


namespace core {


Root::Root() {
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        LogManager::LogInfo("SDL initialized successfully", INTERNAL);
    } else {
        LogManager::LogError("SDL initialization failed!", INTERNAL);
    }

    logManager = std::make_unique<LogManager>();
    renderManager = std::make_unique<RenderManager>();
    soundManager = std::make_unique<SoundManager>();
    networkManager = std::make_unique<NetworkManager>();

    windowPool = std::make_unique<WindowPool>();

    LogManager::LogInfo("- Core initialization complete -", INTERNAL);
}
Root::~Root() {
    windowPool->DestroyAll();

    SDL_Quit();

    LogManager::LogInfo("- Core shutdown complete -", INTERNAL);
}
const std::unique_ptr<LogManager> &Root::GetLogManager() const {
    return logManager;
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