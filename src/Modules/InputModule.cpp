#include <core/Modules/InputModule.h>

namespace core {


InputModule::InputModule() {
    Logger::Log(INFO, INPUT) << "Initialized Input module";
}
InputModule::~InputModule() {
    Logger::Log(INFO, INPUT) << "Destroyed Input module";

}
bool InputModule::GetAnyKey() {
    return false;
}
void InputModule::Update() {
    PollEvents();
}
void InputModule::PollEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exitRequested = true;
        }
    }

}


}