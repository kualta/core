#ifndef CORE_VKMESH_H
#define CORE_VKMESH_H

#include <core/Essential.h>
#include <core/IMesh.h>

#include <array>
#include <assimp/mesh.h>
#include <vulkan/vulkan_core.h>

namespace core {

typedef VkMesh Mesh;

class VkMesh : public IMesh {
public:
    VkMesh(aiMesh* aiMesh);
    ~VkMesh();

    static VkVertexInputBindingDescription GetBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

    static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

protected:

    void CreateVertexBuffer();

    VkBuffer vertexBuffer;

    std::vector<ColorVertex> vertices;
};


}

#endif //CORE_VKMESH_H
