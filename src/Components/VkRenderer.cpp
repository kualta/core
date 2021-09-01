#include <core/Components/VkRenderer.h>
#include <core/Modules/VkBufferFactory.h>
#include <core/Components/Camera.h>

namespace core {

VkRenderer::VkRenderer(Entity& parent,
                       Model* modelPtr,
                       const string& name)
: IRenderer(parent, modelPtr, name)
{
    CreateUniformBuffers();
}
VkRenderer::~VkRenderer() {
    for (size_t i = 0; i < VkRenderModule::swapChainImages.size(); i++) {
        vkDestroyBuffer(VkRenderModule::device, uniformBuffers[i], nullptr);
        vkFreeMemory(VkRenderModule::device, uniformBuffersMemory[i], nullptr);
    }
}
void VkRenderer::Draw() {
    UpdateUniformBuffer(VkRenderModule::imageIndex);
}
// TODO: Add force uniform buffers recreation func on recreation of swap chain
void VkRenderer::CreateUniformBuffers() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(VkRenderModule::swapChainImages.size());
    uniformBuffersMemory.resize(VkRenderModule::swapChainImages.size());

    for (size_t i = 0; i < VkRenderModule::swapChainImages.size(); i++) {
        VkBufferFactory::CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
    }
}
void VkRenderer::UpdateUniformBuffer(uint32_t currentImage) {
    UniformBufferObject ubo { };

    ubo.model = Matrix4::identity;
        ubo.model = ubo.model * Math::ScaleMatrix(entity->transform->scale);
        ubo.model = ubo.model * Math::EulerRotationMatrix(entity->transform->rotation);
        ubo.model = ubo.model * Math::TranslationMatrix(entity->transform->position);
    ubo.view = VkRenderModule::mainCamera->GetViewMtx();
    ubo.proj = VkRenderModule::mainCamera->GetProjMtx();

    void* data;
    vkMapMemory(VkRenderModule::device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(VkRenderModule::device, uniformBuffersMemory[currentImage]);
}

}