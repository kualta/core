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
void VkWindowRenderer::InitWindow(Window &window) {
    // TODO: Switch behaviour based on windowing lib

    uint32_t extensionCount { 0 };
    SDL_Vulkan_GetInstanceExtensions(nullptr, &extensionCount, nullptr);
    std::vector<const char*> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(nullptr, &extensionCount, extensionNames.data());

    std::vector<const char*> layerNames { };

    if ( !parent->isReady() ) {
        parent->extensions = extensionNames;
        parent->layers = layerNames;
        parent->Init(window);
    }
}

}