#include <core/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {


int32_t EngineLoop::Enter() {
    while ( isRunning ) {

        this->UpdateModules();

        if ( Input->exitRequested ) {
            EngineLoop::Stop();
        }

    }

    Logger::Log(INFO, INTERNAL) << "Main loop exit requested: quitting.";
    return 0;
}
void EngineLoop::UpdateModules() {
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