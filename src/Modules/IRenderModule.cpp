#include <core/Modules/IRenderModule.h>

namespace core {

IRenderModule::IRenderModule(const string &moduleName, IWindowRenderer *windowRenderer, InputModule *inputModule)
: IModule(moduleName, RENDER),
windowRenderer(windowRenderer),
inputModule(inputModule)
{
    SubscribeToEvents();
    Logger::Log(RENDER, INFO) << "Render Module initialized";
}
void IRenderModule::Tick() {
    Frame();
}
void IRenderModule::SubscribeToEvents() {
    if ( !inputModule ) {
        Logger::Log(RENDER, WARN_HERE) << "Render module doesn't have dependent InputModule! "
                                       << "Cannot subscribe to events";
    }
    inputModule->SubscribeTo("OnWindowResized", OnWindowResized);
}

}