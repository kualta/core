#include <core/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {

EngineLoop::EngineLoop(InputModule* inputModule) : Input(inputModule) {

}
int32_t EngineLoop::Enter() {
    while ( isRunning ) {

        /*
         * This will call Update() function on every module added to the core.
         * The modules lower in the dependency hierarchy are guaranteed to be updated before
         * their dependants.
         */
        this->TickModules();

        if ( Input->exitRequested ) {
            EngineLoop::Stop();
        }

    } // main loop

    Logger::Log(INFO, INTERNAL) << "Main loop exit requested: quitting.";
    return 0;
}
void EngineLoop::TickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Tick();
    });
}
void EngineLoop::Stop() {
    isRunning = false;
}

}