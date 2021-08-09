#ifndef CORE_VKRENDERER_H
#define CORE_VKRENDERER_H

#include <core/Essential.h>
#include <core/Components/IRenderer.h>
#include <core/Matrix.h>

#include "vulkan/vulkan.h"

namespace core {

struct UniformBufferObject {
    Matrix4 model;
    Matrix4 view;
    Matrix4 proj;
};


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

    void CreateUniformBuffers();
    void UpdateUniformBuffer(uint32_t currentImage);

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    VkMesh* mesh { nullptr };
};

}

#endif //CORE_VKRENDERER_H
