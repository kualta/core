#include <core/Components/VkRenderer.h>
#include <core/Modules/VkBufferFactory.h>

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

    ubo.model =
    //    matrix = matrix * Math::ScaleMatrix(scale);
    //    matrix = matrix * Math::EulerRotationMatrix(rotation);
    //    matrix = matrix * Math::TranslationMatrix(position);
}

}