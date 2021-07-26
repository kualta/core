#include <core/Modules/VkMesh.h>
#include <core/Vertex.h>

namespace core {

VkMesh::VkMesh(aiMesh *aiMesh) {

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


}