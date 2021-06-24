#include <core/Modules/WindowModule.h>
#include <core/Logger.h>

namespace core {

WindowModule::WindowModule(IRenderModule* rModule)
: IModule("Window", WINDOW),
windowPool("Window pool"),
renderModule(rModule)
{

}
WindowModule::~WindowModule() {

}
void WindowModule::Tick() {

}

}
