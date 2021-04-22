#include <core/Root.h>
#include <core/Renderer.h>

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

    Logger::Log(INFO, INTERNAL) << "* Core initialization complete *";
}
Root::~Root() {
    renderer->DestroyAll();

    SDL_Quit();
}

}