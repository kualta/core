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

protected:
    static VkVertexInputBindingDescription GetBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

};


}

#endif //CORE_VKMESH_H