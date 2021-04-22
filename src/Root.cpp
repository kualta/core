#include <core/Root.h>

#include <bgfx/bgfx.h>
#include <SDL.h>
#include <memory>


namespace core {


Root::Root() : Object("Root") {
    if ( !SDL_Init(SDL_INIT_EVERYTHING) ) {
        Logger::Log(INFO, INTERNAL) << "SDL initialized successfully";
    } else {
        Logger::Log(ERR, INTERNAL) << "SDL initialization failed!";
    }

    windowPool = std::make_unique<Pool<Window>>("Windows pool");

    Logger::Log(INFO, INTERNAL) << "* Core initialization complete *";
}
Root::~Root() {
    bgfx::shutdown();
    Logger::Log(INFO, INTERNAL) << "Shut down renderer";

    SDL_Quit();
    Logger::Log(INFO, INTERNAL) << "Shut down SDL";
}

}