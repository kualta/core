#ifndef CORE_VKMESH_H
#define CORE_VKMESH_H

#include <core/Essential.h>
#include <core/IMesh.h>

#include <assimp/mesh.h>

namespace core {

typedef VkMesh Mesh;

class VkMesh : public IMesh {
public:
    VkMesh(AiMesh* aiMesh);

protected:
    static VkVertexInputBindingDescription GetBindingDescription();

};


}

#endif //CORE_VKMESH_H
