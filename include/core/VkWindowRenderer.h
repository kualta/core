#ifndef CORE_VKWINDOWRENDERER_H
#define CORE_VKWINDOWRENDERER_H

#include "Essential.h"
#include "IWindowRenderer.h"

namespace core {

class VkWindowRenderer : public IWindowRenderer {
public:

    bool InitWindow(Window &window) override;

};

}

#endif //CORE_VKWINDOWRENDERER_H
