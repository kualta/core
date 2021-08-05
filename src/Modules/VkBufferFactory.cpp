#include <core/Modules/VkBufferFactory.h>

namespace core {

void VkBufferFactory::CreateBuffer(VkDeviceSize          size,
                                   VkBufferUsageFlags    usage,
                                   VkMemoryPropertyFlags properties,
                                   VkBuffer              &buffer,
                                   VkDeviceMemory        &bufferMemory)
{
    VkBufferCreateInfo bufferInfo { };
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(VkRenderModule::device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        Logger::Log(MEMORY, ERR_HERE) << "Failed to create vulkan buffer";
        throw std::runtime_error("Failed to create buffer");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(VkRenderModule::device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo { };
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(VkRenderModule::device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        Logger::Log(MEMORY, ERR_HERE) << "Failed to allocate buffer memory";
        throw std::runtime_error("Failed to allocate buffer memory");
    }

    vkBindBufferMemory(VkRenderModule::device, buffer, bufferMemory, 0);
}
uint32_t VkBufferFactory::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(VkRenderModule::physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    Logger::Log(MEMORY, ERR_HERE) << "Failed to find suitable memory type";
    throw std::runtime_error("Failed to find suitable memory type");
}
void VkBufferFactory::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBufferAllocateInfo allocInfo { };
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = VkRenderModule::commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(VkRenderModule::device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo { };
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);
        VkBufferCopy copyRegion { };
        copyRegion.srcOffset = 0;
        copyRegion.dstOffset = 0;
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo { };
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(VkRenderModule::graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(VkRenderModule::graphicsQueue);

    vkFreeCommandBuffers(VkRenderModule::device, VkRenderModule::commandPool, 1, &commandBuffer);
}

}