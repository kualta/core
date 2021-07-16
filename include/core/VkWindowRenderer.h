#ifndef CORE_VKWINDOWRENDERER_H
#define CORE_VKWINDOWRENDERER_H

#include <vulkan/vulkan_core.h>
#include "Essential.h"
#include "IWindowRenderer.h"

namespace core {

class VkWindowRenderer : public IWindowRenderer {
public:
    VkWindowRenderer(VkRenderModule* renderModule);

    void InitWindow(Window &window) override;

    void AddRenderer(Window& window) override;

    VkRenderModule* renderModule;
};

}

#endif //CORE_VKWINDOWRENDERER_H
