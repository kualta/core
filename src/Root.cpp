#include <core/Root.h>
#include <core/WindowPool.h>
#include <core/Logger.h>
#include <core/Renderer.h>
#include <core/Entity.h>

#include <SDL.h>
#include <memory>


namespace core {


Root::Root() {
    if ( !SDL_Init(SDL_INIT_EVERYTHING) ) {
        Logger::Log(INFO, INTERNAL) << "SDL initialized successfully";
    } else {
        Logger::Log(ERR, INTERNAL) << "SDL initialization failed!";
    }

    // Note: rootEntity is not the same as singleton core::Root object!
    // It is only used as Entity hierarchy root.
    Entity* rootEntity = new Entity();
    Entity::SetRoot(rootEntity);

    logger = std::make_unique<Logger>();
    renderer = std::make_unique<Renderer>();
    windowPool = std::make_unique<WindowPool>();

    Logger::Log(INFO, INTERNAL) << "- Core initialization complete -";
}
Root::~Root() {
    windowPool->DestroyAll();
    renderer->DestroyAll();
    renderer->Destroy();

    SDL_Quit();

    Logger::Log(INFO, INTERNAL) << "- Core shutdown complete -";
}

}