#include <core/Modules/IRenderModule.h>

#include <utility>

namespace core {

IRenderModule::IRenderModule(const string& moduleName, string type, IWindowRenderer* wRend)
: IModule(moduleName, RENDER),
renderType(std::move(type)),
windowRenderer(wRend)
{
    Logger::Log(RENDER, INFO) << " | Render Module configuration: ";
    Logger::Log(RENDER, INFO) << " |    Renderer type: " + renderType;
}
void IRenderModule::Tick() {
    Frame();
}

}