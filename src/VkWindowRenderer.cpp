#include <core/VkWindowRenderer.h>
#include <core/Modules/VkRenderModule.h>
#include <core/Modules/WindowModule.h>
#include <core/Core.h>

#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

namespace core {

VkWindowRenderer::VkWindowRenderer(VkRenderModule* parent)
: parent(parent)
{

}
void VkWindowRenderer::InitWindow(Window& window) {
    // TODO: Switch behaviour based on windowing lib

    uint32_t extensionCount { 0 };
    SDL_Vulkan_GetInstanceExtensions(nullptr, &extensionCount, nullptr);
    std::vector<const char*> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(nullptr, &extensionCount, extensionNames.data());

    if ( !parent->isReady() ) {
        parent->requiredExtensions = extensionNames;
        parent->Init(window);
    }
}
void VkWindowRenderer::AddRenderer(Window& window) {
    if (SDL_Vulkan_CreateSurface(window.GetSdlWindow(), parent->instance, &parent->surface) != SDL_TRUE) {
        Logger::Log(RENDER, ERR_HERE) << "Cannot create vulkan surface";
        throw std::runtime_error("Cannot create vulkan surface");
    }
    Logger::Log(RENDER, INFO) << "Created vulkan surface for window " << window.GetTitle();
}

}