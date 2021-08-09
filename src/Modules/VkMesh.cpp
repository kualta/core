#include <core/Modules/VkMesh.h>
#include <core/Modules/VkRenderModule.h>
#include <core/Modules/VkBufferFactory.h>
#include <core/Vertex.h>
#include <core/Matrix.h>
#include <core/Primitive.h>

namespace core {

VkMesh::VkMesh(aiMesh *aiMesh) {

}
VkMesh::VkMesh() {
    vertices = {
            {-0.5f, -0.5f, {1.0f, 0.0f, 0.0f}},
            {0.5f, -0.5f, {0.0f, 1.0f, 0.0f}},
            {0.5f, 0.5f, {0.0f, 0.0f, 1.0f}},
            {-0.5f, 0.5f, {1.0f, 1.0f, 1.0f}}
    };
    indices = {
            0, 1, 2, 2, 3, 0
    };

    CreateVertexBuffer();
    CreateIndexBuffer();

    VkRenderModule::meshes.push_back(this);
}
VkMesh::~VkMesh() {
    vkDestroyBuffer(VkRenderModule::device, vertexBuffer, nullptr);
    vkFreeMemory(VkRenderModule::device, vertexBufferMemory, nullptr);

    vkDestroyBuffer(VkRenderModule::device, indexBuffer, nullptr);
    vkFreeMemory(VkRenderModule::device, indexBufferMemory, nullptr);
}
VkVertexInputBindingDescription VkMesh::GetBindingDescription() {
    VkVertexInputBindingDescription bindingDescription { };
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(ColorVertex2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}
std::array<VkVertexInputAttributeDescription, 2> VkMesh::GetAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions { };

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(ColorVertex2, x);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(ColorVertex2, rgb);

    return attributeDescriptions;
}
void VkMesh::CreateVertexBuffer() {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    VkBufferFactory::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
    | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(VkRenderModule::device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(VkRenderModule::device, stagingBufferMemory);

    VkBufferFactory::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT
    | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    VkBufferFactory::CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(VkRenderModule::device, stagingBuffer, nullptr);
    vkFreeMemory(VkRenderModule::device, stagingBufferMemory, nullptr);
}
void VkMesh::CreateIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    VkBufferFactory::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(VkRenderModule::device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(VkRenderModule::device, stagingBufferMemory);

    VkBufferFactory::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
    VkBufferFactory::CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(VkRenderModule::device, stagingBuffer, nullptr);
    vkFreeMemory(VkRenderModule::device, stagingBufferMemory, nullptr);
}

}