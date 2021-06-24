#ifndef CORE_VKWINDOWRENDERER_H
#define CORE_VKWINDOWRENDERER_H

#include "Essential.h"
#include "IWindowRenderer.h"

namespace core {

class VkWindowRenderer : public IWindowRenderer {
public:
    VkWindowRenderer(VkRenderModule* parent);

    void InitWindow(Window &window) override;

    VkRenderModule* parent;
};

}

#endif //CORE_VKWINDOWRENDERER_H
