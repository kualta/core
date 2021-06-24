#include <core/Modules/VkRenderModule.h>
#include <core/VkWindowRenderer.h>
#include <core/CoreConfig.h>
#include <iostream>

namespace core {

VkRenderModule::VkRenderModule()
: IRenderModule("Render",
                "Vulkan",
                new VkWindowRenderer(this))
{

}
VkRenderModule::~VkRenderModule() {
    Cleanup();
}
void VkRenderModule::Init(Window& window) {
    CreateInstance(window);
    Logger::Log(RENDER, INFO) << "Initialized VkRenderModule";
    initialized = true;
}
void VkRenderModule::Cleanup() {
    delete windowRenderer;
}
void VkRenderModule::Frame() {

}
void VkRenderModule::CreateInstance(Window& window) {
    VkApplicationInfo appInfo { };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = CoreConfig::AppInfo::name.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(CoreConfig::AppInfo::majorVersion,
                                                 CoreConfig::AppInfo::minorVersion,
                                                 CoreConfig::AppInfo::patchVersion);
    appInfo.pEngineName = CoreConfig::CoreInfo::name.c_str();
    appInfo.engineVersion = VK_MAKE_VERSION(CoreConfig::CoreInfo::majorVersion,
                                            CoreConfig::CoreInfo::minorVersion,
                                            CoreConfig::CoreInfo::patchVersion);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    Logger::Log(RENDER, INFO) << "Available Vulkan extentions(" << extensionCount << "): ";
    for (const auto& extension : availableExtensions) {
        Logger::Log(RENDER, INFO) << " | " << extension.extensionName << " v." << extension.specVersion;
    }

    VkInstanceCreateInfo createInfo { };
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = layers.size();
    createInfo.ppEnabledLayerNames = layers.data();

    Logger::Log(RENDER, INFO) << "Creating VkInstance: ";
    Logger::Log(RENDER, INFO) << " | Application name: " << appInfo.pApplicationName;
    Logger::Log(RENDER, INFO) << " | Application version: " << appInfo.applicationVersion;
    Logger::Log(RENDER, INFO) << " | Engine version: " << appInfo.engineVersion;
    Logger::Log(RENDER, INFO) << " | API version: " << appInfo.apiVersion;
    Logger::Log(RENDER, INFO) << " | Enabled extensions (" << createInfo.enabledExtensionCount << "): ";
    for (int i = 0; i < createInfo.enabledExtensionCount; i++) {
        Logger::Log(RENDER, INFO) << " |  * " << *(createInfo.ppEnabledExtensionNames + i);
    }
    Logger::Log(RENDER, INFO) << " | Enabled layers (" << createInfo.enabledLayerCount << "): " ;
    for (int i = 0; i < createInfo.enabledLayerCount; i++) {
        Logger::Log(RENDER, INFO) << " |  * " << *(createInfo.ppEnabledLayerNames + i);
    }

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        Logger::Log(RENDER, ERR_HERE) << "VkInstance creation failed with error code: " << result;
        Logger::Log(RENDER, INFO) << "NOTE: check error code values here: ";
        Logger::Log(RENDER, INFO) << "https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkResult.html";
        throw std::runtime_error("VkInstance creation failed with error code: " + std::to_string(result));
    }
    Logger::Log(RENDER, INFO) << "Created VkInstance";
}
bool VkRenderModule::isReady() {
    return initialized;
}

}