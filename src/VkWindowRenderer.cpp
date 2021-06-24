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

    const std::vector<const char*> layerNames = {
            "VK_LAYER_KHRONOS_validation"
    };

    if ( !parent->isReady() ) {
        parent->requiredExtensions = extensionNames;
        parent->requiredLayers = layerNames;
        parent->Init(window);
    }
}

}