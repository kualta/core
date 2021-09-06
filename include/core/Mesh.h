#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Essential.h"

#include <assimp/mesh.h>

namespace core {

class Mesh {
public:

protected:
    explicit Mesh(aiMesh* mesh);

    Vertex*   vertexBuffer    { nullptr };
    uint32_t* indexBuffer     { nullptr };

    size_t    indicesAmount   { 0 };
    size_t    verticesAmount  { 0 };
    size_t    trianglesAmount { 0 };
};


} // namespace core

#endif //CORE_MESH_H
