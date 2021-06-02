#include <core/Modules/IRenderModule.h>

#include <utility>

namespace core {

IRenderModule::IRenderModule(const string& moduleName, string type)
: IModule(moduleName, RENDER),
renderType(std::move(type))
{
    Logger::Log(RENDER, INFO) << " | Render Module configuration: ";
    Logger::Log(RENDER, INFO) << " |    Renderer type: " + renderType;
}
void IRenderModule::Tick() {
    Frame();
}

}