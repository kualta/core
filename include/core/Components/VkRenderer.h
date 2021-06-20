#ifndef CORE_VKRENDERER_H
#define CORE_VKRENDERER_H

#include <core/Essential.h>
#include <core/Components/IRenderer.h>

namespace core {

class VkRenderer : public IRenderer {
public:
    VkRenderer(Entity& parent,
               Model* modelPtr,
               const string& name = "Renderer");

    void Draw() override;

};


}

#endif //CORE_VKRENDERER_H
