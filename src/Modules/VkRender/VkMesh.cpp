#include <core/Modules/VkRender/VkMesh.h>

namespace core {

VkMesh::VkMesh(AiMesh *aiMesh) {


}
VkVertexInputBindingDescription VkMesh::GetBindingDescription() {
    VkVertexInputBindingDescription bindingDescription { };

    return bindingDescription;
}


}