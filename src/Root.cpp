#include <core/Root.h>
#include <core/WindowPool.h>
#include "core/LogManager.h"
#include "core/RenderManager.h"

#include <SDL.h>
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

}