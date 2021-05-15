#include <core/Modules/EngineModule.h>

namespace core {

EngineModule::EngineModule(InputModule* input)
: IModule("Engine", INTERNAL), Input(input), mainLoop(std::make_unique<EngineLoop>(input)) {

}
EngineModule::~EngineModule() {

}
int32_t EngineModule::Main() {

    // Main engine loop
    mainLoop->Enter();

    return 0;
}
void EngineModule::Update() {

}

}
