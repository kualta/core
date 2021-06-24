#include <core/Modules/IRenderModule.h>

#include <utility>

namespace core {

IRenderModule::IRenderModule(const string& moduleName, const string& type, IWindowRenderer* wRend)
: IModule(moduleName, RENDER),
renderType(type),
windowRenderer(wRend)
{
    Logger::Log(RENDER, INFO) << " | Render Module configuration: ";
    Logger::Log(RENDER, INFO) << " |    Renderer type: " + renderType;
}
void IRenderModule::Tick() {
    Frame();
}

}