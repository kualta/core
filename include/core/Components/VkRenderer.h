#ifndef CORE_VKRENDERER_H
#define CORE_VKRENDERER_H

#include <core/Essential.h>
#include <core/Components/IRenderer.h>

namespace core {

#ifdef CORE_SIMPLIFY_SYNTAX
typedef class VkRenderer Renderer;
#endif

class VkRenderer : public IRenderer {
public:
    VkRenderer(Entity& parent,
               Model* modelPtr,
               const string& name = "Renderer");
    ~VkRenderer();

    void Draw() override;

protected:

    VkMesh*     mesh    { nullptr };

};

}

#endif //CORE_VKRENDERER_H
