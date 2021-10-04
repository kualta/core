#include <core/Engine/EngineLoop.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace core {

bool EngineLoop::isRunning { true };

EngineLoop::EngineLoop(InputModule* inputModule) : inputModule(inputModule) {

}
int32_t EngineLoop::Enter() {

    while ( isRunning ) {

        /** Called before the frame is drawn */
        this->EarlyTickModules();

        /** Update modules & draw frame */
        this->TickModules();

        /** Called after the frame has been drawn */
        this->LateTickModules();

    } // main loop

    return 0;
}
void EngineLoop::StartModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Start();
    });
}
void EngineLoop::StopModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Stop();
    });
}
void EngineLoop::EarlyTickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->EarlyTick();
    });
}
void EngineLoop::TickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Tick();
    });
}
void EngineLoop::LateTickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->LateTick();
    });
}
void EngineLoop::Stop() {
    Logger::Log(INTERNAL, INFO) << "Main loop exit requested";
    isRunning = false;
}

}