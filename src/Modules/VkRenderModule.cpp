#include <core/Modules/VkRenderModule.h>

namespace core {

VkRenderModule::VkRenderModule()
: IRenderModule("Render", "Vulkan")
{
    Init();
}
VkRenderModule::~VkRenderModule() {
    Cleanup();
}
void VkRenderModule::Init() {
    CreateInstance();
}
void VkRenderModule::Cleanup() {

}
void VkRenderModule::Frame() {

}
void VkRenderModule::CreateInstance() {
    VkApplicationInfo appInfo { };

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Core Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Core Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
}

}