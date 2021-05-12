#include <core/Modules/WindowModule.h>
#include <core/Logger.h>

namespace core {

WindowModule::WindowModule() : IModule("Window"), windowPool("Window pool") {
    Logger::Log(INFO, WINDOW) << "Initialized Window module";
}
WindowModule::~WindowModule() {
    Logger::Log(INFO, WINDOW) << "Destroyed Window module";
}
void WindowModule::Update() {

}

}
