#include <core/Modules/EngineModule.h>

namespace core {

EngineModule::EngineModule(InputModule* input)
: IModule("Engine", INTERNAL), engineLoop(std::make_unique<EngineLoop>(input)), inputModule(input) {

}
void EngineModule::Start() {
    inputModule->OnExitEvent.Subscribe([&](ExitEvent& event) { engineLoop->Stop(); });
}
int32_t EngineModule::Main() {

    /** Start all modules */
    engineLoop->StartModules();
    Logger::Log(INTERNAL, INFO) << "All Modules Started";

    /** Enter the Main Loop */
    engineLoop->Enter();

    /** Stop all modules */
    engineLoop->StopModules();
    Logger::Log(INTERNAL, INFO) << "All Modules Stopped";

    return 0;
}

}
