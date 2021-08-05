#ifndef CORE_VKMESH_H
#define CORE_VKMESH_H

#include <core/Essential.h>
#include <core/IMesh.h>

#include <array>
#include <assimp/mesh.h>
#include <vulkan/vulkan_core.h>

namespace core {

#ifdef CORE_SIMPLIFY_SYNTAX
typedef class VkMesh Mesh;
#endif

class VkMesh : public IMesh {
public:
    VkMesh();
    VkMesh(aiMesh* aiMesh);
    ~VkMesh();

    static VkVertexInputBindingDescription GetBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkBuffer vertexBuffer;
    std::vector<ColorVertex2> vertices;
protected:

    void CreateVertexBuffer();

    VkDeviceMemory vertexBufferMemory;

};


}

#endif //CORE_VKMESH_H
