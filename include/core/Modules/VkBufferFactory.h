#ifndef CORE_VKBUFFERFACTORY_H
#define CORE_VKBUFFERFACTORY_H


#include <core/Essential.h>
#include <core/Modules/VkMesh.h>
#include <core/Modules/VkRenderModule.h>
#include <core/Vertex.h>
#include <core/Primitive.h>

namespace core {

/// Set of vulkan buffer factory & helper functions
// Note: Functions are tied to core::VkRenderModule. FIXME?
class VkBufferFactory {
public:

    static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                             VkBuffer &buffer, VkDeviceMemory &bufferMemory);

    static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


};


}

#endif //CORE_VKBUFFERFACTORY_H
