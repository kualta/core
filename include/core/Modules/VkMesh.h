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
    // TODO: add constructor from core::Mesh* mesh, remove aiMesh* constructor
    VkMesh(aiMesh* aiMesh);
    ~VkMesh();

    static VkVertexInputBindingDescription GetBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

    // TODO: move two buffers to core::Mesh
    std::vector<ColorVertex2> vertices;
    std::vector<uint16_t> indices;

    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;

protected:

    void CreateVertexBuffer();
    void CreateIndexBuffer();

    VkDeviceMemory vertexBufferMemory;
    VkDeviceMemory indexBufferMemory;

};


}

#endif //CORE_VKMESH_H
