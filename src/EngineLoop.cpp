#include <core/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {

bool EngineLoop::isRunning { true };

EngineLoop::EngineLoop(InputModule* inputModule) : inputModule(inputModule) {

}
int32_t EngineLoop::Enter() {

    while ( isRunning ) {

        /*
         * This will call Tick() function on every module added to the core.
         * The modules lower in the dependency hierarchy are guaranteed to be updated before
         * their dependants.
         */
        this->TickModules();

        if ( inputModule->exitRequested ) {
            Logger::Log(INTERNAL, INFO) << "Main loop exit requested: ";

            this->StopModules();
            Logger::Log(INTERNAL, INFO) << " | Modules stopped";

            EngineLoop::Stop();
            Logger::Log(INTERNAL, INFO) << " | Main loop stopped";
        }

    } // main loop

    return 0;
}
void EngineLoop::Stop() {
    isRunning = false;
}
void EngineLoop::TickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Tick();
    });
}
void EngineLoop::StopModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Stop();
    });
}

}