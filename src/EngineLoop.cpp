#include <core/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {


int32_t EngineLoop::Enter() {

    SDL_Event event;
    while ( isRunning ) {

        // TO BE MOVED TO InputModule
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                EngineLoop::Stop();
            }
        }



    }

    Logger::Log(INFO, INTERNAL) << "Main loop exit requested: quitting.";
    return 0;
}
void EngineLoop::Stop() {
    isRunning = false;
}

}