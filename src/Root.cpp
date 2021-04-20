#include <core/Root.h>
#include <core/EntityPool.h>
#include <core/Renderer.h>
#include <core/Entity.h>

#include <SDL.h>
#include <memory>


namespace core {


Root::Root() : Object("Root") {
    if ( !SDL_Init(SDL_INIT_EVERYTHING) ) {
        Logger::Log(INFO, INTERNAL) << "SDL initialized successfully";
    } else {
        Logger::Log(ERR, INTERNAL) << "SDL initialization failed!";
    }

    logger = std::make_unique<Logger>();
    renderer = std::make_unique<Renderer>();
    windowPool = std::make_unique<Pool<Window>>("Windows pool");
    entityPool = std::make_unique<Pool<Entity>>("Entity pool");

    Logger::Log(INFO, INTERNAL) << "* Inner initialization complete *";
}
Root::~Root() {
    renderer->DestroyAll();

    SDL_Quit();

    Logger::Log(INFO, INTERNAL) << "* Inner shutdown complete *";
}

}