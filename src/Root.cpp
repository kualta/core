#include <core/Root.h>
#include <core/WindowPool.h>
#include <core/Logger.h>
#include <core/RenderManager.h>
#include <core/Entity.h>

#include <SDL.h>
#include <memory>


namespace core {


Root::Root() {
    if ( !SDL_Init(SDL_INIT_EVERYTHING) ) {
        Logger::LogInfo("SDL initialized successfully", INTERNAL);
    } else {
        Logger::LogError("SDL initialization failed!", INTERNAL);
    }

    // Note: rootEntity is not the same as singleton core::Root object!
    // It is only used as Entity hierarchy root.
    Entity* rootEntity = new Entity();
    Entity::SetRoot(rootEntity);

    logger = std::make_unique<Logger>();
    renderManager = std::make_unique<RenderManager>();
    windowPool = std::make_unique<WindowPool>();

    Logger::LogInfo("- Core initialization complete -", INTERNAL);
}
Root::~Root() {
    windowPool->DestroyAll();

    SDL_Quit();

    Logger::LogInfo("- Core shutdown complete -", INTERNAL);
}
const std::unique_ptr<Logger> &Root::GetLogManager() const {
    return logger;
}
const std::unique_ptr<RenderManager> &Root::GetRenderManager() const {
    return renderManager;
}

}