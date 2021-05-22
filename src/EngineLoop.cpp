#include <core/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {


int32_t EngineLoop::Enter() {
    while ( isRunning ) {

        /*
         * This will call Update() function on every module added to the core.
         * The modules lower in the dependency hierarchy are guaranteed to be updated before
         * their dependants.
         */
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
        module->Tick();
    });
}
void EngineLoop::Stop() {
    isRunning = false;
}
EngineLoop::EngineLoop(InputModule* inputModule) : Input(inputModule) {

}

}