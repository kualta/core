#include <core/Modules/IRenderModule.h>

namespace core {

IRenderModule::IRenderModule(const string &moduleName, IWindowRenderer *windowRenderer)
: IModule(moduleName, RENDER),
windowRenderer(windowRenderer),
inputModule(inputModule)
{
    Logger::Log(RENDER, INFO) << "Render Module initialized";
}
void IRenderModule::Tick() {
    Frame();
}

}