#include <core/Modules/VkMesh.h>
#include <core/Modules/VkRenderModule.h>
#include <core/Vertex.h>
#include <core/Primitive.h>

namespace core {

VkMesh::VkMesh(aiMesh *aiMesh) {
    vertices = {
            {-1.0f,  1.0f,  1.0f, {1.0f, 1.0f, 1.0f, 1.0f}},
            { 1.0f,  1.0f,  1.0f, {1.0f, 1.0f, 1.0f, 1.0f}},
            {-1.0f, -1.0f,  1.0f, {1.0f, 0.5f, 1.0f, 1.0f}},
            { 1.0f, -1.0f,  1.0f, {1.0f, 0.5f, 1.0f, 1.0f}},
            {-1.0f,  1.0f, -1.0f, {1.0f, 1.0f, 0.5f, 1.0f}},
            { 1.0f,  1.0f, -1.0f, {1.0f, 1.0f, 0.5f, 1.0f}},
            {-1.0f, -1.0f, -1.0f, {1.0f, 1.0f, 1.0f, 0.5f}},
            { 1.0f, -1.0f, -1.0f, {1.0f, 1.0f, 1.0f, 0.5f}}
    };
}
VkVertexInputBindingDescription VkMesh::GetBindingDescription() {
    VkVertexInputBindingDescription bindingDescription { };
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(ColorVertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}
std::array<VkVertexInputAttributeDescription, 2> VkMesh::GetAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions { };

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(ColorVertex, x);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(ColorVertex, argb);


    return attributeDescriptions;
}
void VkMesh::CreateVertexBuffer() {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(vertices[0]) * vertices.size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(VkRenderModule::device, &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
        Logger::Log(RENDER, ERR_HERE) << "Failed to create vertex buffer";
        throw std::runtime_error("Failed to create vertex buffer");
    }
}
VkMesh::~VkMesh() {
    vkDestroyBuffer(VkRenderModule::device, vertexBuffer, nullptr);
}
uint32_t VkMesh::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(VkRenderModule::physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if (typeFilter & (1 << i)) {
            return i;
        }
    }

    Logger::Log(MEMORY, ERR_HERE) << "Failed to find suitable memory type";
    throw std::runtime_error("Failed to find suitable memory type");
}


}