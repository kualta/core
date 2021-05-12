#include <core/Modules/EngineModule.h>

namespace core {

EngineModule::EngineModule(InputModule* input) : Input(input), mainLoop(std::make_unique<EngineLoop>(input)) {
    Logger::Log(INFO, INTERNAL) << "Initialized Engline module";
}
EngineModule::~EngineModule() {
    Logger::Log(INFO, INTERNAL) << "Destroyed Engline module";
}
int32_t EngineModule::Main() {

    // Main engine loop
    mainLoop->Enter();

    return 0;
}

}
