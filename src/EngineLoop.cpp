#include <core/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {


int32_t EngineLoop::Enter() {
    while ( isRunning ) {

        Input->Update();

        if ( Input->exitRequested ) {
            EngineLoop::Stop();
        }

        this->TickAll();

    }

    Logger::Log(INFO, INTERNAL) << "Main loop exit requested: quitting.";
    return 0;
}
void EngineLoop::TickAll() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Update();
    });
}
void EngineLoop::Stop() {
    isRunning = false;
}
EngineLoop::EngineLoop(InputModule* inputModule) : Input(inputModule) {

}

}